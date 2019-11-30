#include<LiquidCrystal.h>
#include <EEPROM.h>

const int RS = 12;
const int E = 11;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;
const int pinSW = 10;
const int pinX = A1;
const int pinY = A0;

int cursorPosition = 0;

int swValue;
int xValue = 0;
int yValue = 0;
bool joyCanMove = false;
int minThreshold = 400;
int maxThreshold = 600;

int buttonState = 0;
unsigned long lastSwTime = 0;
unsigned long currentTime = 0;
const int Switch = 200;

unsigned long lastLevel = 0;
unsigned long lastGame = 0;
const int inLevel = 4000;
const int inGame = 10000;
int level = 0;
int highScore = 0;
int lives = 3;
int checkGame = 0;
int checkScore = 0;
int checkFinishedGame = 0;
int score = 0;
int checkEEPROM = 0;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);




void cursor() {
  lcd.setCursor(0, 0);
  lcd.print(" ");
  lcd.setCursor(7, 0);
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print(" ");

  if (cursorPosition < 0) cursorPosition = 2;
  if (cursorPosition > 2) cursorPosition = 0;
  if (cursorPosition == 0) lcd.setCursor(0, 0);
  else if (cursorPosition == 1) lcd.setCursor(7, 0);
  else if (cursorPosition == 2) lcd.setCursor(0, 1);
  lcd.print(">");

}



void buttonPressed() {
  if (swValue == 0 && currentTime - lastSwTime >= Switch) {
    if (buttonState == 0) {
      buttonState = 1;
    }
    else {
      buttonState = 0;
    }
    lastSwTime = currentTime;
  }
}

void Menu() {
  lcd.setCursor(1, 0);
  lcd.print("Start ");
  lcd.setCursor(8, 0);
  lcd.print("Score  ");
  lcd.setCursor(1, 1);
  lcd.print("Settings       ");
}
void setup() {
  pinMode(pinSW, INPUT_PULLUP);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  swValue = digitalRead(pinSW);

  buttonPressed();

  if (buttonState == 0) {
     Menu();
    checkGame = 0;
    checkScore = 0;
    checkFinishedGame = 0;
    yValue = analogRead(pinY);
    if (yValue < minThreshold && joyCanMove == true) {
      cursorPosition++;
      cursor();
      joyCanMove = false;
    }

    if (yValue > maxThreshold && joyCanMove == true) {
      cursorPosition--;
      cursor();
      joyCanMove = false;
    }
    if (yValue >= minThreshold && yValue <= maxThreshold) {
      joyCanMove = true;
      cursor();
    }
  }
  else
  {

    if (cursorPosition == 0) {
      if (checkFinishedGame == 0) {
        lcd.setCursor(0, 0);
        lcd.print("Lives:");
        lcd.print(lives);
        lcd.print("  Level:");
        lcd.print(level);
        lcd.setCursor(0, 1);
        lcd.print("Score: ");
        score = level * 3;
        lcd.print(score);
        lcd.print(" ");
        if (checkScore == 0) {
          lastLevel = millis();
          checkScore = 1;
        }
        if (millis() - lastLevel >= inLevel) {
          level++;
          if (level > 5) level = 5;
          lastLevel = millis();
        }
        if (checkGame == 0) {
          lastGame = millis();
          checkGame = 1;
        }
      }
      if (millis() - lastGame >= inGame) {
        lcd.setCursor(0, 0);
        lcd.print("Congratulations! ");
        lcd.setCursor(0, 1);
        lcd.print("  You won!  ");
        checkFinishedGame = 1;
        if (score > highScore) highScore = score;
      }
    }

    else if (cursorPosition == 1) {
      EEPROM.write(0, highScore);
      highScore = EEPROM.read(0);
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 0);
      lcd.print("High Score: ");
      lcd.print(highScore);
      lcd.print("  ");
      EEPROM.write(0, highScore);
      EEPROM.update(0, highScore);
    }
    else {
      lcd.setCursor(0, 1);
      yValue = analogRead(pinY);
      if (yValue < minThreshold && joyCanMove == true) {
        level--;
        joyCanMove = false;
      }

      if (yValue > maxThreshold && joyCanMove == true) {
        level++;
        joyCanMove = false;
      }
      if (yValue >= minThreshold && yValue <= maxThreshold) {
        joyCanMove = true;
      }

      if (level < 0) level = 5;
      if (level > 5) level = 0;

      lcd.setCursor(0, 0);
      lcd.print("Start level: ");
      lcd.print(level);
      lcd.print("  ");
      lcd.setCursor(0, 1);
      lcd.print("           ");
      
    }
  }
}
