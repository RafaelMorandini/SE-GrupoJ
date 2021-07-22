#include "lcd_real.h"


LCDReal::LCDReal(int rs, int en, int d4, int d5, int d6, int d7): lcd(rs, en, d4, d5, d6, d7)
{
  lcd.setCursor(0, 0);
  lcd.begin(20, 4);
  lcd.print("iniciando...");
}


void LCDReal::escreve(float acelx,float acely,float acelz,float pres,float temp)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aceleracao x:");
  lcd.print(acelx);
  lcd.setCursor(0, 1);
  lcd.print("Ay:");
  lcd.print(acely);
  lcd.print(" Az:");
  lcd.print(acelz);
  lcd.setCursor(0, 2);
  lcd.print("Pressao:");
  lcd.print(pres);
  lcd.setCursor(0, 3);
  lcd.print("Temperatura:");
  lcd.print(temp);
}

void LCDReal::apaga()
{
  lcd.clear();
}


/************************
  LCDReal::acionar
 Aciona ou desaciona o LCD
 entradas
   controle: TRUE:ligar FALSE:desligar
 saidas
   nenhuma
*************************/
void LCDReal::ligar(int controle)
{
    ligado = controle;
}

int LCDReal::estaligado()
{
    return ligado;
}
