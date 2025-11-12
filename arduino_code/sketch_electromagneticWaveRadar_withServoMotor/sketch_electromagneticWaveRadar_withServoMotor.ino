// aggiunita della Servo library
#include <Servo.h>

// nome dei pin della scheda Arduino utilizzati dal circuito
const int sensorPin = A0;
const int servoPin = 3;
const int LEDPin = 10;
 
// variabili dichiarate
int lightAmount = 0; // memorizza il valore analogico dal sensore di luce
int servoAngle = 0;
int inputCommand = 0;

Servo myServo;  // crea un oggetto servo

void setup() {
  // codice di installazione, eseguito una volta:

  pinMode(LEDPin, OUTPUT);

  // avvia il monitor seriale
  Serial.begin(9600);

  myServo.attach(servoPin);   // collega il servo sul pin 3 all'oggetto servo
  myServo.write(servoAngle);  // sposta il servo nella posizione iniziale
  delay(1000);

}

void loop() {
  // codice principale, eseguito ripetutamente:

  // controlla se ci sono dati nel buffer seriale
  if (Serial.available() > 0) {
    // legge il primo byte e cancella dal buffer
    inputCommand = Serial.read();

    switch (inputCommand){
      case '+':
      // aumenta l'angolo del servo di 10 gradi
      servoAngle = servoAngle + 10;
      // assicurarsi che l'angolo sia entro i limiti di 180 gradi del servo, altrimenti fai lampeggiare il LED blu come indicatore del limite
      if (servoAngle >= 180) {
        servoAngle = 180;
        digitalWrite(LEDPin, HIGH);
        delay(1000);
        digitalWrite(LEDPin, LOW);
      }
      break;
      case '-':
      // diminuisce l'angolo del servo di 10 gradi
      servoAngle = servoAngle - 10;
      // assicurarsi che l'angolo sia entro il limite minimo di 0 gradi del servo, altrimenti fai lampeggiare il LED blu come indicatore del limite
      if (servoAngle <= 0) {
        servoAngle = 0;
        digitalWrite(LEDPin, HIGH);
        delay(1000);
        digitalWrite(LEDPin, LOW);
      }
      break;
      // la variabile deve rimanere sempre all'interno dell'intervallo del servo (0-180 gradi)
    }

    // sposta il servo nell'angolo corretto
    myServo.write(servoAngle);
    delay(1000);

    // legge il sensore di luce e memorizza la misura in una variabile
    lightAmount = analogRead(sensorPin);

    Serial.print("Angle: ");
    Serial.print(servoAngle);
    Serial.print("     Light Intensity: ");
    Serial.println(lightAmount);
  }
}
