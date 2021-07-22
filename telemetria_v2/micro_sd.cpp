#include "micro_sd.h"

Micro_SD::Micro_SD(int cs){
    CS = cs; 
    pinMode(CS, OUTPUT);
    
}
void Micro_SD::setp(){
    if (!SD.begin(CS)) { // Initialize SD card
        Serial.println("Could not initialize SD card."); // if return value is false, something went wrong.
    }
}

void Micro_SD::escreve(float acelx,float acely,float acelz,float pres,float temp){
    file = SD.open("file.txt", FILE_WRITE);
    file.print("acelx:");
    file.print(acelx, 4);
    file.print(",acely:");
    file.print(acely, 4);
    file.print(",acelz:");
    file.print(acelz, 4);
    file.print(",pres:");
    file.print(pres, 4);
    file.print(",temp:");
    file.println(temp, 4);
    file.close();
}
    
void Micro_SD::ler(){
    file = SD.open("file.txt", FILE_READ);
    char character;
    while ((character = file.read()) != -1) { 
        Serial.print(character);
    }
    file.close();
}

void Micro_SD::ligar(int controle)
{
    ligado = controle;
}

int Micro_SD::estaligado()
{
    return ligado;
}