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

bool do_refresh = false;

int clicks = 0;

void setup() {

  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  refreshdisplay();
}

void loop() {
  float vol_a = (analogRead(A0) * (5.0 / 1024.0));
  float vol_b = (analogRead(A1) * (5.0 / 1024.0));
  
  // Serial.println(vol_a);
  // Serial.println(vol_b);

  if(vol_a >= 3.1337){    
    if(!left){
      clicks -= 1;
      do_refresh = true;
      left = true;
    }
  } else {
    left = false;
  }

  if(vol_b >= 3.1337){
    if(!right){
      clicks += 1;
      do_refresh = true;
      right = true;
    }
  }else{
    right = false;
  }

  // 

  if(do_refresh){
    do_refresh = false;
    refreshdisplay();
  }

}

void refreshdisplay(void) {
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
