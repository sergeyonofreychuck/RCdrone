

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");
  setupUserInput();
}

void loop() {
  readUserInput();
  delay(50);
}  
