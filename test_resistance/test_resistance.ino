#define Capteur_pp A0 // broche photorésistance

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(Capteur_pp);
  
  Serial.println("Analog  Value: ");
  Serial.println(value);

delay(250);
}
