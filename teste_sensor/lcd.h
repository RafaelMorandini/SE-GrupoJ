#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED


class LCD {
  public:
  virtual void escreve(float acelx,float acely,float acelz,float pres,float temp);

  virtual void ligar(int controle);

  
  int ligado = false;
};

#endif // LCD_H_INCLUDED
