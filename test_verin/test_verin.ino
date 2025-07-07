#include <Servo.h> //on importe la bibliothèque Servo

#define VERIN 9 // broche vérin

Servo LeVerin; // on définit un objet Servo nommé LeVerin

int angle;

void setup() {
  pinMode(VERIN, OUTPUT);
  LeVerin.attach(VERIN); // on relie l'objet au pin de commande
  LeVerin.writeMicroseconds(1000);
  delay(1000);
  Serial.begin(9600);
}

void loop() {
  LeVerin.writeMicroseconds(2000);
  delay(4000);
  LeVerin.writeMicroseconds(1000);
  delay(4000);
}
