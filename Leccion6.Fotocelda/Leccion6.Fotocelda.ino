/*
Curso: Desarrollo de Prototipos para IoT
Autor: Carlos Ramirez (carloslrm@gmail.com)
Septiembre - 2017
===========================================

Leccion # 6 . Fotocelda

*/

//Usamos el pin A0 como entrada analogica
int pinLuz =0;


// La rutina setup se ejecuta cuando encendemos el Arduino, 
// o presionamos el boton de reset:
void setup() {
  
  Serial.begin(9600); //inicializamos el puerto serial a 9600 baudrate
  Serial.println("Aprendiendo Internet de las Cosas");
  Serial.println("Intecap - Centro Tics");
}

//La rutina loop se ejecuta una y otra vez, de forma infinita:
void loop() {
  //leemos el valor analogico del pin A0 y lo guardamos en una variable 
  int lectura  = analogRead(pinLuz); 
  //escribimos el valor de la variable en el puerto serial
  Serial.print("Valor medido : ");
  Serial.print(lectura);

  float voltaje = (lectura/1024.0) * 5.0 ;
  Serial.print(", Volts: ");
  Serial.println(voltaje);
  
  delay(500);
}




