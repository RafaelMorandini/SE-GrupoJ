#ifndef SENSOR_ACEL_H_INCLUDED
#define SENSOR_ACEL_H_INCLUDED

#include "sensor.h"

class Sensor_acel: public Sensor{
    public:
      Sensor_acel();
      void setp();
      void get_val();
      float get_valx();
      float get_valy();
      float get_valz();
      int ligado;
      void ligar(int controle);
      int estaligado();
      const int MPU=0x68;
      Adafruit_MPU6050 mpu;
      sensors_event_t a, g, temp;
};
#endif
