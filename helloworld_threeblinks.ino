//Theodore Storl-Desmond
//Cameron Hagg!
void setup() {
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(9, INPUT);
}

void loop() {
  if(digitalRead(9) == HIGH){
    digitalWrite(8, HIGH);
    delay(900);
    digitalWrite(8, LOW);
    delay(900);

    digitalWrite(12, HIGH);
    delay(900);
    digitalWrite(12, LOW);
    delay(1000);

    digitalWrite(13, HIGH);
    delay(900);
    digitalWrite(13, LOW);
    delay(900);
    
  }
}
