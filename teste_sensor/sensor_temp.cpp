#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#include "sensor_temp.h"

Sensor_temp::Sensor_temp(){
}


void Sensor_temp::setp(){
    Serial.println("setp temp");
    if (!bmp180.begin()) 
    {
        Serial.println("Sensor nao encontrado !!");
        while (1) {}
    }
}

float Sensor_temp::get_val(){
    return bmp180.readTemperature();
}

int Sensor_temp::estaligado(){
    return ligado;
}

void Sensor_temp::ligar(int controle){
    ligado = controle;
}
