#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

RF24 radio(7, 8); // SPI Bus CE, CSN 
const byte address[6] = "00001"; // RX = TX same address
int pin = A0; // Rotary Encoder Module (KY-040) [S120] : http://rdiot.tistory.com/126 [RDIoT Demo]

void setup() {
  pinMode(pin, INPUT);
  
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN); // Power Level : accoding to distance : RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX

  radio.stopListening();  // TX 

  lcd.init(); // initialize the lcd 
  lcd.backlight();
  lcd.print("start LCD1602");
  delay(1000);
  lcd.clear();
    
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("S275:RF24L01 TX");
  
  int readVal = analogRead(pin);
  readVal = map(readVal, 0, 1023, 0, 179);
  Serial.println(readVal);

  lcd.setCursor(0, 1);
  lcd.print("msg=>" + String(readVal) + "  ");
 
  
  char buf[4];
  itoa(readVal, buf, 10);
    
  radio.write(&buf, sizeof(buf)); //send messages to RX 
  delay(10);
  
}

