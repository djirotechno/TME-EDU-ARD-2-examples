/*  TME EDUCATION
 *  Random
 *  v0.1.0
 *  -------------
 *  Random numbers
 */ 
#define PROJECT_NAME "Random"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define KEY_RIGHT 7
#define KEY_LEFT 4
#define MICROPHONE A0
#define BUZZER 2
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define RESET_BTN 4
////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_MCP23008 seg;
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, RESET_BTN);


void setup(){
  lcd.begin(16, 2);
  // intro(lcd);

  display.begin(0x2, 0x3C, false);
  display.clearDisplay();
  display.display();

  seg.begin(0x4);
  for(int i = 0; i < 8; i++)
    seg.pinMode(i, OUTPUT);

  pinMode(KEY_RIGHT , INPUT);
  pinMode(KEY_LEFT , INPUT);
  pinMode(MICROPHONE, INPUT);

  randomSeed(analogRead(MICROPHONE));

  lcd.print(" press to rand");
  lcd.setCursor(0, 1);
  lcd.print("<- one or two ->");

  display.setTextColor(1); 
  display.setTextSize(8);
}

void loop(){
  if(digitalRead(KEY_LEFT)){
    while(digitalRead(KEY_LEFT)){
      display.clearDisplay();
      display.setCursor(45, 0);
      display.println(random(0, 9));
      display.display();

      if(millis() % 200 > 100 && millis() % 200 < 150)
        tone(BUZZER, 1000, 100);
    }
    delay(5000);
  }

  if(digitalRead(KEY_RIGHT)){
    while(digitalRead(KEY_RIGHT)){
      display.clearDisplay();
      display.setCursor(45, 0);
      display.println(random(0, 10));
      display.display();

      printOnSevenSeg(random(0, 10));
    
      if(millis() % 200 > 100 && millis() % 200 < 150)
        tone(BUZZER, 1000, 100);
    }
    delay(5000);
  }

  if(millis() % 1000 == 0){
    tone(BUZZER, 1000, 100);

    display.clearDisplay();
    display.setCursor(45, 0);
    display.println(random(0, 10));
    display.display();

    printOnSevenSeg(random(0, 10));
  }
}

void printOnSevenSeg(int sign){
  uint8_t data = 0;
  
  switch(sign){
    case 0:
      data = B11111100;
      break;
    case 1:
      data = B01100000;
      break;
    case 2:
      data = B11011010;
      break;
    case 3:
      data = B11110010;
      break;
    case 4:
      data = B01100110;
      break;
    case 5:
      data = B10110110;
      break;
    case 6:
      data = B10111110;
      break;
    case 7:
      data = B11100000;
      break;
    case 8:
      data = B11111110;
      break;
    case 9:
      data = B11110110;
      break;
  }
  for(int i = 0; i < 8; i++)
    seg.digitalWrite(i, bitRead(data, 7 - i));  
}
