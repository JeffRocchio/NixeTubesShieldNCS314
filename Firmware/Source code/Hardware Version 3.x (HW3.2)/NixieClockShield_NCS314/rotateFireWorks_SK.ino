/******************************************************************************/
//  Jeff Rocchio's Customizations.

/*  2023-03-02_a
        - Created ability for intensity of the RGB-LED under the dots column
      to be less than the intensity of the LEDs under the tubes.
      Did this because for me that LED shines too bright and interferes with
      the appearence of the blinking dots.
      NOTE-1: Since I have the 4-digit clock (HH:MM) I did not attempt to make
      the code work for clocks with two dot columns.
      NOTE-2: I hard-coded an intensity adjustment into my patch. There is
      no provision for a user-configurable setting via the back panel
      controls. To adjust the intensity you have to change the code
      in the the rotateFireWorks_SK.ino module.
      See documentation note CD-03 in CodeDocumentation.odt. */

/*  2023-03-02_b
        - Removed the obsolete lines of code that had been commented 
      out in the original source code I cloned. Did this to make the code
      a bit easier to follow. */

#include <Adafruit_NeoPixel.h>

#define PIN            6
#define NUMPIXELS      8
#define LEDsSpeed      10
#define COLdim         50 // 2023-03-02_a: Percent to dim the RGB LED under the blinking dots column.
const int LEDsDelay=40;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void LEDsSetup()
{
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(50);
}

void LEDsOFF()
{
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
  }
  pixels.show();
}

void LEDsTest()
{
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); 
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(1000);
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0)); 
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(1000);
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255)); 
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(1000);
  LEDsOFF();
}

void rotateFireWorks()
  /*  PURPOSE: 'Rotate' LED colors
        jrr, 2023-03-02: This function appears to "advance" the LED color
      when called. That is, the LEDs are lit, with a given color. This
      function increments each current R,G,B color value using some
      formula for that. So when called over time this has the effect
      of "rotating" the colors under the tubes. */
{
  if (tone1.isPlaying()) return; // jrr: If music is playing don't mess with the LEDs until it has stopped.
  if (!RGBLedsOn) // jrr: I assume RGBLedsOn is a flag indicating if the user has configured the backlight LEDs to be OFF or ON.
  {
    LEDsOFF();
    return;
  }
  if (LEDsLock) return;
  RedLight = RedLight + LEDsSpeed * fireforks[rotator * 3]; //jrr, 2023-03-02: Don't know what that fireforks[] is doing.
  GreenLight = GreenLight + LEDsSpeed * fireforks[rotator * 3 + 1];
  BlueLight = BlueLight + LEDsSpeed * fireforks[rotator * 3 + 2];

  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(RedLight, GreenLight, BlueLight)); 
  }

  pixels.show(); // This sends the updated pixel color to the hardware.
  
    /*   jrr, 2023-03-02: Have not tried to work out how this piece of code
      affects the color cycling. */
  cycle = cycle + 1;
  if (cycle == 255/LEDsSpeed)
  {
    rotator = rotator + 1;
    cycle = 0;
  }
  if (rotator > 5) rotator = 0;
}

void setLEDsFromEEPROM()
  /*  PURPOSE: light backlight LEDs if one color.
        This function lights the tube backlight RGB-LEDs when
      the user has configured them to be set to show one single
      color only (vs the default of rotating through color 
      changes).

    2023-03-02_a
      Modified to reduce the brightness of the LED that
      sits under the blinking dots column. See documentation
      item CD-03.
  */
{
  Serial.println("In setLEDsFromEEPROM()");

  float fDimFactor = (100-(float)COLdim)/100; // Dim column LED by this percentage 
  int R,G,B, Rc, Gc, Bc;
  
  R=EEPROM.read(LEDsRedValueEEPROMAddress);
  G=EEPROM.read(LEDsGreenValueEEPROMAddress);
  B=EEPROM.read(LEDsBlueValueEEPROMAddress);

  Rc = (int)(R * fDimFactor);
  Gc = (int)(G * fDimFactor);
  Bc = (int)(B * fDimFactor);

  for(int i=0;i<NUMPIXELS;i++)
  {
    if (i==2) { // pixel #2 is the dot-column LED pixel.
      pixels.setPixelColor(i, pixels.Color(Rc, Gc, Bc)); 
      Serial.print("Rc: "); Serial.println(Rc);
      Serial.print("Gc: "); Serial.println(Gc);
      Serial.print("Bc: "); Serial.println(Bc);
    }
    else { // digit tube LED pixels.
      pixels.setPixelColor(i, pixels.Color(R, G, B)); 
    }
  }
  pixels.show();
  Serial.println(F("LED Colors Read from EEPROM"));
  Serial.println(F("Digit Tube Values---"));
  Serial.print(F("   RED=")); Serial.println(R);
  Serial.print(F("   GREEN=")); Serial.println(G);
  Serial.print(F("   BLUE=")); Serial.println(B);
  Serial.println(F("Column Values---"));
  Serial.println(F("   Dimming Multiplier: ")); Serial.print(fDimFactor);
  Serial.print(F("      RED=")); Serial.println(Rc);
  Serial.print(F("      GREEN=")); Serial.println(Gc);
  Serial.print(F("      BLUE=")); Serial.println(Bc);
}
