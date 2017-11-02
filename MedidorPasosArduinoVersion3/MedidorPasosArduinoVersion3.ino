/*
Autor: Carlos Ramirez (carloslrm@gmail.com)
Septiembre - 2017
===========================================

Programa para contar pasos con un sensor de presion, y calcular la frecuencia de pasos.

*/

#define DEBUG true
#include <SoftwareSerial.h>

//aqui es donde conectamos el tx y rx del esp-01
SoftwareSerial esp(10, 11); // RX, TX

//informacion del Wifi
String wifiSSID = "thisphone";
String wifiPass = "TheLastJedi";

// servidor web y archivo php colector
//String http_server = "iotstuff.000webhostapp.com";
//String http_port = "80";
//String uri = "/colector_datos_json.php";

String http_server = "192.168.43.187";
String http_port = "1880";
String uri = "/home";



//definición de pinout
int sensorPie1 = 0;
int sensorPie2 = 1;
int ledPie1=2;
int ledPie2=3;
int ledFlote=4;

//punto medio de la lectura de los sensores (calibracion)
//zapatos: 720 y 750
int midSensor1=170;
int midSensor2=140;

int lectura1;
int lectura2;


//Control de pasos
int cuentaPasos = 0; //contador de pasos
long freqPaso = 0; //frecuencia de pasos (pasos por minuto)
int con1Paso=0; //punto de control1
int con2Paso=0; //punto de control2
int cambioPie1 = 0;
int cambioPie2 = 0;

//Control de flotación
int cuentaFlote = 0; //contador de flotacion
long freqFlote =0;
int con1Flote=0; //punto de control1 flotacion
int con2Flote=0; //punto de control2 flotacion
int cambioFlote = 0;

//Control de pie en aire
boolean airePie1 =false;
boolean airePie2 =false;

int controlActividad = 0;

//variable de control
unsigned long t2 = 0;

//VARIABLES PARA CONTROLAR TIEMPOS DE LOS EVENTOS//
//===============================================//

//Evento de Pausa Automatica
//intervalo de tiempo que toma como estado de reposo (no está corriendo)
unsigned long interval_pause =25; //en segundos

//Evento enviar Mensaje 1: "cuenta de pasos & cuenta de flotes"
long intMensaje1 = 2000; //cada cuanto enviar el mensaje  millisegundos
unsigned long tMensaje1 = 0; //variable de control
boolean msg1=false;

//Evento enviar Mensaje 2: "
//pasos de control & flote de control & frecuencia pasos & frecuencia flote
long intCalculosFreq = 10000; //cada cuanto enviar el mensaje en millisengundos
unsigned long tCalculosFreq = 0;
boolean msg2=false;


void setup()
{
  pinMode(ledPie1,OUTPUT);
  pinMode(ledPie2,OUTPUT);
  pinMode(ledFlote,OUTPUT);

  checkLeds();

  t2=millis();

  Serial.begin(9600); //inicializamos el puerto serial a 9600 baudrate
  esp.begin(9600);

  //reiniciar el ESP-01
  sendData("AT+RST\"\r\n",5000,DEBUG);
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); //poner ESP-01 en modo cliente&AP
  sendData("AT+CWJAP=\""+wifiSSID+"\",\""+wifiPass+"\"\r\n",8000,DEBUG); //conectarWifi
  sendData("AT+CIFSR\r\n",1000, DEBUG);//obtenerIP

  connect_tcp(http_server,http_port);
  sendData("AT+CIPMODE=1\r\n",500, DEBUG);//obtenerIP
  sendData("AT+CIPSEND\r\n",500, DEBUG);//obtenerIP



}



void loop()
{


  leer_sensores();

  //variable para llevar la cuenta del tiempo transcurrido desde
  //que inició el programa
  unsigned long currentMillis = millis();


  //Evento: PAUSA AUTOMATICA
  //luego de pasado cierto tiempo sin contar pasos, reinicia todo y envia mensaje
  //de pausa automatica

  if (currentMillis - t2 >= (interval_pause*1000))
  {
    controlActividad = 0;
    cuentaPasos = 0;
    freqPaso = 0;
    freqFlote = 0;
    cuentaFlote = 0;
    //Serial.println("pausa automatica");
  }

  //Evento: calcular frecuencias de paso y de flote
  //cada intCalculosFreq milisegundos
  if (currentMillis - tCalculosFreq >= intCalculosFreq)
  {

     //calcular frecuencia paso, y frecuencia flote
     float segundos= (currentMillis - tCalculosFreq )/1000.00;

     con2Paso=cuentaPasos;
     int pasos_intervalo=con2Paso-con1Paso;
     con1Paso=con2Paso;

     con2Flote=cuentaFlote;
     int flote_intervalo=con2Flote-con1Flote;
     con1Flote=con2Flote;

     freqPaso=60*(pasos_intervalo/segundos);
     freqFlote=60*(flote_intervalo/segundos);


     tCalculosFreq = currentMillis;


  }

  //Evento: enviar Mensaje1
  //cada intMensaje1 milisegundos
  //este es mas seguido que el otro
  if     (currentMillis - tMensaje1 >= intMensaje1)    {

     //ejemplo: "controlActividad=1&cuentaPasos=10&cuentaFlote=5"
     String msg = "controlActividad=";
     msg+=controlActividad;
     msg+= "&cuentaPasos=";
     msg+=cuentaPasos;
     msg+= "&cuentaFlote=";
     msg+=cuentaFlote;
     //"controlPasos&freqPasos&controlFlote&freqFlote"
     msg+= "&freqPasos=";
     msg+=freqPaso;
     msg+= "&freqFlote=";
     msg+=freqFlote;

     Serial.println(msg);
     GET_UART(http_server,uri,msg);

     tMensaje1 = currentMillis;

  }


}


String connect_tcp(String s, String p)
{
    //iniciar conexion TCP
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += s;
    cmd += "\"," + p;
    cmd += "\r\n";
    String returns = sendData(cmd,1000,DEBUG);
    return returns;
}

void POST_UART(String servidor, String colector, String data){

  //preparamos el mensaje POST
  String request =
    "POST " + colector + " HTTP/1.0\r\n" +
    "Host: " + servidor + "\r\n" +
    "Accept: *" + "/" + "*\r\n" +
    "Content-Length: " + data.length() + "\r\n" +
    "Content-Type: application/x-www-form-urlencoded\r\n" +
    "\r\n" + data;

  esp.print(request);
}


void GET_UART(String servidor, String colector, String data){

  String request =
  "GET " + colector + "?" + data + " HTTP/1.1\r\n" +
  "Host: " + servidor + "\r\n" +
  "\r\n";

  esp.print(request);


}
/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
Thanks to : http://fab.cba.mit.edu/classes/865.15/people/dan.chen/esp8266/
*/

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";

    esp.print(command); // send the read character to the esp8266

    long int time = millis();

    while ((time + timeout) > millis())
    {
        while (esp.available())
        {

            // The esp has data so display its output to the serial window
            char c = esp.read(); // read the next character.
            response += c;
        }
    }

    if (debug)
    {
        Serial.println(response);
    }

    return response;
}

void checkLeds(){
  //chequeo de los LEDs
  digitalWrite(ledPie1,HIGH);
  digitalWrite(ledPie2,HIGH);
  digitalWrite(ledFlote,HIGH);
  delay(500);
  digitalWrite(ledPie1,LOW);
  digitalWrite(ledPie2,LOW);
  digitalWrite(ledFlote,LOW);
}

void leer_sensores(){

  //leemos el sensor del pie1
  lectura1 = analogRead(sensorPie1);
  //delay para estabilidad
  delay(10);
  //leemos el sensor del pie2
  lectura2 = analogRead(sensorPie2);

  //Verificar si tiene el Pie1 en el suelo
  if (lectura1>=midSensor1) {
    airePie1=false; //pie en el suelo
    digitalWrite(ledPie1,HIGH);
    //si el pie esta en el suelo, aumenta los pasos unas sola vez
    if (cambioPie1==0){
      cambioPie1=1;
      cuentaPasos+=1;
      t2=millis();
      controlActividad=1;
    }
  }
  //el Pie1 esta en el aire
  else {
    digitalWrite(ledPie1,LOW);
    airePie1=true;//pie en el aire
    cambioPie1=0;
  }

  //Verificar si tiene el Pie2 en el suelo
  if (lectura2>=midSensor2) {
    airePie2=false;//pie en el suelo
    digitalWrite(ledPie2,HIGH);
    if (cambioPie2==0){
      cambioPie2=1;
      cuentaPasos+=1;
      t2=millis();
      controlActividad=1;
    }
  }
  else {
    digitalWrite(ledPie2,LOW);
    airePie2=true; //pie en el aire
    cambioPie2=0;
  }

  //ver si tiene ambos pies en el Aire
  if (airePie1&&airePie2){
    digitalWrite(ledFlote,HIGH);
    //aumenta el contador de flotes solo una vez
    if (cambioFlote==0){
      cuentaFlote+=1;
      cambioFlote=1;

    }
  } else{
    digitalWrite(ledFlote,LOW);
    cambioFlote=0;

}

}
