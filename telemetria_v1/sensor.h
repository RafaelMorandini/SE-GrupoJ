#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>


#include <Adafruit_BMP085.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include "definicoes_sistema.h"

class Sensor{
    public:
        //virtual int ligado;
        virtual int estaligado();
        virtual void ligar(int controle);
};
#endif
