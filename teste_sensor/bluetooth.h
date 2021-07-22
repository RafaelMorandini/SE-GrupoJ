#ifndef BLUETOOTH
#define BLUETOOTH
#include <SoftwareSerial.h>

class Module_bluetooth {
   public:
   Module_bluetooth(int rx, int tx);
   SoftwareSerial module;
   void setp();
   void escreve(int dado); //dados vindo do sensor para ser passados via bluetooth
   void ligar(int controle);
   int estaligado();
   int ligado;
};

#endif
