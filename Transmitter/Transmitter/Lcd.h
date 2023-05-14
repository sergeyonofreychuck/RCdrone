#ifndef RC_LCD
#define RC_LCD

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void initScreen(){
  lcd.init();
  lcd.backlight();
}

int length(float f) {
  int n = f;
  int count = 0;
  do {
    n /= 10;
    ++count;
  } while (n != 0);
  if (f < 0) {
    count++;
  }
  return count + 3;
}

int length(int i) {
  int n = i;
  int count = 0;
  do {
    n /= 10;
    ++count;
  } while (n != 0);
  if (i < 0) {
    count++;
  }
  return count;
}

void showEdit(bool edit) {
  lcd.setCursor(0,0);
  if (edit) {
    lcd.blink();
  } else {
    lcd.noBlink();
  }  
}

void showSettingsItem(String name, float value, float min, float max, bool edit){
  // Serial.println("showSettingsItem ");
  // Serial.println(name);  
  // Serial.println(value);
  // Serial.println(min);
  // Serial.println(max);
  // Serial.println(edit);

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(name);
  lcd.setCursor(15-length(value) + 1, 0);
  lcd.print(value);
  lcd.setCursor(1, 1);
  lcd.print(min);
  lcd.setCursor(15-length(max) + 1, 1);
  lcd.print(max);

  showEdit(edit);
}

void showIntSettingsItem(String name, int value, int left, int right, bool edit){
  // Serial.println("showSettingsItem ");
  // Serial.println(name);  
  // Serial.println(value);
  // Serial.println(left);
  // Serial.println(right);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(name);
  lcd.setCursor(15-length(value) + 1, 0);
  lcd.print(value);
  lcd.setCursor(0, 1);
  lcd.print(left);
  lcd.setCursor(15-length(right) + 1, 1);
  lcd.print(right);

  showEdit(edit);
}

void showTwoFloatItem(String name, float valueLeft, float valueRight, bool edit){
  // Serial.println("showTwoFloatItem ");
  // Serial.println(name);  
  // Serial.println(valueLeft);
  // Serial.println(valueRight);
  // Serial.println(edit);

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(name);
  lcd.setCursor(1, 1);
  lcd.print(valueLeft);
  lcd.setCursor(15-length(valueRight) + 1, 1);
  lcd.print(valueRight);

  showEdit(edit);
}

void showSingleFloatItem(String name, float value, bool edit){
  // Serial.println("showSingleFloatItem ");
  // Serial.println(name);  
  // Serial.println(value);
  // Serial.println(edit);

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(name);
  lcd.setCursor(1, 1);
  lcd.print(value);

  showEdit(edit);
}

void showEditItem(String name, bool edit){
  // Serial.println("showEditItem ");
  // Serial.println(name);  
  // Serial.println(edit);

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(name);

  showEdit(edit);
}

void showIntScreen(String name, int value, int left, int right, int mid){
  // Serial.println("showIntScreen ");
  // Serial.println(name);  
  // Serial.println(value);
  // Serial.println(left);
  // Serial.println(mid);
  // Serial.println(right);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(name);
  lcd.setCursor(15-length(value) + 1, 0);
  lcd.print(value);
  lcd.setCursor(0, 1);
  lcd.print(left);
  lcd.setCursor(6, 1);
  lcd.print(mid);
  lcd.setCursor(15-length(right) + 1, 1);
  lcd.print(right);
}

void showGroupItem(String name){
  // Serial.println("showGroupItem ");
  // Serial.println(name);  

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(name);
}

#endif