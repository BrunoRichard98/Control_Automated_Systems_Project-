#include <Servo.h> //on importe la bibliothèque Servo

#define FCM 8  // Broche fin de course côté moteur
#define FCA 7  // Broche fin de course côté Arduino
#define AVANCE 5   //Broche avance chariot
#define RECUL  6  // Broche recul chariot


boolean avancerChariot;
boolean fcm, fca = 1;

Servo LeVerin; // on définit un objet Servo nommé LeVerin

void setup() {
  pinMode(FCM, INPUT_PULLUP);
  pinMode(FCA, INPUT_PULLUP);

  pinMode(AVANCE, OUTPUT);
  pinMode(RECUL, OUTPUT);

  LeVerin.attach(VERIN); // on relie l'objet au pin de commande
  Serial.begin(9600);
}

void loop() {
  fcm = digitalRead(FCM);
  fca = digitalRead(FCA);
  delay(10);
  Serial.print("fcm=    ");
  Serial.println(fcm);
  Serial.print("fca=    ");
  Serial.println(fca);

  if(fcm) avancerChariot = 1;
  if(fca) avancerChariot = 0;
  
  if(avancerChariot){
    analogWrite(AVANCE, 255);
    analogWrite(RECUL, 0);
  }
  else{
    analogWrite(RECUL, 255);
    analogWrite(AVANCE, 0);
  }
}
