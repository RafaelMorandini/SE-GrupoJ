#ifndef SENSOR_ACEL_H_INCLUDED
#define SENSOR_ACEL_H_INCLUDED

#include "sensor.h"

class Sensor_acel: public Sensor{
    public:
      Sensor_acel();
      void setp();
      void get_val(float *AcX, float *AcY, float *AcZ);
      int ligado;
      void ligar(int controle);
      int estaligado();
      const int MPU=0x68;
      Adafruit_MPU6050 mpu;
};
#endif
