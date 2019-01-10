#include <Wire.h>;
#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C lcd(0x27,16,2);

int i = 0;
int j = 0;
int k = 0;
int delayTime = 350; // Delay between shifts

void scrollLeft (int line, char str1[]) {
  i = strlen(str1);
    for (j = 16; j >= 0; j--) {
    lcd.setCursor(0, line);
    for (k = 0; k <= 15; k++) {
      lcd.print(" "); // Clear line 
    }
    lcd.setCursor(j, line);
    lcd.print(str1);
    delay(delayTime);
  }

}


void setup() {
  lcd.init();       //Khởi động màn hình. Bắt đầu cho phép Arduino sử dụng màn hình
  lcd.backlight();   //Bật đèn nền
  lcd.print("Test Only");
  delay(1000);
}

void loop() {
  lcd.clear();
  scrollLeft(0, "Hello World");
}
