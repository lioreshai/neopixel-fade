#include <Adafruit_NeoPixel.h>

#define LED_PIN 22
#define LED_COUNT 7

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  neopixel_fade(strip.Color(0,0,0), strip.Color(0,0,255), 1000);
}

// the loop function runs over and over again forever
void loop() {
  neopixel_fade(strip.Color(0,0,255), strip.Color(255,0,0), 1000);
  neopixel_breathe(50, 200, 600);
  neopixel_breathe(50, 230, 1000);
  neopixel_breathe(50, 200, 600);
  neopixel_fade(strip.Color(255,0,0), strip.Color(0,0,255), 1000);
  neopixel_breathe(50, 230, 600);  
  neopixel_breathe(50, 200, 1000);  
  neopixel_breathe(50, 230, 600);
}

void neopixel_breathe(int start_brightness, int end_brightness, int duration) {
  int delta = end_brightness-start_brightness;
  int steps = duration > 100 ? round(duration/10) : duration;
  float step_size = delta/steps;
  float current_brightness = start_brightness;
  int wait_time = duration > 100 ? 10 : 1;
  for(int i=0; i<steps/2; i++) {
    current_brightness += step_size;
    strip.setBrightness(current_brightness);
    strip.show();
    delay(wait_time);
  }
  for(int i=0; i<steps/2; i++) {
    current_brightness -= step_size;
    strip.setBrightness(current_brightness);
    strip.show();
    delay(wait_time);
  }
}

void neopixel_fade(uint32_t start_color, uint32_t end_color, int duration) {
  int steps = duration > 100 ? round(duration/10) : duration;
  int wait_time = duration > 100 ? 10 : 1;
  int end_red = end_color >> 16 & 0xFF;
  int end_green = end_color >> 8 & 0xFF;
  int end_blue = end_color & 0xFF;
  float current_red = start_color >> 16 & 0xFF;
  float current_green = start_color >> 8 & 0xFF;
  float current_blue = start_color & 0xFF;
  float step_size_red = (end_red-current_red)/steps;
  float step_size_green = (end_green-current_green)/steps;
  float step_size_blue = (end_blue-current_blue)/steps;
  for(int i=0; i<steps; i++) { 
    current_red += step_size_red;
    current_green += step_size_green;
    current_blue += step_size_blue;
    strip.fill(strip.Color(current_red,current_green,current_blue), 0, strip.numPixels());
    strip.show();
    delay(wait_time);
  }
  strip.fill(strip.Color(end_red,end_green,end_blue), 0, strip.numPixels());
  strip.show();
}
