/*
Curso: Desarrollo de Prototipos para IoT
Autor: Carlos Ramirez (carloslrm@gmail.com)
Septiembre - 2017
===========================================

Leccion # 7 . Sensor de Temperatura LM35 y TMP36

*/

//Usamos el pin A0 como entrada analogica que viene del sensor de temperatura
int pinSensor =0;

//utilice dcOffset = 0V para el sensor LM35 o 0.5V para el sensor TMP36
//float dcOffset=0.0;
float dcOffset=0.5;


// La rutina setup se ejecuta cuando encendemos el Arduino, 
// o presionamos el boton de reset:
void setup() {

  //analogReference(INTERNAL);
  Serial.begin(9600); //inicializamos el puerto serial a 9600 baudrate
  Serial.println("Aprendiendo Internet de las Cosas");
  Serial.println("Intecap - Centro Tics");
}

//La rutina loop se ejecuta una y otra vez, de forma infinita:
void loop() {
  //leemos el valor analogico del pin A0 y lo guardamos en una variable 
  int valorSensor  = analogRead(pinSensor); 
  
  //escribimos el valor leido por el sensor en el puerto serial
  Serial.print("Valor del Sensor: ");
  Serial.print(valorSensor);

  //Calculamos el voltaje y lo enviamos al puerto serial
  float voltaje = (valorSensor/1024.0) * 5.0 ;
  Serial.print(", Volts: ");
  Serial.print(voltaje);

  //Calculamos la temperatura y la enviamos al puerto serial
  float temperatura = (voltaje - dcOffset) * 100.0;
  Serial.print(", Temperatura en °C: ");

  //esperamos 2 segundos para volver a correr el ciclo
  delay(2000);
}




