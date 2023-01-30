#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Max72xxPanel.h"
int pinCS = 10;
//Din conectado ao pino 11
//CLK conectado ao pino 13


int numberOfHorizontalDisplays = 2t ;
int numberOfVerticalDisplays = 1;


int thermistorPin = A0;
float R1 = 10000;
float R2, logR2, logR2Cube, tK, tC, tF;
float A = 9.76086e-04, B = 2.38890e-04, C = 2.27e-07;


Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);


int wait = 50;
int spacer = 1;
int width = 5 + spacer;


void setup() {
matrix.setIntensity(7);
matrix.setRotation(1, 2);
matrix.setRotation(3, 2);
}


void loop() {


int Vout = analogRead(thermistorPin);


R2 = R1 * (1023.0 / Vout - 1.0);
logR2 = log(R2);
logR2Cube = pow(logR2, 3);
tK = (1.0 / (A + B * logR2 + C * logR2Cube));
tC = tK - 273.15;
//tF = (tC * 9.0) / 5.0 + 32.0;


String tape = "Temp: " + String(tC) + " C";


for (int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {
matrix.fillScreen(LOW);


int letter = i / width;
int x = (matrix.width() - 1) - i % width;
int y = (matrix.height() - 8) / 2;

while ( x + width - spacer >= 0 && letter >= 0 ) {
  if ( letter < tape.length() ) {
    matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
  }

  letter--;
  x -= width;
}

matrix.write();
delay(wait);
}
}