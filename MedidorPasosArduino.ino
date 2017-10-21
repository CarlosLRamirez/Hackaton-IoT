
//Usamos el pin A0 como entrada analogica
int sensor =0;
int pico=0;
int slope=0;
int lectura1=0;
int lectura2=0;
int pico1=1024;
int pico2=0;
int margen_cambio=10;
int pico_max=0;
int borde = 0;
int pasos=0;
unsigned long t1=1024;
unsigned long t2=1024;
unsigned long periodo;

long freqpaso=0;

unsigned long tMensaje = 0;

long interval_pause = 5000; //10 segundos
long interval_mensaje =500; //1 segundo

// La rutina setup se ejecuta cuando encendemos el Arduino, 
// o presionamos el boton de reset:
void setup() {
  
  Serial.begin(9600); //inicializamos el puerto serial a 9600 baudrate

}

//La rutina loop se ejecuta una y otra vez, de forma infinita:
void loop() {


//Si han pasado mas de 30 segundos sin dar un paso, es porque esta parado
//La frecuencia de paso es 0 y reiniciamos los pasos
unsigned long currentMillis = millis();

if (currentMillis - t2 >= interval_pause){
    freqpaso=0;
    pasos=0;
}

if (currentMillis - tMensaje>=interval_mensaje){
    tMensaje = currentMillis;
    
    
      //char buf[50];
      //sprintf(buf, "%lu Pasos por minuto", freqpaso);
      //Serial.println(buf);
   

    Serial.println(String(pasos)+","+String(freqpaso));
    
    
    
    
}
 
  //leemos el sensor una vez
  lectura1=analogRead(sensor);
  delay(50);
  //leemos el sonesor otra vez
  lectura2  = analogRead(sensor); 

  //si la lectura actual es mayor que la lectura previa, significa que va cuesta arriba
  if (lectura2>lectura1){
    int cambio = lectura2-lectura1;
    if (cambio>=50) {
      slope=100;
      pico2=lectura2;
      borde=0;
    }
    
  }
  //si la lectura actual es menor que la lectura previa, significa que va cuesta abajo
  if (lectura2<lectura1){
    int cambio = lectura1 - lectura2;
    if (cambio>=50) {
      slope=-100;
      pico1=pico2;
      if (borde==0) {
        borde=1000; 
        pasos=pasos+1; 
        //Serial.println(pasos);
        t2=millis();
        periodo=t2-t1;
        t1=t2;

        freqpaso=(60000/periodo);
      

      }
     
    }
   }
    
  
  
  
  
}




