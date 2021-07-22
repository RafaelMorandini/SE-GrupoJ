#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#include "sensor_pres.h"

Sensor_pres::Sensor_pres(){
}


void Sensor_pres::setp(){
    Serial.println("setp pres");
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
