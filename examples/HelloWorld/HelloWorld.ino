/*****************************************************************
| KTM-S1201 Arduino library                                      |
| Developed and maintanied by MCUdude                            |
| https://github.com/MCUdude/KTMS1201                            |            
| Released to the public domain                                  |
|                                                                |
| Basic "Hello world" example                                    |
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
  // Set up the LCD
  lcd.begin();
  // Set cursor at the first character
  lcd.setCursor(0);
  
  // Print message
  lcd.print("Hello world");
  delay(3000);
  // Clear the entire screen
  lcd.clear();
  
  // Print message
  lcd.print("Int");
  // Set cursor to the 10th digit
  lcd.setCursor(4);
  // Print integer value
  lcd.print(123);
  delay(2500);
  lcd.print(-123);
  delay(2500);
  // Clear entire screen
  lcd.clear();
  
  // Set cursor to the first digit
  lcd.setCursor(0);
  // Print message
  lcd.print("Float");
  // Set cursor to the 7th digit
  lcd.setCursor(6);
  lcd.print(123.45);
  delay(3000);
  // Clear entire screen
  lcd.clear();
  
  // Set cursor to the first digit
  lcd.setCursor(0);
  // Print message
  lcd.print("Blink fast");
  // Blink the LCD fast
  lcd.blink(fast);
  delay(5000);
  // Clear entire screen
  lcd.clear();
  
  // Print message
  lcd.print("Blink slow");
  // Blink the LCD slow
  lcd.blink(slow);
  delay(5000);
  // Clear entire screen
  lcd.clear();
  // Stop the blinking
  lcd.noBlink();
  
  // Set cursor to the first digit
  lcd.setCursor(0);
  // Print message
  lcd.print("Seconds");
}

void loop()
{ 
  // Set the cursor at the 9th digit
  lcd.setCursor(8);
  
  // Print seconds
  lcd.print(millis()/1000);
}