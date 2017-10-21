/*
Curso: Desarrollo de Prototipos para IoT
Autor: Carlos Ramirez (carloslrm@gmail.com)
Septiembre - 2017
===========================================

Leccion # 8 . Sensor Ultrasonica HC-SR04

Uso de la libreria NewPing

*/

#include <NewPing.h>
 
#define PIN_DISPARO  8
#define PIN_RESPUESTA     9
#define DISTANCIA_MAX 200
 
NewPing sonar(PIN_DISPARO, PIN_RESPUESTA, DISTANCIA_MAX);
 
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  delay(50);
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
}


