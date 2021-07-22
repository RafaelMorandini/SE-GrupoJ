#include "bluetooth.h"


Module_bluetooth::Module_bluetooth(int rx, int tx):module(rx,tx) {
}

void Module_bluetooth::setp() {
  module.begin(9600);
  module.write("init");
}

void Module_bluetooth::escreve(float acelx,float acely,float acelz,float pres,float temp) //dadoata: sinal a ser transmitido
{
  module.print("ax:");
  module.print(acelx);
  module.print(",ay:");
  module.print(acely);
  module.print(",az:");
  module.print(acelz);
  module.print(",pres:");
  module.print(pres);
  module.print(",temp:");
  module.println(temp); //printa no serial
}

void Module_bluetooth::ligar(int controle)
{
  ligado = controle;
}

int Module_bluetooth::estaligado()
{
  return ligado;
}
