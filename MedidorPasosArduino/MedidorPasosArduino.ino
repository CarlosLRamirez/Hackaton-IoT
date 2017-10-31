/*
Autor: Carlos Ramirez (carloslrm@gmail.com)
Septiembre - 2017
===========================================

Programa para contar pasos con un sensor de presion, y calcular la frecuencia de pasos.

*/

//Usamos el pin A0 como entrada analogica para el sensor de presión
int sensor = 0;

//variable para ir guardando el ultimo  valor pico de la señal medida con el sensor de presion
int pico1 = 1024;

//variable para ir guardando el pico instantaneo, si en la cresta positiva de la señal, pico2
//es menor que pico1, entonces pico1 se reduce al valor de pico2
int pico2 = 0;

//variable para guardar si la señal va cuesta arriba (slope=100) o cuesta abajo (slope=-100)
int slope = 0;

//variables para guardar las lecturas instantaneas del sensor de presion
int lectura1 = 0;
int lectura2 = 0;

//setear el % de la señal que detectaría como cambio
//aún no utilizada
int margen_cambio = 10;

//para guardar el borde negativo, es decir el instante en que la señal tiene una cresta
int borde = 0;

//levar la cuenta de los pasos
int pasos = 0;

//variables para llevar los insantes los entre una cresta y otra
unsigned long t1 = 1024;
unsigned long t2 = 1024;

//llevar el tiempo que transcurre entre t1 y t2
unsigned long periodo;

//variable para ir guardando la frecuencia de paso (inverso al periodo)
long freqpaso = 0;

//intervalo de tiempo que toma como estado de reposo (no está corriendo)
long interval_pause = 5000; //10 segundos

//instante de tiempo que envio el ultimo mensaje
unsigned long tMensaje = 0;

//intervalo de tiempo para enviar los mensajes por el puerto serial
long interval_mensaje = 50; //1 segundo

void setup()
{

  Serial.begin(9600); //inicializamos el puerto serial a 9600 baudrate
}

void loop()
{

  //leemos el sensor una vez
  lectura1 = analogRead(sensor);
  //esperamos un tiempo entre lecturas para no leer rebotes
  delay(10);
  //leemos el sonesor otra vez
  lectura2 = analogRead(sensor);

  //si la lectura actual es mayor que la lectura previa, significa que la señal va cuesta arriba
  if (lectura2 > lectura1)
  {
    //solo detectamos el cambio si este es mayor a 50 unidades 
    int cambio = lectura2 - lectura1;
    if (cambio >= 50)
    {
      slope = 100;
      //mientras la señal vaya subiendo el pico2 va ir siguiendo la señal
      pico2 = lectura2;
      //mientras la señal vaya subiendo, el borde es 0
      borde = 0;
    }
  }

  //si la lectura actual es menor que la lectura previa, significa que va cuesta abajo
  if (lectura2 < lectura1)
  {
    //solo detectamos el cambio si este es mayor a 50 unidades 
    int cambio = lectura1 - lectura2;
    if (cambio >= 50)
    {
      slope = -100;
      //el pico1 va ser igual al ultimo valor pico medido cuando la señal venía subiendo
      pico1 = pico2;
      //si el borde es igual a 0 cuando ya viene bajando, significa que estamos en la cresta de la señal
      //por lo tanto aumentamos los pasos en 1 y guardamos el tiempo en t2
      if (borde == 0)
      {
        
        borde = 1000;
        pasos = pasos + 1;
        t2 = millis();
        //perido es el tiempo transcurrido entre el t1 (tiempo anterior) y t2(tiempo actual) 
        periodo = t2 - t1;
        //al salir, t1 toma el valor de t2
        t1 = t2;

        //frequiencia de paso en pasos por minuto
        freqpaso = (60000 / periodo);
      }
    }
  }

  //Si han pasado mas de "interval_pause" milisegundos sin dar un paso, es porque no esta corriendo
  //La frecuencia de paso es 0 y reiniciamos los pasos a 0
  unsigned long currentMillis = millis();

  if (currentMillis - t2 >= interval_pause)
  {
    freqpaso = 0;
    pasos = 0;
  }

  //enviamos cada "tMensaje" milisegundos los datos por el puerto serial
  if (currentMillis - tMensaje >= interval_mensaje)
  {
    tMensaje = currentMillis;

    //char buf[50];
    //sprintf(buf, "%lu Pasos por minuto", freqpaso);
    //Serial.println(buf);

      Serial.println(String(lectura1) + "," + String(lectura2));
  }
}
