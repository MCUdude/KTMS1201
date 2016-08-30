#include "KTMS1201.h"

 uint8_t N_SCK = 3;
 uint8_t SI = 4;
 uint8_t CD = 5;
 uint8_t RESET = 6;
 uint8_t BUSY = 7;
 uint8_t CS = 10;

 KTMS1201 ktms(N_SCK, SI, CD, RESET, BUSY, CS);

void setup()
{
  ktms.begin();
}

void loop()
{
    ktms.setCursor(1);
    ktms.print(F("HAN.Q"));
    delay(2000);
    ktms.clear();

    ktms.setCursor(0);
    ktms.print(1.56);
    delay(2000);
    ktms.clear();

    ktms.setCursor(5);
    ktms.print('A');
    delay(2000);
    ktms.clear();



    

}


