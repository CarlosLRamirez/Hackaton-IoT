/*
  Curso: Desarrollo de Prototipos para IoT
  Autor: Carlos Ramirez (carloslrm@gmail.com)
  Septiembre - 2017
  ===========================================

  Leccion # 9 . Pantalla LCD

*/

#include <LiquidCrystal.h>


// Construmios un elemento lcd asociando los pines de la pantalla LCD con los
// pines donde la tenemos conectada en el Arduino
const int rs = 8, en = 9, d4 = 3, d5 = 2, d6 = 1, d7 = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Inicializamos la pantalla indicando el numero de filas y columnas, en este caso 16x2
  lcd.begin(16, 2);

  // Imprimimos un mensaje en la pantalla

  lcd.setCursor(0, 0);
  lcd.print("INTECAP");
  delay(500);
  lcd.setCursor(0, 1);

  lcd.print("#tumejorversion");
  delay(2000);

}



void loop() {

  //En este ciclo, corremos el texto en 8 posiciones hacia la derecha
  for (int positionCounter = 0; positionCounter < 8; positionCounter++) {
    // Corremos el texto una posicion a la derecha
    lcd.scrollDisplayRight();
    //esperamos un poco
    delay(500);
  }


  //En este ciclo, corremos el texto en 8 posiciones hacia la izquierda
  for (int positionCounter = 0; positionCounter < 8; positionCounter++) {
    //Corremos el texto una posicion a la izquierda
    lcd.scrollDisplayLeft();
    //esperamos un poco
    delay(500);
  }


  //hacemos una espera de 1 segundo al final del loop
  delay(1000);



}














