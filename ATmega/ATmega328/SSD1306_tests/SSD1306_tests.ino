#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64

#define OLED_RESET      -1 // -1 = Arduino reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool left = false;
bool right = false;

int clicks = 0;
void setup() {

  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  testdrawstyles();

}

void loop() {
  float vola = (analogRead(A0) * (5.0 / 1024.0));
  float volb = (analogRead(A1) * (5.0 / 1024.0));
  
  // Serial.println(vola);
  // Serial.println(volb);

  if(vola >= 3.1337){    
    if(!left){
      clicks -= 1;
      testdrawstyles();
      left = true;
    }
  } else {
    left=false;
  }
  if(volb >= 3.1337){

    if(!right){
      clicks += 1;
      testdrawstyles();
      right = true;
    }
  }else{
      right=false;
    }
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.setTextColor(BLACK, WHITE); // Draw 'inverse' text
  display.println(F("enzyme42"));
  display.setTextSize(1); 
  display.println("013D 013D 013D 013D");
  display.setTextColor(WHITE, BLACK);
  display.println("");
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);
  display.setTextSize(1); 
  display.println(clicks);

  display.display();
}
