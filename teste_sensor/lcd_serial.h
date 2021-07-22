#ifndef LCD_SERIAL_H_INCLUDED
#define LCD_SERIAL_H_INCLUDED

#include "lcd.h"

class LCDSerial: public LCD {
  public:
    LCDSerial();
  	void escreve(char *msg);
  	void ligar(int controle);
    int estaligado();
    int ligado;
};


#endif // LCD_SERIAL_H_INCLUDED
