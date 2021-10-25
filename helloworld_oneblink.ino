//Theodore Storl-Desmond
//Cameron Hagg
void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
}

void loop() {
  if(digitalRead(9) == HIGH){
    digitalWrite(8, HIGH);
    delay(900);
    digitalWrite(8, LOW);
    delay(900);
  }
}
