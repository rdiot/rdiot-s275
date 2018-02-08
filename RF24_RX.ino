#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h> 
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h> 

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

RF24 radio(7, 8); // SPI Bus CE, CSN 
const byte address[6] = "00001"; // TX = RX same address

Servo myservo; 
int servoPin = 4; 

void setup() {

  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN); // Power Level : accoding to distance : RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX

  radio.startListening(); // RX

  myservo.attach(servoPin); 

  lcd.init(); // initialize the lcd 
  lcd.backlight();
  lcd.print("start LCD1602");
  delay(1000);
  lcd.clear();
 
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("S275:RF24L01 RX");

  lcd.setCursor(0, 1);
  if (radio.available()) {    
    char text[4] = "";
    
    radio.read(&text, sizeof(text));
    Serial.println(text);
    
    lcd.print("rcv=>" + String(text) + "     ");

    int value = atoi(text);
     myservo.write(180-value);
  }

  delay(10);
  
}
