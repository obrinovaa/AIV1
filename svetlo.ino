#include <Adafruit_NeoPixel.h>
#include <Wire.h>           
#include <BH1750.h>         

BH1750 lightMeter;          
#define LED_PIN 5           
#define LED_COUNT 64        

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);     
  Wire.begin();
  if (!lightMeter.begin()) {
    Serial.println("Senzor BH1750 sa nepodarilo inicializovať!");
    while (true);
  }
  strip.begin();            
  strip.show();             
  strip.setBrightness(20);  
}

void loop() {
  float lux = lightMeter.readLightLevel();  
  if (lux < 0) { 
    Serial.println("Chyba pri čítaní hodnoty luxov zo senzora BH1750.");
    delay(1000);
    return;  
  }
  float dif = 750 - lux;  
  Serial.print("\nIntenzita osvetlenia: ");
  Serial.print(lux);
  Serial.print("\nRozdiel luxov: ");
  Serial.print(dif);
  delay(1000);  
  strip.clear();  
  int step = 8;  

  if (dif <= 100) step = 8;     
  else if (dif > 100 && dif <= 200) step = 7;
  else if (dif > 200 && dif <= 300) step = 6;
  else if (dif > 300 && dif <= 400) step = 5;
  else if (dif > 400 && dif <= 500) step = 4;
  else if (dif > 500 && dif <= 600) step = 3;
  else if (dif > 600 && dif <= 700) step = 2;
  else if (dif > 700 && dif <= 750) step = 1;  

  for (int i = 0; i < LED_COUNT; i += step) {
    strip.setPixelColor(i, strip.Color(255, 255, 255)); 
  }

  Serial.print("\nRozsvietené každú ");
  Serial.print(step);
  Serial.println(". LED");
  strip.show();  
}
