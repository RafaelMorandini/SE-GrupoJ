#include "sensor_acel.h"

Sensor_acel::Sensor_acel(){

}

void Sensor_acel::setp(){
    Serial.println("teste acel");
    if (!mpu.begin()) {
        Serial.println("MPU6050 nao encontrado");
        while (1) {
            delay(10);
        }
    }

};
void Sensor_acel::get_val()
{
  mpu.getEvent(&a, &g, &temp);
};

float Sensor_acel::get_valx()
{
  return a.acceleration.x;
};

float Sensor_acel::get_valy()
{
  return a.acceleration.y;
};

float Sensor_acel::get_valz()
{
  return a.acceleration.z;
};

int Sensor_acel::estaligado(){
        return ligado;
}

void Sensor_acel::ligar(int controle){
        ligado = controle;
}
