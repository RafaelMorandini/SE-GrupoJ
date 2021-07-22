#ifndef SENSOR_PRES_H_INCLUDED
#define SENSOR_PRES_H_INCLUDED

#include "sensor.h"

class Sensor_pres: public Sensor{
    public:
    Sensor_pres();
    Adafruit_BMP085 bmp180;
    void setp();
    float get_val();
    int ligado;
    void ligar(int controle);
    int estaligado();
    
};
#endif
