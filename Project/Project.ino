//Programme de base pour P2

#include <Servo.h> //on importe la bibliothèque Servo
#define VERIN 9 // broche vérin
#define AVANCE 5   //Broche avance chariot
#define RECUL  6  // Broche recul chariot
#define LEDEVAC  13 // LED signalant évacuation en cours
#define FCM 8  // Broche fin de course côté moteur
#define FCA 7  // Broche fin de course côté Arduino
#define Capteur_pp A0 // broche photorésistance
#define TRIGGER_PIN 10
#define ECHO_PIN 11

#define intMA A2
#define intMdM A1
#define AxeX A3
#define AxeY A4
/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 34.0 / 1000; // en cm/us
const unsigned long MEASURE_TIMEOUT = 25000UL;
Servo LeVerin; // on définit un objet Servo nommé LeVerin


boolean X1=0, X2=0,X3=0,X4=0,X5=0,X6=0,X7=0, X8=0; // déclaration et initialisation de Xi
boolean X10=0,X11=0,X12=0,X13=0;
boolean X20=0,X21=0;
boolean X30=0,X31=0,X32=0,X33=0,X34=0,X35=0;
boolean X40=0,X41=0,X42=0,X43=0;
boolean X50=0,X51=0,X52=0, X53=0, X54=0, X55=0;
boolean X60=0,X61=0,X62=0;
boolean T1=0,T2=0,T3=0,T4=0,T5=0,T6=0,T7=0,T8=0,T9=0,T10=0,T11=0,T12=0, T20=0, T21=0;
boolean T30=0, T31=0, T32=0, T33=0, T34=0, T35=0;
boolean T40=0,T41=0,T42=0,T43=0,T44=0,T45=0;
boolean T50=0, T51=0, T52=0, T61=0, T62=0;
boolean arret=0, marche=0, autom=0, manu=0;
int VaxeX=0, VaxeY=0;
boolean fca=0,fcm=0;//variables booléennes fins de course
int pp, position; // valeur renvoyée par le photorésistance, valeur angulaire de la position du vérin, valeur saisie par l'opérateur
int verin_position = 1000;
long measure;// retour du capteur ultrason en micro_s
float distance_cm;// mesure du capteur ultrason en cm

void setup() {
  // Configurations (E/S, liaison série):
  Serial.begin(9600);
  
  LeVerin.attach(VERIN); // on relie l'objet au pin de commande
  
  // Ultrason
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
  
  // Motor
  pinMode(FCM, INPUT_PULLUP);
  pinMode(FCA, INPUT_PULLUP);
  pinMode(AVANCE, OUTPUT);
  pinMode(RECUL, OUTPUT);

  // Verin
  pinMode(VERIN, OUTPUT);
  LeVerin.writeMicroseconds(verin_position);

  // Led
  // pour l'alumée il fault l'envoyer HIGH
  pinMode(LEDEVAC, OUTPUT);

  // selecteurs
  pinMode(intMA, INPUT);
  pinMode(intMdM, INPUT);
  
// Initialisations (des sorties, du state diagram):
  X40=1; 
}

void loop() {

//1 lecture des entrées :
  // Ultrason
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  distance_cm = measure / 2.0 * SOUND_SPEED;
  
  // Fin de course
  fcm = digitalRead(FCM);
  fca = digitalRead(FCA);

  // Resistance
  pp = analogRead(Capteur_pp);

  //MA
  if (digitalRead(intMdM)){
    manu = 0;
    autom = 1;
  }
  else{
    manu = 1;
    autom = 0;
  }

  if (digitalRead(intMA)){
    arret = 0;
    marche = 1;
  }
  else{
    arret = 1;
    marche = 0;
  }
  
  VaxeX = analogRead(AxeX);
  VaxeY = analogRead(AxeY);

  // verin_position = read(LeVerin)
  
// Pour éventuellement debugger :

Serial.print("Presence pièce =");
Serial.println(pp);
Serial.print("fcm =");
Serial.println(fcm);
Serial.print("fca =");
Serial.println(fca);
Serial.print("distance =");
Serial.println(distance_cm);

// 1.3 calcul des conditions de transition : écrire les expressions logiques des conditions associées à chacune des transitions
T1 = (position != 0);
T2 = ((pp<250) && (35 < position || position < 7));
T3 = ((pp<250) && (36 > position && position > 6));
T4 = fca;
T5 = (distance_cm <= position);
T6 = X12;
T7 = fcm;
T10 = X5;
T11 = (pp>250);
T12 = fcm;
T20 = ((pp>250) && (X3 || X4));
T21 = fcm;
T30 = fca;
T31 = X33;
T32 = fcm;

//super etat
if(X40){X30=1;}
if(X40 && X35){X40=0; X41=1; X30=0; X31=0; X32=0; X33=0; X34=0; X35=0;}
if(X41 && marche && autom){X41=0; X42=1; X1=1; X10=1; X20=1; T1=0;}
if(X42 && arret && fcm){X42=0; X41=1; X1=0; X2=0; X3=0; X4=0; X5=0; X6=0; X10=0; X11=0; X12=0; X20=0; X21=0;}
if(X42 && manu){X42=0; X43=1; X50=1; X60=1; X1=0; X2=0; X3=0; X4=0; X5=0; X6=0; X10=0; X11=0; X12=0; X20=0; X21=0;}
if(X41 && manu){X41=0; X43=1; X50=1; X60=1;}
if(X43 && autom){X43=0; X40=1; X50=0; X51=0; X52=0; X60=0; X61=0; X62=0;}

// initilisation
if(X30){X30=0; X31=1; X32=1;}
if(X31 && fca){X31=0; X33=1;}
if(X32 && X33){X31=0; X32=0; X34=1;}
if(X33 && X34 && fcm){X31=0; X33=0; X34=0; X35=1;}
// if(X35){X35=0; X30=1;}

// automatique
if(X1 && T1){X1 = 0; X2 = 1;}
if(X2 && T2){X2 = 0; X3 = 1;}
if(X2 && T3){X2 = 0; X4 = 1;}
if(X3 && T4){X3 = 0; X5 = 1;}
if(X4 && T5){X4 = 0; X5 = 1;}
if(X5 && T6){X5 = 0; X6 = 1;}
if(X6 && T7){X6 = 0; X2 = 1;}
if(X10 && T10){X10 = 0; X11 = 1;}
if(X11 && T11){X11 = 0; X12 = 1;}
if(X12 && T12){X12 = 0; X10 = 1;}
if(X20 && T20){X20=0; X21 =1;}
if(X21 && T21){X20 = 1; X21 = 0;}

// manu
if(X50 && (VaxeY>=0 && VaxeY<=200)){X50=0; X51=1;}
if(X50 && (VaxeY>=900 && VaxeY<=1023)){X50=0; X52=1;}
if(X51 && (VaxeY>200 && VaxeY<900 || fca)){X51=0; X53=1;}
if(X52 && (VaxeY>200 && VaxeY<900 || fcm)){X52=0; X54=1;}
if(X53 || X54){X53=0; X54=0; X50=1;}

if(X60 && VaxeX>=900){X60=0; X61=1;}
if(X60 && VaxeX<=200){X60=0; X62=1;}
if(X61 && (VaxeX>200 && VaxeX<900)){X61=0; X60=1;}
if(X62 && (VaxeX>200 && VaxeX<900)){X62=0; X60=1;}


// 2 Formules d'évolution : pour chaque transitions de votre state diagram 
//A COMPLETER

// pour éventuellement debugger :

Serial.print("X40=   ");
Serial.println(X40);
Serial.print("X41=   ");
Serial.println(X41);
Serial.print("X42=   ");
Serial.println(X42);
Serial.print("X42=   ");
Serial.println(X42);
Serial.print("X43=   ");
Serial.println(X43);
Serial.print("marche=   ");
Serial.println(marche);
Serial.print("arret=   ");
Serial.println(arret);
Serial.print("autom=   ");
Serial.println(autom);
Serial.print("manu=   ");
Serial.println(manu);
Serial.print("VaxeX=   ");
Serial.println(VaxeX);
Serial.print("VaxeY=   ");
Serial.println(VaxeY);


// 3 Ecriture sorties
 // Chaque sortie doit être traitée en une fois : pour chaque sortie écrire l'ensemble des ses conditions d'activation
 // Pour la LED et les mouvements du chariot ne pas oublier d'indiquer que si la condition n'est pas satisfaite le mouvement doit s'arrêter 
 // Pour gérer les sorties agir directement sur les broches correspondantes

 // Gestion de la sortir : Saisir Position Evacuation
 if (X1)            // on ne fait la lecture du caractère que lorsque l'on est en situation éta1 1 actif
 {    
    Serial.println("entrez la position d evacuation voulue  en cm");
    if (Serial.available()>0){  
          position= Serial.parseInt();
    } 
       // on a une distance en cm ok
 }
 //Autres sorties 
if (X3 || X4 || X31 || X51)
  analogWrite(AVANCE, 80); else analogWrite(AVANCE, 0);
  
if (X5)
  digitalWrite(LEDEVAC, HIGH); else digitalWrite(LEDEVAC, LOW);

if(X6 || X33 || X52)
  analogWrite(RECUL, 80); else digitalWrite(RECUL, 0);

if(X11 || X32 || X61)
  LeVerin.writeMicroseconds(2000);

if(X12 || X34 || X62)
  LeVerin.writeMicroseconds(1000);

if(X21)
  Serial.println("PERTE PIÈCE");

}
