//dodanie potrzebnych bibliotek
#include <PinChangeInterrupt.h>
#include <LowPower.h>

//definiowanie nazw pinow
#define laserPin 2
#define fotoResPin A5

volatile byte laserInpulse = 0; //nalicza ilosc sygnalow lasera

void setup() {
  //ustawianie trybow kazdego z uzywanych pinow
  pinMode(laserPin, OUTPUT);  
  pinMode(fotoResPin, INPUT);

  digitalWrite(laserPin, HIGH); //aktywacja lasera

  //ustawienie przerwania dla fotorezystora
  attachPCINT(digitalPinToPCINT(fotoResPin), laserOnOff, RISING);
}

void loop() {
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); //wejscie Arduino w stan uspienia, do czasu wystapienia przerwania
  
  delay(1000); //czeka na naliczenie sygnalow
  if(laserInpulse == 3)
    digitalWrite(laserPin, LOW); //aktywuje laser
  else if(laserInpulse == 5)
    digitalWrite(laserPin, HIGH); //dezaktywuje laser
  laserInpulse = 0; //zeruje ilosc naliczonych impulsow lasera
}

void laserOnOff(){
  ++laserInpulse; //nalicza kazdy impuls
}
