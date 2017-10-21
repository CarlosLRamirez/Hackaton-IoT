/*
Curso: Desarrollo de Prototipos para IoT
Autor: Carlos Ramirez (carloslrm@gmail.com)
Septiembre - 2017
===========================================

Leccion # 1 - Hola Mundo

*/


// La rutina setup se ejecuta cuando encendemos el Arduino, 
// o presionamos el boton de reset:
void setup() {
  // inicializa el pin 10 como SALIDA (OUTPUT)
  pinMode(10, OUTPUT);
}

//La rutina loop se ejecuta una y otra vez, de forma infinita:
void loop() {
  digitalWrite(10, HIGH);   // Enciente el LED (voltaje HIGH)
  delay(1000);               // espera un segundo
  digitalWrite(10, LOW);    // Apaga el LED (voltaje LOW)
  delay(1000);               // espera un segundo
}
