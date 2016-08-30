# KTMS1201
A high level Arduino library for the KTM-S1201 LCD module. Based on the [Tronixstuff's work](http://tronixstuff.com/2013/03/11/arduino-and-ktm-s1201-lcd-modules/) and the Arduino print class. This library makes it really easy to interface with the LCD, and add it to you existing project. Make sure to check out [the examples](https://github.com/MCUdude/KTMS1201/tree/master/examples) for getting the most out of this library!
<br/> <br/>
<img src="http://i.imgur.com/SHNdIkf.jpg" width="450">

##Supported microcontrollers
* Any Arduino compatible microcontroller with at least 5 IO pins! This library does not depend on hardware spesific code.


##About the LCD
The LCD is probably some OEM modules for old telephones. the LCD is driven by the [NEC uPD7225 LCD driver](http://www.lcd-module.de/eng/pdf/zubehoer/upd7225.pdf), and can be purchased [here](http://www.thepartsplace.k5nwa.com/index.php?route=product/product&product_id=58). The LCD got six interface pins; SCK, SI, CD, RESET, BUSY and CS. It's optional, but recommended to use the <b>BUSY</b> pin. This might be a trade off if you need the extra pin.
<br/> <br/>
<img src="http://i.imgur.com/sBTxKxt.png" width="450">

##Minimal setup
Here's a minimal setup that will get you up and running. Note that this setup includes the BUSY pin.
<br/> <br/>
<img src="http://i.imgur.com/01oAg7P.png" width="500">
<br/> <br/>


##Reference

###Constructor
This library has two constructors, on with and one without the BUSY pin. Using the BUSY pin isn't mandatory, but it's recommended, since the LCD controller is handling the speed, rather than a fixed delay.
``` c++
// Constructor with the BUSY pin
KTMS1201 lcd(N_SCK, SI, CD, RESET, BUSY, CS);
// Constructor without the BUSY pin
KTMS1201 lcd(N_SCK, SI, CD, RESET, CS);
```

###Methods
These are the public methods for this library. Note that there exist multiple print() methods for different data types. You don't really need to care about this, just use the library like you would use `Serial.print()`!
``` c++
    void begin();
    void command(uint8_t);                            // Send raw command
    void customChar(uint8_t);                         // Print custom character
    void setCursor(uint8_t cursorPos = 0);            // Set cursor at index
    void clear(uint8_t start = 0, uint8_t stop = 11); // Clear a part of, or the entire screen
    void blink(bool speed = slow);                    // Blink the LCD (slow/fast)
    void noBlink();                                   // Stop the blinking
    void display();                                   // Enable display
    void noDisplay();                                 // Disable display
    
    void print(String);                               // Print string
    void print(char*);                                // Print char array
    void print(char);                                 // Print character
    void print(uint32_t, uint8_t base = DEC);         // Print unsigned 32-bit integer (Base: HEX, DEC, OCT, BIN)
    void print(int32_t, uint8_t base = DEC);          // Print signed 32-bit integer
    void print(uint16_t, uint8_t base = DEC);         // Print unsigned 16-bit integer
    void print(int16_t, uint8_t base = DEC);          // Print signed 16-bit integer
    void print(double, uint8_t decimals = 2);         // Print float number (default 2 decimals)
```

###Custom characters
This library supports custom characters, as long as it's printed induvidually. The picture below shows what hexadecimal numbers that represents each segment. Want to display more than one segment? simply add the segment values together!
Enabling segment A, B and C is as simple as adding their values: <i>0x01 + 0x02 + 0x04 = 0x07</i>.
This code will print a "/" at index 0:
``` c++
lcd.clear();          // Clear the entire LCD
lcd.setCursor(0);     // Set cursor at index 0
lcd.customChar(0x62); // 0x40 + 0x20 + 0x02 = 0x62 -> slash
```

<br/> <br/>
<img src="http://i.imgur.com/SVq4vOA.jpg" width="450">
