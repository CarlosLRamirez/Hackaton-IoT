/*
Curso: Desarrollo de Prototipos para IoT
Autor: Carlos Ramirez (carloslrm@gmail.com)
Septiembre - 2017
===========================================

Leccion # 2 . Boton pulsador y LEDs
*/


//En este espacio podemos inicializar variables
int pin_boton = 8;
int pin_ledrojo = 9;
int pin_ledverde = 10;

// La rutina setup se ejecuta cuando encendemos el Arduino, 
// o presionamos el boton de reset:
void setup() {
  // inicializa el pin del boton como ENTRADA con resistencia Pull-up interna
  pinMode(pin_boton, INPUT_PULLUP);
  // inicializa los pines para LED como SALIDAS
  pinMode(pin_ledrojo, OUTPUT);
  pinMode(pin_ledverde, OUTPUT);
}

//La rutina loop se ejecuta una y otra vez, de forma infinita:
void loop() {
  
  if (digitalRead(pin_boton) == LOW) //si esta presionado el pulsador, la entrada se lee como LOW 
  { 
  iniciar();  // ejecuta el codigo dentro de la funcion
  }
  if (digitalRead(pin_boton) == HIGH)  //si NO esta presionado el pulsador, la entrada se lee como HIGH 
  {
  apagar(); // ejecuta el codigo dentro de la funcion
  }
    
}

//funcion iniciar
void iniciar(){
  digitalWrite(pin_ledverde, HIGH);
  digitalWrite(pin_ledrojo,LOW);
  delay(1500);
  digitalWrite(pin_ledverde,LOW); 
  digitalWrite(pin_ledrojo, HIGH);
  delay(1500);
}

//funcion apagar
void apagar(){
  digitalWrite(pin_ledverde, LOW);
  digitalWrite(pin_ledrojo,LOW);
}

