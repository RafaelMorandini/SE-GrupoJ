#include "sensor_pres.h"

Sensor_pres::Sensor_pres(){
}


void Sensor_pres::setp(){
    if (!bmp180.begin())
    {
        Serial.println("Sensor nao encontrado !!");
        while (1) {}
    }
}
float Sensor_pres::get_val(){
    return bmp180.readPressure();
}

int Sensor_pres::estaligado(){
        return ligado;
}

void Sensor_pres::ligar(int controle){
        ligado = controle;
}
