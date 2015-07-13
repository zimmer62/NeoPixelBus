#include <NeoPixelBus.h>

#define pixelCount 4 // this example assumes 4 pixels, making it smaller will cause a failure
#define pixelPin1 2  // make sure to set this to the correct pin
#define pixelPin2 5
#define pixelPin3 9
#define pixelPin4 10

#define colorSaturation 128

// the multibus will update all the attached NeoPixelBus at the same time
NeoPixelMultiBus multiStrip = NeoPixelMultiBus(4);

NeoPixelBus strip1 = NeoPixelBus(pixelCount, pixelPin1);
NeoPixelBus strip2 = NeoPixelBus(pixelCount, pixelPin2);
NeoPixelBus strip3 = NeoPixelBus(pixelCount, pixelPin3);
NeoPixelBus strip4 = NeoPixelBus(pixelCount, pixelPin4);

RgbColor red = RgbColor(colorSaturation, 0, 0);
RgbColor green = RgbColor(0, colorSaturation, 0);
RgbColor blue = RgbColor(0, 0, colorSaturation);
RgbColor white = RgbColor(colorSaturation);
RgbColor black = RgbColor(0);
    
void setup()
{
    // this resets all the neopixels to an off state
    strip1.Begin();
    strip1.Show();

    strip2.Begin();
    strip2.Show();

    strip3.Begin();
    strip3.Show();

    strip4.Begin();
    strip4.Show();

    // attach the buses to the multibus 
    multiStrip.AddBus(&strip1);
    multiStrip.AddBus(&strip2);
    multiStrip.AddBus(&strip3);
    multiStrip.AddBus(&strip4);
    
  delay(10000); // time to reattach serial debug tool

  Serial.begin(115200);
  Serial.println("Alive and well...");
  Serial.flush();
}


void loop()
{
    uint32_t last;
    
    Serial.println("going rgb");
      
    last = millis();
    while ((millis() - last) < 3000)
    {
        // only set the first pixel of each bus to a color, 
        // if they don't match in order, you may need to use NEO_GRB flag
        strip1.SetPixelColor(0, red);
        strip2.SetPixelColor(0, green);
        strip3.SetPixelColor(0, blue);
        strip4.SetPixelColor(0, white);
        multiStrip.ShowAll(); // let the multibus show them
        delay(1000/24);
    }

    Serial.println("going black");
    last = millis();
    while ((millis() - last) < 3000)
    {
        // turn off the pixels
        strip1.SetPixelColor(0, black);
        strip2.SetPixelColor(0, black);
        strip3.SetPixelColor(0, black);
        strip4.SetPixelColor(0, black);
        multiStrip.ShowAll();
        delay(1000/24);
    }
}


