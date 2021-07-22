#ifndef BLUETOOTH_H_INCLUDED
#define BLUETOOTH_H_INCLUDED

#include <Arduino.h>
#include <SoftwareSerial.h>

class Module_bluetooth {
   public:
   Module_bluetooth(int rx, int tx);
   SoftwareSerial module;
   void setp();
   void escreve(float acelx,float acely,float acelz,float pres,float temp); //dados vindo do sensor para ser passados via bluetooth
   void ligar(int controle);
   int estaligado();
   int ligado;
};

#endif  //BLUETOOTH_H_INCLUDED
