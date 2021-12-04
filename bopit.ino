#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int level;

void setup() {
  lcd.init(); // initialize the lcd
  lcd.backlight();
  
  level = 1;
  
  pinMode(0, INPUT); //reset button
  pinMode(12, OUTPUT); // LED lights if player wins
  pinMode(13, OUTPUT); //LED lights if player loses
  pinMode(2, OUTPUT); //yellow LED 1 of task 1
  pinMode(3, OUTPUT); //red LED 2 of task 1
  pinMode(4, OUTPUT); //blue LED 3 of task 1
  pinMode(6, INPUT); //Button 1 of task 1
  pinMode(7, INPUT); //Button 2 of task 1
  pinMode(8, INPUT); //Button 3 of task 1
  pinMode(1, INPUT); //Button low of task 2
  pinMode(10, INPUT); // Button high of task 2
  pinMode(9, OUTPUT); //Buzzer
  pinMode(11, INPUT); //LED to signal if flipped of task 2
}

void loop() {

  String binaryLevel = decToBinary(level);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level " + binaryLevel);

  if (level == 100) {
    win();
  }

  int mode;
  if (level >= 1 && level <= 10) {
    mode = 3;
  }
  else if (level >= 11 && level <= 20) {
    mode = 4;
  }
  else if (level >= 21 && level <= 30) {
    mode = 5;
  }
  else if (level >= 31 && level <= 40) {
    mode = 6;
  }
  else if (level >= 41 && level <= 50) {
    mode = 7;
  }
  else if (level >= 51 && level <= 60) {
    mode = 8;
  }
  else if (level >= 61 && level <= 70) {
    mode = 9;
  }
  else if (level >= 71 && level <= 80) {
    mode = 10;
  }
  else if (level >= 81 && level <= 90) {
    mode = 10;
  }
  else {
    mode = 11;
  }

  int randomTask = random(1,4);

  if (randomTask == 1) {
    blinkingLights()
  }

  if (randomTask == 2) {
    randomNoises()
  }

  if (randomTask == 3) {
    flip()
  }
}

boolean blinkingLights() {
  lcd.setCursor(0, 1);
  lcd.print("Blinking Lights");

  int flashOrder[mode];

  for (int i=0;i<mode;i++) {
    delay(500);

    //pick a random LED to light up
    int randomLED = random(1,4);

    if (randomLED == 1) {
      digitalWrite(2, HIGH);
      delay(500);
      digitalWrite(2, LOW);
      flashOrder[i] = 6;
    }
    else if (randomLED == 2) {
      digitalWrite(3, HIGH);
      delay(500);
      digitalWrite(3, LOW);
      flashOrder[i] = 7;
    }
    else {
      digitalWrite(4, HIGH);
      delay(500);
      digitalWrite(4, LOW);
      flashOrder[i] = 8;
    }
  }

  int pressOrder[mode];

  boolean button1_lock = false;
  boolean button2_lock = false;
  boolean button3_lock = false;

  for (int i=0;i<mode;i++) {
    boolean button_pressed = false;

    while(button_pressed == false){
      if (digitalRead(6) == HIGH && button1_lock == false){
        pressOrder[i] = 6;
        button1_lock = true;
        button_pressed = true;
        digitalWrite(2, HIGH);
      }
      if (digitalRead(7) == HIGH && button2_lock == false){
        pressOrder[i] = 7;
        button2_lock = true;
        button_pressed = true;
        digitalWrite(3, HIGH);
      }
      if (digitalRead(8) == HIGH && button3_lock == false){
        pressOrder[i] = 8;
        button3_lock = true;
        button_pressed = true;
        digitalWrite(4, HIGH);
      }
    }

    while (button1_lock == true || button2_lock == true || button3_lock == true) {
      if (digitalRead(6) == LOW){
        button1_lock = false;
        digitalWrite(2, LOW);
      }
      if (digitalRead(7) == LOW){
        button2_lock = false;
        digitalWrite(3, LOW);
      }
      if (digitalRead(8) == LOW){
        button3_lock = false;
        digitalWrite(4, LOW);
      }
    }
  }

  if (array_compare(flashOrder, pressOrder, mode, mode)) {
    nextRound();
  }
  else {
    gameOver();
  }
}

boolean randomNoises() {
  lcd.setCursor(0, 1);
  lcd.print("Random Noise");

  int soundOrder[mode];

  for (int i=0;i<mode;i++) {
    delay(500);

    int randomSound = random(1,3);

    if (randomSound == 1) {
      tone(9, 880);
      delay(500);
      noTone(9);
      soundOrder[i] = 1;
    }
    else {
      tone(9, 55);
      delay(500);
      noTone(9);
      soundOrder[i] = 10;
    }
  }

  int pressOrder[mode];

  boolean button1_lock = false;
  boolean button2_lock = false;

  for (int i=0;i<mode;i++) {
    boolean button_pressed = false;

    while(button_pressed == false){
      if (digitalRead(1) == HIGH && button1_lock == false){
        pressOrder[i] = 1;
        button1_lock = true;
        button_pressed = true;
        tone(9, 880);
      }
      if (digitalRead(10) == HIGH && button2_lock == false){
        pressOrder[i] = 10;
        button2_lock = true;
        button_pressed = true;
        tone(9, 55);
      }
    }

    while (button1_lock == true || button2_lock == true) {
      if (digitalRead(1) == LOW){
        button1_lock = false;
      }
      if (digitalRead(10) == LOW){
        button2_lock = false;
      }
    }
    noTone(9);
  }

  if (array_compare(soundOrder, pressOrder, mode, mode)) {
    nextRound();
  }
  else {
    gameOver();
  }
}

boolean flip() {
  lcd.setCursor(0, 1);
  lcd.print("Flip " + String(mode) + " Times");

  int flips = -2;
  boolean flipped = false;
  boolean high_lock = false;
  boolean low_lock = false;

  for (int i=0;i<mode;i++) {
    while(flipped == false){
      if (digitalRead(11) == HIGH and high_lock == false) {
        delay(1000);
        if (digitalRead(11) == HIGH) {
          high_lock = true;
          low_lock = false;
          flips = flips+2;
        }
      }
      if (digitalRead(11) == LOW and low_lock == false) {
        delay(1000);
        if (digitalRead(11) == LOW) {
          low_lock = true;
          high_lock = false;
          flips--;
        }
      }
      if (flips >= mode){
        flipped = true; 
      }
    }
  }

  if (flipped) {
    nextRound();
  }
  else {
    gameOver();
  }
}




String decToBinary(int n)
{
    int binaryNum[32];
    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    String binaryStr = "";
    for (int j = i - 1; j >= 0; j--)
        binaryStr += binaryNum[j]; 

    return binaryStr;
}

boolean array_compare(int *a, int *b, int len_a, int len_b){
  int n;
  if (len_a != len_b) {
    return false;
  }
  for (n=0;n<len_a;n++) {
    if (a[n]!=b[n]) {
      return false;
    }
  }
  return true;
}

void nextRound() {
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);
  level++;
  return;
}

void gameOver() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  level = 1;
  return;
}

void win() {
  digitalWrite(12, HIGH);
  tone(9, 1000, 500);
  delay(500);
  tone(9, 3000, 500);
  delay(500);
  tone(9, 5000, 500);
  delay(500);
  digitalWrite(12, LOW);
  level = 1;
  return;
}
