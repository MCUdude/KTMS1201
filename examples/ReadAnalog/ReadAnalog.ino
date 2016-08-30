/*****************************************************************
| KTM-S1201 Arduino library                                      |
| Developed and maintanied by MCUdude                            |
| https://github.com/MCUdude/KTMS1201                            |            
| Released to the public domain                                  |
|                                                                |
| Read analog pin example                                        |
*****************************************************************/


// Include the library code
#include "KTMS1201.h"

// Pin definitions
byte analogPin = A0;
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
	// Set up the LCD
  lcd.begin();
  
  // Set the cursor on the first LCD character
  lcd.setCursor(0);
  // Print message
  lcd.print("LCD LIB");
  delay(2000);
  //Clear the entire screen
  lcd.clear();
  
  // Print message
  lcd.print("A0 VAL"); 
  // Set cursor on the 9th LCD character
  lcd.setCursor(8);
}

void loop()
{ 
	// Clear clear character 7 to 12
  lcd.clear(6,11);
  // Print the analog value
  lcd.print(analogRead(analogPin));
  delay(500);
}
