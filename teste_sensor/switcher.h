#ifndef SWITCHER_H_INCLUDED
#define SWITCHER_H_INCLUDED

#include "definicoes_sistema.h"

class SWITCHER {
  public:
  SWITCHER(int pin);
  int pino;
  int estaligado();
  int ligado;
};

#endif // SWITCHER_H_INCLUDED
