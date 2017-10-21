/*
Curso: Desarrollo de Prototipos para IoT
Autor: Carlos Ramirez (carloslrm@gmail.com)
Septiembre - 2017
===========================================

Sensor de Temperatura LM35 (o TMP36) y envio por protocolo TCP
utilizando ESP8266 y comandos AT

*/

#include <SoftwareSerial.h>

//Usamos el pin A0 como entrada analogica que viene del sensor de temperatura
int pinSensor =0;

//Led interno para control
int ledPin  = 13;

//direccion ip y puerto del servidor TCP (tambien se puede poner la url en lugar de la IP)
String tcp_server = "tcp.acifuina.com";
String tcp_port = "3150";

//Puerto serial por software en los pines 10 y 11
SoftwareSerial ser(10, 11); // RX, TX

//utilizar dcOffset = 0V para el sensor LM35 
//float dcOffset=0.0;
//utilizar dcOffset = 0.5V para el sensor TMP36
float dcOffset=0.5;


// La rutina setup se ejecuta cuando encendemos el Arduino, 
// o presionamos el boton de reset:
void setup() {

  //analogReference(INTERNAL);
  Serial.begin(9600); //inicializamos el puerto serial a 9600 baudrate
  Serial.println("Aprendiendo Internet de las Cosas");
  Serial.println("Intecap - Centro Tics");

  pinMode(ledPin, OUTPUT);    
  //iniciamoos el puerto sofware serial en 9600, 
  //este es el puerto por el que nos comunicamos con el ESP9266
  ser.begin(115200);
  
  //reiniciamos el modulo ESP8266
  ser.println("AT+RST");

}

//La rutina loop se ejecuta una y otra vez, de forma infinita:
void loop() {

  //Blink en el led interno para verificar que el programa esta corriendo
  digitalWrite(ledPin, HIGH);   
  delay(100);               
  digitalWrite(ledPin, LOW);
  
  //leemos el valor analogico del pin A0 y lo guardamos en una variable 
  int valorSensor  = analogRead(pinSensor); 

  //calculamos el voltaje
  float voltaje = (valorSensor/1024.0) * 5.0 ;
  
  //calculamos la temperatura
  float temperatura = (voltaje - dcOffset) * 100.0;

  //Convertimos la temperatura a string
  char buf[16];
  String strTemp = dtostrf(temperatura, 4, 1, buf);
  Serial.println(strTemp);

   // Conexión TCP/IP
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += tcp_server;
  cmd += "\","+ tcp_port ;
  ser.println(cmd);
  Serial.println(cmd);

  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }

  // Enviamos data a través del ESP8266
  cmd = "AT+CIPSEND=";
  
  //Enviamos el dato en forma estructurada usando json
  String json_temp = ("{\"ID\":1,\"temp\":" + strTemp + "}\n");
  cmd += String(json_temp.length());
  Serial.println(json_temp);
  Serial.println ("comando enviado: "+cmd);
  ser.println(cmd);
 
  if(ser.find(">")){
    ser.print(json_temp);
  }
  else{
    ser.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE");
  }
  

  delay(3000);
}




