/*
  Curso: Desarrollo de Prototipos para IoT
  Autor: Carlos Ramirez (carloslrm@gmail.com)
  Septiembre - 2017
  ===========================================

  Lectura del Sensor de Temperatura LM35
  y envio por medio de HTTP Request (GET y POST)
  utilizando el ESP8266-01 y comandos AT

  Los datos son enviados con el siguiente formato:
  dato1=10.00&dato2=20.00...

*/

#include <SoftwareSerial.h>

//Usamos el pin A0 como entrada analogica que viene del sensor de temperatura
int pinSensor = 0;

//Led interno para control
int ledPin  = 13;

//datos del servidor web asi como el archivo php
String server = "iotstuff.000webhostapp.com";
String uri = "/colector_datos_json.php";

//Puerto serial por software en los pines 10 y 11
SoftwareSerial ser(10, 11); // RX, TX

//utilizar dcOffset = 0V para el sensor LM35
float dcOffset = 0.0;
//utilizar dcOffset = 0.5V para el sensor TMP36
//float dcOffset = 0.5;


// La rutina setup se ejecuta cuando encendemos el Arduino,
// o presionamos el boton de reset:
void setup() {

  Serial.begin(9600); //inicializamos el puerto serial a 9600 baudrate

  //led interno
  pinMode(ledPin, OUTPUT);

  //iniciamoos el puerto sofware serial en 9600,
  //este es el puerto por el que nos comunicamos con el ESP9266
  ser.begin(9600);

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
  float voltaje = (valorSensor / 1024.0) * 5.0 ;

  //calculamos la temperatura
  float temperatura = (voltaje - dcOffset) * 100.0;

  //Convertimos la temperatura a string
  char buf[16];
  String strTemp = dtostrf(temperatura, 4, 1, buf);

  //formateamos los datos antes de enviarlos
  String strData = "id=ArduinoPOST&temperatura=" + strTemp;

  //envio por el metodo POST
  httppost(server, uri, strData);
  delay(10000);

  //formateamos los datos antes de enviarlos
  strData = "id=ArduinoGET&temperatura=" + strTemp;

  //envio por el metodo GET
  httpget(server,uri,strData);
  delay(10000);
}




void httppost (String servidor, String colector, String data) {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += servidor;
  cmd += "\",80";
  ser.println(cmd);
  Serial.println("Estableciendo conexion TCP");
  delay(200);

  if ( ser.find("OK")) {
    Serial.println("ERROR EN LA CONEXION TCP: AT+CIPSTART error");
  }

  //preparamos el mensaje POST
  String postRequest =
    "POST " + colector + " HTTP/1.0\r\n" +
    "Host: " + servidor + "\r\n" +
    "Accept: *" + "/" + "*\r\n" +
    "Content-Length: " + data.length() + "\r\n" +
    "Content-Type: application/x-www-form-urlencoded\r\n" +
    "\r\n" + data;

  // Enviamos datos través del ESP8266
  // Primero determinamos la longitud del mensaje
  cmd = "AT+CIPSEND=";
  cmd += String(postRequest.length());
  ser.println(cmd);

  if (ser.find(">")) {
    ser.print(postRequest);
    Serial.print("Enviando...");
  } else {
    ser.println("AT+CIPCLOSE");
    Serial.println("No se pudo enviar el mensaje por TCP, cerrando conexion");
  }

  if (ser.find("SEND OK")) {
    Serial.println("Datos enviados exitosamente por HTTP POST");
  }
  while (ser.available()) {
    String tmpResp = ser.readString();
    Serial.println(tmpResp);
  }
  // close the connection
  ser.println("AT+CIPCLOSE");


}


void httpget (String servidor, String colector, String data) {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += servidor;
  cmd += "\",80";
  ser.println(cmd);
  Serial.println("Estableciendo conexion TCP");
  delay(200);

  if ( ser.find("OK")) {
    Serial.println("ERROR EN LA CONEXION TCP: AT+CIPSTART error");
  }

  String getRequest =
    "GET " + colector + "?" + data + " HTTP/1.0\r\n" +
    "Host: " + servidor + "\r\n" +
    "\r\n" + data;
  
  // Enviamos datos través del ESP8266
  // Primero determinamos la longitud del mensaje
  cmd = "AT+CIPSEND=";
  cmd += String(getRequest.length());
  ser.println(cmd);

  if (ser.find(">")) {
    ser.print(getRequest);
    Serial.print("Enviando...");
  } else {
    ser.println("AT+CIPCLOSE");
    Serial.println("No se pudo enviar el mensaje por TCP, cerrando conexion");
  }

  if (ser.find("SEND OK")) {
    Serial.println("Datos enviados exitosamente por HTTP GET");
  }
  while (ser.available()) {
    String tmpResp = ser.readString();
    Serial.println(tmpResp);
  }
  // close the connection
  ser.println("AT+CIPCLOSE");


}





