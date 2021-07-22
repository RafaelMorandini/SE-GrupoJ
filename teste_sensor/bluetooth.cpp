#include <Arduino.h>
#include <SoftwareSerial.h>
#include "bluetooth.h"


Module_bluetooth::Module_bluetooth(int rx, int tx):module(rx,tx) {
}

void Module_bluetooth::setp() {
  module.begin(9600);
  module.write("init");
}

void Module_bluetooth::escreve(int dado) //dadoata: sinal a ser transmitido
{
  module.print("acel");
  module.println(dado); //printa no serial
}

void Module_bluetooth::ligar(int controle)
{
  ligado = controle;
}

int Module_bluetooth::estaligado()
{
  return ligado;
}
