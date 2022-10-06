#include <Arduino.h>
#include <Wire.h> //for I2C
#include <M5Atom.h>

// M5 ATOM-Lite 用的是 WS2812B 或 SK6812 這種 三合一的 全彩LED
//但 R, G, B 的亮度差異滿多，G>>B>R
//除了 Red, Green, Blue, White 這種純色外，其他調色要調整比重
//例如 0xffff00 的黃色會變成亮綠，改用 0xff3000 卻比較有明顯橘色
// M5.dis.drawpix(0, 0xff3000); //set LED orange
#define GREEN 0x001100 //調低來省電
#define RED 0xff0000
#define BLUE 0x0000ff
#define WHITE 0xffffff
#define ORANGE 0xff3000
#define MAGENTA 0xff00ff
#define BLACK 0x000000
#define LED_OFF 0x000000

#define buttonLEDPin 33
#define buttonPin 23

unsigned long startTime = 0;
unsigned long currentTime = 0;
long randNumber;

void setup()
{
  M5.begin(true, false, true); // M5Atom.h 裡 void begin(bool SerialEnable = true, bool I2CEnable = true, bool DisplayEnable = false);
                               // 由於我們不使用 Atom-lite 預設的 25(SDA), 21(SCL) ，所以 I2CEnable 設為 false
  // Wire.begin(26,32);            // 使用 HY2.0 的 pins 作為 I2C    26(SDA), 32(SCL). Even I2CEnable is set to true, Overwrite it.

  M5.dis.drawpix(0, GREEN); // RED for start up

  // button GPIO - pressed when boot up t0 force to use bridge AP mode
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonLEDPin, OUTPUT);
  Serial.print("Init completed");

  //點亮 0.5 秒作為開機指示
  digitalWrite(buttonLEDPin, LOW);
  delay(500);
  digitalWrite(buttonLEDPin, HIGH);
}

void loop()
{
  // Serial.print(digitalRead(buttonPin));
  //  digitalWrite(buttonLEDPin, HIGH);
  //  delay(1000);
  //  digitalWrite(buttonLEDPin, LOW);
  //  delay(1000);

  startTime=millis();
  randNumber = random(1000, 3000);
  Serial.println(randNumber);
  delay(randNumber);
  digitalWrite(buttonLEDPin, LOW);
  delay(100);
  digitalWrite(buttonLEDPin, HIGH);

  while (digitalRead(buttonPin) == 1)
  {
    currentTime=millis();
    if ((currentTime - startTime) >5000){
      Serial.println("Timeout");
      digitalWrite(buttonLEDPin, LOW);
      delay(100);
      digitalWrite(buttonLEDPin, HIGH);  
      delay(100);
      digitalWrite(buttonLEDPin, LOW);
      delay(100);
      digitalWrite(buttonLEDPin, HIGH);     
      break;
    }

    //Serial.println(currentTime - startTime);
  }
}