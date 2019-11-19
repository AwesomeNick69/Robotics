//joystick pins
const int pinX = A0; 
const int pinY = A1; 
const int pinSW = A2; // all the digital pins are occupied

const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int segSize = 8;

const int noOfDisplays = 4;
const int noOfDigits = 10;

int dpState = LOW;
int swState = LOW;
int lastSwState = LOW;
int switchValue;
int xValue = 0;
int yValue = 0;
bool xjoyMoved = false;
bool yjoyMoved = false;
bool buttonPressed = false;
int digitPos = 0;
int digit = 0;
int number = 0;
int minThreshold= 400;
int maxThreshold= 600;

unsigned long period=500;
unsigned long time_now=0;


// segments array, similar to before
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
// digits array, to switch between them easily
int digits[noOfDisplays] = {
  pinD1, pinD2, pinD3, pinD4
 };   
 
byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

int displayNumbers[noOfDisplays] = {
  0, 0, 0, 0
};
void displayNumber(byte digit, byte decimalPoint) {
  for (int i = 0; i < segSize - 1; i++) {
  digitalWrite(segments[i], digitMatrix[digit][i]);
  }

  // write the decimalPoint to DP pin
  digitalWrite(segments[segSize - 1], decimalPoint);
}

// activate the display no. received as param
void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
  digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num], LOW);
}

void setup() {
  for (int i = 0; i < segSize - 1; i++)
  {
    pinMode(segments[i], OUTPUT);  
  }
  for (int i = 0; i < noOfDisplays; i++)
  {
    pinMode(digits[i], OUTPUT);  
  }
  pinMode(pinSW, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  swState = digitalRead(pinSW);
  if (swState !=  lastSwState) {
    if (swState == LOW) {
      buttonPressed = !buttonPressed;
            
    }
  }
  lastSwState = swState;  
  if( buttonPressed == true ){
    yValue = analogRead(pinY);
    showDigit(digitPos);
    displayNumber(displayNumbers[digitPos],dpState);
    if(millis() > time_now + period){
         time_now = millis(); 
         dpState = !dpState;
      }
    if (yValue < minThreshold && yjoyMoved == false) {
      if (displayNumbers[digitPos] > 0) {
          displayNumbers[digitPos]--;
      } else {
          displayNumbers[digitPos] = 9;
      }
      yjoyMoved = true;
    }
    if (yValue > maxThreshold && yjoyMoved == false) {
      if (displayNumbers[digitPos] < 9) {
          displayNumbers[digitPos]++;
      } else {
          displayNumbers[digitPos] = 0;
      }
      yjoyMoved = true;
    }
    if (yValue >= minThreshold && yValue <= maxThreshold) {
      yjoyMoved = false;
    }
  } else {
      xValue=analogRead(pinX);
    if (xValue < minThreshold && xjoyMoved == false){
      if(digitPos > 0){
        digitPos--;
      } else{
        digitPos = 3;
      }
      xjoyMoved=true;
    }
     if (xValue > maxThreshold && xjoyMoved == false){
      if(digitPos < 3){
        digitPos++;
      } else{
        digitPos = 0;
      }
      xjoyMoved = true;
    }
    if (xValue >= minThreshold && xValue <= maxThreshold) {
    xjoyMoved = false;
    }
    showDigit(digitPos);
    displayNumber(displayNumbers[digitPos],HIGH);
   }
 
 
  for(int i = 0; i < noOfDisplays; i++)
  {
      showDigit(i);
      displayNumber(displayNumbers[i],LOW); 
       
  }
  

}
