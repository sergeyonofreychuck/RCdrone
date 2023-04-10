

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");
  initSettings();
  initDefaults();
  readSettings();

  setupUserInput();
  setupMenu();
}

void loop() {
  readUserInput();
  delay(50);
}  
