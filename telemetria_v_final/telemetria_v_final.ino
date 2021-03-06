
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include "definicoes_sistema.h"
#include "sensor.h"

#include "sensor_acel.h"
#include "sensor_pres.h"
#include "sensor_temp.h"
#include "led.h"
#include "lcd.h"
#include "lcd_real.h"

#include "switcher.h"
#include "bluetooth.h"
#include "micro_sd.h"

#include "task_switcher.h"





/***********************************************************************
Estaticos
**********************************************************************/
int codigoEvento = NENHUM_EVENTO;
int codigoAcao;
int eventoInterno = NENHUM_EVENTO;
int estado = IDLE;
int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];

const int rx = 15;//trocar valores aqui !!!!!!!!!
const int tx = 14;
const int swt_pin = 12;
const int led_pin1 = 11;
const int led_pin2 = 10;
const int CS = 4;//pino do micro sd
const int rs = 43, en = 33, d4 = 41, d5 = 39, d6 = 37, d7 = 35;

const int limite_temperatura = 100;


/***********************************************************************
Componentes
***********************************************************************/

SWITCHER swt(swt_pin);
LED led1(led_pin1);
LED led2(led_pin2);
Sensor_acel acel;
Sensor_temp tmp;
Sensor_pres prs;
Micro_SD micro(CS);
Module_bluetooth bluetooth(rx,tx);
LCDReal lcd(rs, en, d4, d5, d6, d7);

/***********************************************************************
Globais
**********************************************************************/

float aclx = 0;
float acly = 0;
float aclz = 0;
float temperatura = 0;
float pressao = 0;



/***********************************************************************
 FreeRTOS
 ***********************************************************************/
void taskMaqEstados(void *pvParameters);
void taskObterEvento(void *pvParameters);
void taskLerSensores(void *pvParameters);
void taskEscreveLCD(void *pvParameters);
void taskBluetooth(void *pvParameters);
void taskEscreveSD(void *pvParameters);

TaskHandle_t xTaskMaqEstados, xTaskObterEvento, xTaskLerSensores, xTaskEscreveLCD, xTaskEscreveSD,xTaskBluetooth;
QueueHandle_t xQueue;
SemaphoreHandle_t xBinarySemaphore;

/************************************************************************
 executarAcao
 Executa uma acao
 Parametros de entrada:
    (int) codigo da acao a ser executada
 Retorno: (int) codigo do evento interno ou NENHUM_EVENTO
*************************************************************************/
int executarAcao(int codigoAcao)
{
    int retval;

    retval = NENHUM_EVENTO;
    if (codigoAcao == NENHUMA_ACAO)
        return retval;

    switch(codigoAcao)
    {
    case ACIONAR:
        xSemaphoreGive(xBinarySemaphore);
        tmp.ligar(true);
        acel.ligar(true);
        prs.ligar(true);
        lcd.ligar(true);
        micro.ligar(true);
        led1.ligar(true);
        bluetooth.ligar(true);
        Serial.println("ATIVACAO -> Estado ATIVADO");
        break;
    case DESLIGAR:
        lcd.apaga();
        tmp.ligar(false);
        acel.ligar(false);
        prs.ligar(false);
        lcd.ligar(false);
        micro.ligar(false);
        led1.ligar(false);
        bluetooth.ligar(false);
        Serial.println("DESATIVACAO -> Estado IDLE");
        break;
    } // switch

    return retval;
} // executarAcao

/************************************************************************
 iniciaMaquina de Estados
 Carrega a maquina de estados
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void iniciaMaquinaEstados()
{
  int i;
  int j;

  for (i=0; i < NUM_ESTADOS; i++) {
    for (j=0; j < NUM_EVENTOS; j++) {
       acao_matrizTransicaoEstados[i][j] = NENHUMA_ACAO;
       proximo_estado_matrizTransicaoEstados[i][j] = i;
    }
  }
  //Matriz de estados:
  proximo_estado_matrizTransicaoEstados[IDLE][LIGAR_SWITCH] = ATIVO;  
  acao_matrizTransicaoEstados[IDLE][LIGAR_SWITCH] = ACIONAR;

  proximo_estado_matrizTransicaoEstados[ATIVO][DESLIGAR_SWITCH] = IDLE;
  acao_matrizTransicaoEstados[ATIVO][DESLIGAR_SWITCH] = DESLIGAR;

  proximo_estado_matrizTransicaoEstados[IDLE][DESLIGAR_SWITCH] = IDLE;
  acao_matrizTransicaoEstados[IDLE][DESLIGAR_SWITCH] = NENHUMA_ACAO;

  proximo_estado_matrizTransicaoEstados[ATIVO][LIGAR_SWITCH] = ATIVO;
  acao_matrizTransicaoEstados[ATIVO][LIGAR_SWITCH] = NENHUMA_ACAO;

  
} // initStateMachine

/************************************************************************
 iniciaSistema
 Inicia o sistema ...
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void iniciaSistema()
{
   iniciaMaquinaEstados();
} // initSystem


/************************************************************************
 obterAcao
 Obtem uma acao da Matriz de transicao de estados
 Parametros de entrada: estado (int)
                        evento (int)
 Retorno: codigo da acao
*************************************************************************/
int obterAcao(int estado, int codigoEvento) {
  return acao_matrizTransicaoEstados[estado][codigoEvento];
} // obterAcao


/************************************************************************
 obterProximoEstado
 Obtem o proximo estado da Matriz de transicao de estados
 Parametros de entrada: estado (int)
                        evento (int)
 Retorno: codigo do estado
*************************************************************************/
int obterProximoEstado(int estado, int codigoEvento) {
  return proximo_estado_matrizTransicaoEstados[estado][codigoEvento];
} // obterAcao

/***********************************************************************
 Tasks
 ***********************************************************************/

/************************************************************************
 taskMaqEstados
 Task principal de controle que executa a maquina de estados
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void taskMaqEstados(void *pvParameters) {
  int codigoEvento;
  BaseType_t xStatus;

  for( ;; ) {
    if( xQueueReceive( xQueue, &codigoEvento, portMAX_DELAY ) == pdPASS ) {
      if (codigoEvento != NENHUM_EVENTO)
      {
        
        codigoAcao = obterAcao(estado, codigoEvento);
        estado = obterProximoEstado(estado, codigoEvento);
        eventoInterno = executarAcao(codigoAcao);
        Serial.print("Estado: ");
        Serial.print(estado);
        Serial.print(" Evento: ");
        Serial.print(codigoEvento);
        Serial.print(" Acao: ");
        Serial.println(codigoAcao);

       //Descomente para imprimir ocupa????o do stack
//       Serial.print("Task stacks remaining: "); 
//       Serial.print(uxTaskGetStackHighWaterMark(xTaskLerSensores)); Serial.print(" "); 
//       Serial.println(uxTaskGetStackHighWaterMark(xTaskEscreveLCD));
      }
    }
    else {
      Serial.println("Erro ao receber evento m.e. na fila");
    }
  }
}

/************************************************************************
 taskObterEvento
 Task que faz pooling de eventos
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void taskObterEvento(void *pvParameters) {
  int codigoEvento;
  BaseType_t xStatus;
  TickType_t xLastWakeTime;
  const TickType_t xDelay100ms = pdMS_TO_TICKS( 250 );

  for( ;; ) {
    codigoEvento = NENHUM_EVENTO;
    
    if ((swt.estaligado())&&(!estado)) {
      codigoEvento = LIGAR_SWITCH;
      xStatus = xQueueSendToBack( xQueue, &codigoEvento, 0 );
      if( xStatus != pdPASS ){
        Serial.println("Erro ao enviar evento o.e.1 para fila");
      }
      vTaskDelayUntil( &xLastWakeTime, xDelay100ms )
      continue;
    }
    else if ((!swt.estaligado())&&(estado)){
      codigoEvento = DESLIGAR_SWITCH;
      xStatus = xQueueSendToBack( xQueue, &codigoEvento, 0 );
      if( xStatus != pdPASS ){
        Serial.println("Erro ao enviar evento o.e.2 para fila");
      }
      vTaskDelayUntil( &xLastWakeTime, xDelay100ms )
      continue;
    }
  }
}

/************************************************************************
 taskLerSensores
 Task que bipa a sirene periodicamente caso acionada
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void taskLerSensores(void *pvParameters) {
  TickType_t xLastWakeTime;
  const TickType_t xDelay500ms = pdMS_TO_TICKS( 500 );

  for( ;; ) {
    xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
    xLastWakeTime = xTaskGetTickCount();
    while(tmp.estaligado()) {
      temperatura = tmp.get_val();
      if (temperatura>limite_temperatura && !led2.estaligado()){
        led2.ligar(true);
      }
      else if (temperatura<limite_temperatura && led2.estaligado()){
        led2.ligar(false);
      }
      pressao = prs.get_val();
      acel.get_val();
      aclx = acel.get_valx();
      acly = acel.get_valy();
      aclz = acel.get_valz();
      xSemaphoreGive(xBinarySemaphore);
      vTaskDelayUntil( &xLastWakeTime, xDelay500ms );
    }
  }
}

/************************************************************************
 taskEscreveLCD
 Task que bipa a sirene periodicamente caso acionada
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void taskEscreveLCD(void *pvParameters) {
  TickType_t xLastWakeTime;
  const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000 );

  for( ;; ) {
    xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
    xLastWakeTime = xTaskGetTickCount();
    while(lcd.estaligado()) {
      lcd.escreve(aclx,acly,aclz,pressao,temperatura);
      xSemaphoreGive(xBinarySemaphore);
      vTaskDelayUntil( &xLastWakeTime, xDelay1000ms );
    }
  }
}

/************************************************************************
 taskEscreveSD
 Task que bipa a sirene periodicamente caso acionada
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void taskEscreveSD(void *pvParameters) {
  TickType_t xLastWakeTime;
  const TickType_t xDelay500ms = pdMS_TO_TICKS( 500 );

  for( ;; ) {
    xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
    xLastWakeTime = xTaskGetTickCount();

    while(micro.estaligado()) {
      micro.escreve(aclx,acly,aclz,pressao,temperatura);
      xSemaphoreGive(xBinarySemaphore);
      vTaskDelayUntil( &xLastWakeTime, xDelay500ms );
    }
  }
}

/************************************************************************
 taskEscreveSD
 Task que bipa a sirene periodicamente caso acionada
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void taskBluetooth(void *pvParameters) {
  TickType_t xLastWakeTime;
  const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000 );

  for( ;; ) {
    xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
    xLastWakeTime = xTaskGetTickCount();

    while(bluetooth.estaligado()) {
      bluetooth.escreve(aclx, acly, aclz, pressao, temperatura);
      xSemaphoreGive(xBinarySemaphore);
      vTaskDelayUntil( &xLastWakeTime, xDelay1000ms );
    }
  }
}


/************************************************************************
 Main
 Loop principal de controle que executa a maquina de estados
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/


void setup(){

    Serial.begin(9600);
    tmp.setp();
    prs.setp();
    micro.setp();
    acel.setp();
    bluetooth.setp();
    iniciaSistema();
    Serial.println("Setup conclu??do -> Estado: IDLE");

    // configure tasks
    xBinarySemaphore = xSemaphoreCreateBinary();
    xQueue = xQueueCreate(10, sizeof(int));
    if(xQueue != NULL && xBinarySemaphore != NULL)
    {
        xTaskCreate(taskMaqEstados,"taskMaqEstados", 300, NULL, 1, &xTaskMaqEstados);
        xTaskCreate(taskObterEvento,"taskObterEvento", 300, NULL, 1, &xTaskObterEvento);
        xTaskCreate(taskLerSensores,"taskLerSensores", 300, NULL, 1, &xTaskLerSensores);
        xTaskCreate(taskEscreveLCD,"taskEscreveLCD", 500, NULL, 1, &xTaskEscreveLCD);
        xTaskCreate(taskEscreveSD,"taskEscreveSD", 500, NULL, 1, &xTaskEscreveSD);
        xTaskCreate(taskBluetooth,"taskBluetooth", 500, NULL, 1, &xTaskBluetooth);
        vTaskStartScheduler();
    }
    else
    {
        Serial.print("else");/* The queue or semaphore could not be created. */
    }
} // setup
void loop() {
} // main
