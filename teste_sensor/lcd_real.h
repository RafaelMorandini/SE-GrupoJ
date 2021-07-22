#ifndef LCD_REAL_H_INCLUDED
#define LCD_REAL_H_INCLUDED

#include <LiquidCrystal.h>
#include "lcd.h"

class LCDReal: public LCD{
  public:
    LCDReal(int rs, int en, int d4, int d5, int d6, int d7);
    LiquidCrystal lcd;
    void escreve(float acelx,float acely,float acelz,float pres,float temp);
    void ligar(int controle);
    int estaligado();
    int ligado;
};

#endif // LCD_REAL_H_INCLUDED
