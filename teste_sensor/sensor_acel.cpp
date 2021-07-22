#include <Arduino.h>
#include <Wire.h> //comunicação i2c

#include "sensor_acel.h"

Sensor_acel::Sensor_acel(){

}

void Sensor_acel::setp(){
    //Endereco I2C do MPU6050
//    Wire.begin();
//    Wire.beginTransmission(MPU);
//    Wire.write(0x6B); 
//    Wire.write(0); 
//    Wire.endTransmission(true);
    Serial.println("teste acel");
    if (!mpu.begin()) {
    Serial.println("MPU6050 nao encontrado");
    while (1) {
        delay(10);
    }
  }

};
void Sensor_acel::get_val(float *AcX, float *AcY, float *AcZ)
{
//    Wire.beginTransmission(MPU);
//    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
//    Wire.endTransmission(false);
//    //Solicita os dados do sensor
//    Wire.requestFrom(MPU,14,true);  
//    //Armazena o valor dos sensores nas variaveis correspondentes
//    *AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
//    *AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//    *AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  *AcX = a.acceleration.x;
  *AcY = a.acceleration.y;
  *AcZ = a.acceleration.z;
  Serial.println("Acceleration X: ");
  Serial.println(a.acceleration.x);
  Serial.println("Acceleration Y: ");
  Serial.println(a.acceleration.y);
  Serial.println("Acceleration Z: ");
  Serial.println(a.acceleration.z);
};

int Sensor_acel::estaligado(){
        return ligado;
}

void Sensor_acel::ligar(int controle){
        ligado = controle;
}
