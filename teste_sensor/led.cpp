#include <Arduino.h>

#include "definicoes_sistema.h"
#include "led.h"


LED::LED(int pin){
    pino = pin;
    pinMode(pino, OUTPUT);
}

void LED::ligar(int controle)
{
    ligado = controle;
    digitalWrite(pino,ligado);
};

int LED::estaligado()
{
    return ligado;
}