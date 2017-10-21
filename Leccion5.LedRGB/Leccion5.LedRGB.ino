/*
Curso Desarrollo de Prototipos para IoT
por Carlos Ramirez (carloslrm@gmail.com)
Septiembre - 2017
===============================================

basado en el codigo de Simon Monk
https://learn.adafruit.com/series/learn-arduino

Leccion # 5 . Led RGB

*/


int pinRojo = 11;
int pinVerde = 10;
int pinAzul = 9;
 
//descomente esta lina si utiliza LED de Anodo Comun
//#define ANODO_COMUN
 
void setup()
{
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);  
}
 
void loop()
{
  ponerColor(255, 0, 0);  // rojo
  delay(1000);
  ponerColor(0, 255, 0);  // verde
  delay(1000);
  ponerColor(0, 0, 255);  // azul
  delay(1000);
  ponerColor(255, 255, 0);  // amarillo
  delay(1000);  
  ponerColor(80, 0, 80);  // morado
  delay(1000);
  ponerColor(0, 255, 255);  // aqua
  delay(1000);
}
 
void ponerColor(int rojo, int verde, int azul)
{
  #ifdef ANODO_COMUN
    rojo = 255 - rojo;
    verde = 255 - verde;
    azul = 255 - azul;
  #endif
  analogWrite(pinRojo, rojo);
  analogWrite(pinVerde, verde);
  analogWrite(pinAzul, azul);  
}
