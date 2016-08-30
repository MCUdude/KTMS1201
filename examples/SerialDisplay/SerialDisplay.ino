/*****************************************************************
| KTM-S1201 Arduino library                                      |
| Developed and maintanied by MCUdude                            |
| https://github.com/MCUdude/KTMS1201                            |            
| Released to the public domain                                  |
|                                                                |
| Serial display example                                         |
*****************************************************************/


// Include the library code
#include "KTMS1201.h"

// Pin definitions
byte N_SCK = 3;
byte SI = 4;
byte CD = 5;
byte RESET = 6;
byte BUSY = 7;
byte CS = 10;

// Initialize the library with the interface pins
KTMS1201 lcd(N_SCK, SI, CD, RESET, BUSY, CS);
// Alternative without BUSY pin
KTMS1201 lcd(N_SCK, SI, CD, RESET, CS);

void setup()
{
	// Start the serial interface
  Serial.begin(9600);
  
  // Set up the LCD
  lcd.begin();
  
  // Print message
  lcd.print("Serial LCD");
}


void loop() 
{
  if(Serial.available())
  {
    // Wait a bit for the entire message to arrive
    delay(100);
    // Clear the screen
    lcd.clear();
    // Set the cursor at the first character place
    lcd.setCursor(0);
    // Read all the available characters
    while (Serial.available() > 0) 
    {
      // Display each character to the LCD
      lcd.print((char)Serial.read());
    }
  }
}
