/*
Curso: Desarrollo de Prototipos para IoT
Autor: Carlos Ramirez (carloslrm@gmail.com)
Septiembre - 2017
===========================================

Leccion # 4 . Puerto Serial Lectura/Escritura)

Basado en codigo de Simon Monk
https://learn.adafruit.com/series/learn-arduino

*/

//en esta inicializamos las variables
int pinLed1=8;
int pinLed2=9;
int pinLed3=10;

// La rutina setup se ejecuta cuando encendemos el Arduino, 
// o presionamos el boton de reset:
void setup() {
  //inicializamos los pines de LED como salidas
  pinMode(pinLed1,OUTPUT); 
  pinMode(pinLed2,OUTPUT); 
  pinMode(pinLed3,OUTPUT);


  //prueba inicial de los tres LEDS
  digitalWrite(pinLed1,HIGH);
  digitalWrite(pinLed2,HIGH);
  digitalWrite(pinLed3,HIGH);
  delay(1000);
  digitalWrite(pinLed1,LOW);
  digitalWrite(pinLed2,LOW);
  digitalWrite(pinLed3,LOW);
  delay(500);
  

  //inicializamos el puerto serial
  Serial.begin(9600); 
  //esperamos que este listo el puerto serial
  while (! Serial); 
    //escribimos en el puerto serial el mensaje inicial
    Serial.println("Ingrese el numero de LED del 1 al 3 o 'x' para apagarlo todo");
    
}

//La rutina loop se ejecuta una y otra vez, de forma infinita:
void loop() {
  if (Serial.available()) //confirma que este todo bien en el puerto serial
  {
    char ch = Serial.read(); //leemos un caracter del puerto serial
    if (ch >= '1' && ch <= '3') //si el caracter ingresado esta entre 1 y 3
    {
      
      cambiar(ch); //llamado a la funcion para cambiar el estado del led, pasando el valor del caracter como parametro
      Serial.print("Se cambio el estado del LED: "); //mensaje de confirmacion
      Serial.println(ch);
    }
    if (ch == 'x') //si el caracter es 'x'
    {
      limpiar(); //llamado a la funcion que apaga los tres LEDs     
      Serial.println("Todo Apagado"); //mensaje de confirmacion
    }
  }
}

//funcion que cambia el estado del led, recibe el numero de led como parametro
void cambiar(char led){
  switch (led) {
    case '1':
      digitalWrite(pinLed1, !digitalRead(pinLed1)); //cambiamos el estado del led, negando el estado actual
      break;
    case '2':
      digitalWrite(pinLed2, !digitalRead(pinLed2));
      break;
    default: 
      digitalWrite(pinLed3, !digitalRead(pinLed3));
      break;
    
  }
}

void limpiar(){
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
  digitalWrite(pinLed3, LOW);
       
}



