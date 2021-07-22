#ifndef MICRO_SD_H_INCLUDED
#define MICRO_SD_H_INCLUDED

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#include "definicoes_sistema.h"

class Micro_SD{
  public:
    Micro_SD(int cs);
    File file;
    void setp();
    void escreve(float acelx,float acely,float acelz,float pres,float temp);
    void ler();
    void ligar(int controle);
    int estaligado();
    int CS;
    int ligado;
};

#endif // MICRO_SD_H_INCLUDED
