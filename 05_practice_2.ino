int ledPin = 7;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, LOW);
  delay(1000);

  digitalWrite(ledPin, HIGH);
  delay(500);

  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
    delay(200);
  }

  digitalWrite(ledPin, HIGH);
  while (1) {}  
}
