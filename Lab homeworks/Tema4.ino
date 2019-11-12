
const int detectorPin = A2;
const int buzzerPin = 11;
const int buttonPin = 2;

int buzzerTone = 1000;

int knockValue = 0;
int treshold = 100;
int switchVal = 0;

bool alarm = false;

int period = 5000;
unsigned long time_now = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  knockValue = analogRead(detectorPin);
  if(knockValue >= treshold){
    alarm = true;
  }
  if(alarm == true){
    if(millis() > time_now + period){
      time_now = millis();
      tone(buzzerPin, buzzerTone, 10);
    }
    switchVal = digitalRead(buttonPin);
    if(switchVal == HIGH){
      alarm = false;
      noTone(buzzerPin);
    }
  }
}
