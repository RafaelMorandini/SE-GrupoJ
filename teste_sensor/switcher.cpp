#include <Arduino.h>

#include "definicoes_sistema.h"
#include "switcher.h"


SWITCHER::SWITCHER(int pin){
  pino = pin;
  pinMode(pino, INPUT);
};

int SWITCHER::estaligado(){
  ligado = digitalRead(pino);
  return ligado;
};
