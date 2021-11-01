int level = 1;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(2, OUTPUT); //yellow LED 1 of task 1
  pinMode(3, OUTPUT); //red LED 2 of task 1
  pinMode(4, OUTPUT); //blue LED 3 of task 1
  pinMode(6, INPUT); //Button 1 of task 1
  pinMode(7, INPUT); //Button 2 of task 1
  pinMode(8, INPUT); //Button 3 of task 1
}

void loop() {
  // put your main code here, to run repeatedly:

  //randomTask = random(1,4);
  int randomTask = 1;

  if (randomTask == 1) {
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
    
    int flashOrder[mode];

    for (int i = 0; i < mode; i++) {
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
  tone(9, 1000, 250);
  delay(250);
  tone(9, 2000, 250);
  delay(250);
  tone(9, 3000, 250);
  delay(250);
  level++;
  return;
}

void gameOver() {
  tone(9, 2000, 1000);
  delay(1000);
  tone(9, 1000, 1000);
  delay(1000);
  tone(9, 500, 1000);
  delay(1000);
  level = 1;
  return;
}
