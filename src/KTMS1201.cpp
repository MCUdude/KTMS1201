/*****************************************************************
| KTM-S1201 Arduino library                                      |
| Developed and maintanied by MCUdude                            |
| https://github.com/MCUdude/KTMS1201                            |            
|                                                                |
| Based on Tronixstruff's work                                   |
| tronixstuff.com/2013/03/11/arduino-and-ktm-s1201-lcd-modules   |
| Released to the public domain                                  |
*****************************************************************/


#include "Arduino.h"
#include "KTMS1201.h"

/*******************************
******** PUBLIC METHODS ********
*******************************/

// Constructor with busy pin
KTMS1201::KTMS1201(uint8_t NSCK, uint8_t SI, uint8_t CD, uint8_t RESET, uint8_t BUSY, uint8_t CS)
{
	// Store parameters
  _SCK = NSCK;
  _SI = SI;
  _CD = CD;
  _RESET = RESET;
  _BUSY = BUSY;
  _CS = CS;
  
  //Set inputs and outputs
  pinMode(_SCK, OUTPUT);
  pinMode(_SI, OUTPUT);
  pinMode(_CD, OUTPUT);
  pinMode(_RESET, OUTPUT);
  pinMode(_BUSY, INPUT);
  pinMode(_CS, OUTPUT);
}


// Constructor without busy pin
KTMS1201::KTMS1201(uint8_t NSCK, uint8_t SI, uint8_t CD, uint8_t RESET, uint8_t CS)
{
	// Store parameters
  _SCK = NSCK;
  _SI = SI;
  _CD = CD;
  _RESET = RESET;
  _CS = CS;
  
  //Set inputs and outputs
  pinMode(_SCK, OUTPUT);
  pinMode(_SI, OUTPUT);
  pinMode(_CD, OUTPUT);
  pinMode(_RESET, OUTPUT);
  pinMode(_CS, OUTPUT);
}


void KTMS1201::begin()
{
  digitalWrite(_SCK, HIGH);
  digitalWrite(_SI,  HIGH);
  digitalWrite(_CD, HIGH);   // Put in command mode
  digitalWrite(_CS, HIGH);   // Deselect KTM-S1201
  digitalWrite(_RESET, LOW); // Reset LCD
  delay(10);                 // Wait for the LCD to finish
  digitalWrite(_RESET, HIGH);

  // Setup command mode. See header for more info
  command(_Mode);
  command(_Sync);
  command(_NoBlink); 
  command(_DispOn);
  command(_NoDecode); 
  command(_ClearDsp); 
}


void KTMS1201::command(uint8_t cmd)
{
  digitalWrite(_CD, HIGH);
  digitalWrite(_CS, LOW);
  wait(); // Wait for the LCD to finish
  write(cmd);
  wait(); // Wait for the LCD to finish
  digitalWrite(_CS, HIGH); // Deselect LCD to display data
}


void KTMS1201::customChar(uint8_t character)
{
  uint8_t p = 11 - _cursorPos;
  _cursorPos++;
  digitalWrite(_CD, HIGH);
  digitalWrite(_CS, LOW);
  wait(); // Wait for the LCD to finish
  write(_LoadPtr+p*2);
  
  digitalWrite(_CD, LOW);    //Put in data mode
  wait(); // Wait for the LCD to finish
  write(character);
  digitalWrite(_CS, HIGH); //deselect LCD to display data 
}


void KTMS1201::setCursor(uint8_t cursorPos)
{
	// Store cursor position
  _cursorPos = cursorPos;
}


void KTMS1201::clear(uint8_t start, uint8_t stop)
{
  // Clear the whole screen
  if(start == 0 && stop >= 11)
    command(_ClearDsp);
  else
  {
    uint8_t currentCursorPos = _cursorPos; // Store the current cursor position
    setCursor(start);
    String blankSpace = "";

    for(uint8_t i = 0; i < (stop - start + 1); i++) // Fill string with spaces
      blankSpace += ' ';
      
    print(blankSpace);
    setCursor(currentCursorPos);
  }
}


void KTMS1201::blink(bool speed)
{	
	// Blink fast
	if(speed == true)
		command(_FBlink);
	// Blink slow	
	else
		command(_SBlink);
}


void KTMS1201::noBlink()
{	
	command(_NoBlink);
}


void KTMS1201::display()
{	
	command(_DispOn);
}


void KTMS1201::noDisplay()
{	
	command(_DispOff);
}

  
void KTMS1201::print(String str)
{
  int8_t decimalPlace = -1;
  
  for(uint8_t i = 0; i < str.length(); i++)
  {
    if(str[i] == '.')
    {
      str.remove(i, 1);
      decimalPlace = i-1;
    }
  }

  uint8_t strLength = str.length();
  uint8_t p = 12 - strLength - _cursorPos;

  byte textString[strLength];

  str.toUpperCase();

  // Iterate through human readable array and stuff TextString with hex values. 
  for(uint8_t i = 0; i < strLength; i++)
  { 
    for(uint8_t j = 0; j < numberOfCharacters; j++)
    { 
      if(str[i] == charArray[j]) 
      {
        textString[i] = sevenSegHex[j]; 
        break;        
      }
    } 
  }

  if(decimalPlace >= 0)
    textString[decimalPlace] |= 0x08; // bitwise or in the dot
    
  digitalWrite(_CD, HIGH);
  digitalWrite(_CS, LOW);
  wait(); // Wait for the LCD to finish
  write(_LoadPtr+p*2);
  digitalWrite(_CD, LOW);    //Put in data mode
  wait(); // Wait for the LCD to finish

  for(uint8_t i = strLength; i > 0; i--) //display numbers (reverse order)
    write(textString[i-1]);

  digitalWrite(_CS, HIGH); //deselect LCD to display data  
}


void KTMS1201::print(char* inputArray)
{
  uint8_t arrayLength = 0; // It's not possible to use sizeof in a function
  uint8_t i = 0;
  
  while(inputArray[i] > 0) // ugly sizeof workaround
  {
    arrayLength = i+1;
    i++;
  }

  uint8_t p = 12 - arrayLength - _cursorPos;

  char textString[arrayLength];

  // Iterate through human readable array and stuff TextString with hex values. 
  for(i = 0; i < arrayLength; i++)
  { 
    for(uint8_t j = 0; j < numberOfCharacters; j++)
    { 
      if(inputArray[i] == charArray[j]) 
      {
        textString[i] = sevenSegHex[j]; 
        break;
      }
    } 
  }

  digitalWrite(_CD, HIGH);
  digitalWrite(_CS, LOW);
  wait(); // Wait for the LCD to finish
  write(_LoadPtr+p*2);
  digitalWrite(_CD, LOW);    //Put in data mode
  wait(); // Wait for the LCD to finish

  for(uint8_t i = arrayLength; i > 0; i--) //display numbers (reverse order)
    write(textString[i-1]);

  digitalWrite(_CS, HIGH); //deselect LCD to display data   
}


void KTMS1201::print(char character)
{
  uint8_t p = 11 - _cursorPos;
  _cursorPos++;
  digitalWrite(_CD, HIGH);
  digitalWrite(_CS, LOW);
  wait(); // Wait for the LCD to finish
  write(_LoadPtr+p*2);
  
  digitalWrite(_CD, LOW);    //Put in data mode
  wait(); // Wait for the LCD to finish

  for(uint8_t i = 0; i < numberOfCharacters; i++)
  { 
    if(character == charArray[i])
    {
      write(sevenSegHex[i]);
      break;
    }
  } 

  digitalWrite(_CS, HIGH); //deselect LCD to display data  
}


void KTMS1201::print(uint32_t n, uint8_t base)
{
  if(base > 1)
    printNumber(n, base);
}


void KTMS1201::print(int32_t n, uint8_t base)
{
  if(base > 1)
  {
    if(n < 0) 
    {
      n = -n;
      printNumber(n, DEC, true);
    }
    else 
      printNumber(n, base); 
  }
}


void KTMS1201::print(uint16_t n, uint8_t base)
{
  if(base > 1)
    printNumber((uint32_t)n, base);
}


void KTMS1201::print(int16_t n, uint8_t base)
{
  if(base > 1)
  {
    if(n < 0) 
    {
      n = -n;
      printNumber((int32_t)n, DEC, true);
    }
    else 
      printNumber((int16_t)n, base); 
  }
}

void KTMS1201::print(double n, uint8_t digits)
{
  printFloat(n, digits);
}



/********************************
******** PRIVATE METHODS ********
********************************/

void KTMS1201::printNumber(uint32_t number, uint8_t base, bool table)
{
  char buf[8 * sizeof(long) + 1 + table]; // Assumes 8-bit chars plus zero byte
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';
  
  do 
  {
    char c = number % base;
    number /= base;
    
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  }
  while(number);

  // Add minus if negative number
  if(table == true)
    *--str = '-';
   print(str);
}


void KTMS1201::printFloat(double number, uint8_t digits) 
{ 
  String dblValue = "";
  if(isnan(number))
  {
    dblValue += "nan";
    print(dblValue);
    return;
  }
  if(isinf(number))
  {
    dblValue += "inf";
    print(dblValue);
    return;
  }
  if(number > 4294967040.0)
  {
    dblValue += "ovf";
    print(dblValue);
    return;
  }
  if(number <-4294967040.0)
  {
    dblValue += "ovf";
    print(dblValue);
    return;
  }
  
  // Handle negative numbers
  if(number < 0.0)
  {
     dblValue += "-";
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for(uint8_t i = 0; i < digits; i++)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  dblValue += (String)int_part;

  // Print the decimal point, but only if there are digits beyond
  if(digits > 0)
    dblValue += ".";

  // Extract digits from the remainder one at a time
  while(digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    dblValue += (String)toPrint;
    remainder -= toPrint; 
  } 
  print(dblValue);
}


void KTMS1201::write(uint8_t character)
{
  for(uint8_t i = 0; i < 8; i++) 
  {
    digitalWrite(_SI, !!(character & (1 << (7-i))));
    digitalWrite(_SCK,LOW);
    wait(); // Wait for the LCD to finish
    digitalWrite(_SCK, HIGH); 
  }
}


void KTMS1201::wait()
{
	if(_BUSY == 255)
		delay(busyDelay);
	else
		while(digitalRead(_BUSY) == 0);
}



