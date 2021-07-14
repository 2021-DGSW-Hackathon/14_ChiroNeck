#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  if (mySerial.available()) {
    
    int rx = mySerial.read(); //rx를 아스키코드로 받아들임
    Serial.println(rx);
    
    if (rx == 49) { //거북목이 심하다고 판정되었을 때
      
      lcd.clear();
      lcd.setCursor(0, 0);      //첫째 줄에
      lcd.print(" DANGEROUS "); //출력
      lcd.setCursor(0, 1);      //둘째 줄에
      lcd.print(" RED|POINT "); //출력
      setColor(255, 0, 0);      // red
      
    } else if (rx == 50) {  //거북목이 의심될 때
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" BE CAREFUL ");
      lcd.setCursor(0, 1);
      lcd.print(" PURPLE|POINT ");
      setColor(255, 0, 255); // purple
      
    } else if (rx == 51) {  //거북목이 아닐 때
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" GREAT! ");
      lcd.setCursor(0, 1);
      lcd.print(" GREEN|POINT ");
      setColor(0, 255, 0); // green
      
    }                                                                                                             
  }
}

void setColor(int red, int green, int blue) //LED쉽게 출력하는 함수
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
