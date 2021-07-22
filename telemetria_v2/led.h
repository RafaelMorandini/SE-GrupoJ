#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED
#include <Arduino.h>

#include "definicoes_sistema.h"

class LED {
  public:
    LED(int pin);
    int pino;
    void ligar(int controle);
    int ligado;
    int estaligado();
};
#endif // LED_H_INCLUDED