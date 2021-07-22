
#include <Arduino.h>
//#include <Arduino_FreeRTOS.h>
//#include <queue.h>
//#include <semphr.h>
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





/***********************************************************************
Estaticos
**********************************************************************/
int codigoEvento = NENHUM_EVENTO;;
int codigoAcao;
int eventoInterno = NENHUM_EVENTO;
int estado = IDLE;
int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];

int rx = 19;//trocar valores aqui !!!!!!!!!
int tx = 18;

/***********************************************************************
Componentes
***********************************************************************/
int pino = 12;
SWITCHER swt(pino);
//LED led(pino);
const int rs = 43, en = 33, d4 = 41, d5 = 39, d6 = 37, d7 = 35;
Sensor_acel acel;
Sensor_temp tmp;
Sensor_pres prs;
//Transmissao transmit;
int CS = 4;//pino do micro sd
Micro_SD micro(CS);
//Module_bluetooth bluetooth(rx,tx);
LCDReal lcd(rs, en, d4, d5, d6, d7);

/***********************************************************************
Globais
**********************************************************************/

float aclx = 0;
float acly = 0;
float aclz = 0;
float temperatura;
float pressao;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tmp.setp();
  prs.setp();
  micro.setp();
  acel.setp();
  //bluetooth.setp();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //switch
  Serial.println(swt.estaligado());
  delay(1000);
  //lcd.escreve(swt.estaligado());
  delay(1000);

  //pressao
  pressao = prs.get_val();
  Serial.println(pressao);
  delay(1000);
  //lcd.escreve(pressao);
  
  //temperatura
  temperatura = tmp.get_val();
  Serial.println(temperatura);
  delay(1000);

  //aceleração
  acel.get_val(&aclx, &acly, &aclz);
  Serial.println("Acel: ");
  Serial.println(aclx);
  lcd.escreve(aclx,acly,aclz, temperatura,pressao);
  delay(500);

  //bluetooth
  //bluetooth.escreve(swt.estaligado());
  micro.escreve(aclx,acly,aclz,temperatura, pressao);
  delay(500);
  micro.ler();
  delay(500);
  //Serial.print(led.estaligado());
  //led.ligar(true);
  //Serial.print(led.estaligado());
  
}
