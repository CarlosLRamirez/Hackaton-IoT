/*
Curso: Desarrollo de Prototipos para IoT
Autor: Carlos Ramirez (carloslrm@gmail.com)
Septiembre - 2017
===========================================

Leccion # 3 . Leyendo valores analogicos

Basado en codigo de Simon Monk
https://learn.adafruit.com/series/learn-arduino

*/

//en esta parte podemos inicializar variables
int pinPot=0;


// La rutina setup se ejecuta cuando encendemos el Arduino, 
// o presionamos el boton de reset:
void setup() {
  
  Serial.begin(9600); //inicializamos el puerto serial
}

//La rutina loop se ejecuta una y otra vez, de forma infinita:
void loop() {
  //leemos el valor analogico del pin A0 y lo guardamos en una variable 
  int lectura  = analogRead(pinPot); 
  //escribimos el valor de la variable en el puerto serial
  Serial.println(lectura);
  delay(500);
}




