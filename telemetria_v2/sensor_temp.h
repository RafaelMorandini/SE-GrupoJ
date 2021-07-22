#ifndef SENSOR_TEMP_H_INCLUDED
#define SENSOR_TEMP_H_INCLUDED

#include "sensor.h"

class Sensor_temp: public Sensor{
    public:
    Sensor_temp();
    void setp();
    Adafruit_BMP085 bmp180;
    float get_val();
    void ligar(int controle);
    int estaligado();
    int ligado;
};
#endif
