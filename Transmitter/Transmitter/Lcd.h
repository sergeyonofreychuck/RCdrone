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

void showSettingsItem(String name, float value, float min, float max, bool edit){
  Serial.println("showSettingsItem ");
  Serial.println(name);  
  Serial.println(value);
  Serial.println(min);
  Serial.println(max);
  Serial.println(edit);

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(name);
  lcd.setCursor(15-length(value) + 1, 0);
  lcd.print(value);
  lcd.setCursor(1, 1);
  lcd.print(min);
  lcd.setCursor(15-length(max) + 1, 1);
  lcd.print(max);

  lcd.setCursor(0,0);
  if (edit) {
    lcd.blink();
  } else {
    lcd.noBlink();
  }
}

void showIntScreen(String name, int value, int left, int right){
  Serial.println("showSettingsItem ");
  Serial.println(name);  
  Serial.println(value);
  Serial.println(left);
  Serial.println(right);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(name);
  lcd.setCursor(15-length(value) + 1, 0);
  lcd.print(value);
  lcd.setCursor(0, 1);
  lcd.print(left);
  lcd.setCursor(15-length(right) + 1, 1);
  lcd.print(right);
}

void showGroupItem(String name){
  Serial.println("showGroupItem ");
  Serial.println(name);  

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(name);
}

#endif