#include <Arduino.h>

#include "definicoes_sistema.h"
#include "lcd_serial.h"

LCDSerial::LCDSerial() : ligado(false)
{
}

void LCDSerial::escreve(char *msg)
{
  Serial.println(msg);
}

/************************
  LCDSerial::acionar
 Aciona ou desaciona o LCD
 entradas
   controle: TRUE:ligar FALSE:desligar
 saidas
   nenhuma
*************************/
void LCDSerial::ligar(int controle)
{
    ligado = controle;
}

int LCDSerial::estaligado()
{
    return ligado;
}
