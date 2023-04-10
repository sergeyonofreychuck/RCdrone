void setupMenu() {
  setupButtonsCallback(buttonPresed);
}

void buttonPresed(int button) {
  Serial.print(F("Button pressed: "));
  Serial.println(button);
}