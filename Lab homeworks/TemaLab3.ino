
const int potPinRed=A0;
const int potPinGreen=A1;
const int potPinBlue=A2;
const int redPin=11;
const int greenPin=10;
const int bluePin=9;

int potValueRed=0;
int potValueGreen=0;
int potValueBlue=0;
int ledValueRed=0;
int ledValueGreen=0;
int ledValueBlue=0;

void setup() {
  pinMode(potPinRed, INPUT);
  pinMode(potPinGreen, INPUT);
  pinMode(potPinBlue, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  potValueRed=analogRead(potPinRed);
  ledValueRed=map(potValueRed,0,1023,0,255);
  analogWrite(redPin,ledValueRed);
  potValueGreen=analogRead(potPinGreen);
  ledValueGreen=map(potValueGreen,0,1023,0,255);
  analogWrite(greenPin,ledValueGreen);
  potValueBlue=analogRead(potPinBlue);
  ledValueBlue=map(potValueBlue,0,1023,0,255);
  analogWrite(bluePin,ledValueBlue);
}
