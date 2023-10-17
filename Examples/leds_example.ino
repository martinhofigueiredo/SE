/* FILE:    ARD_Multifunction_Shield_LED_Example
   DATE:    28/05/14
   VERSION: 0.1
   
REVISIONS:

28/05/14 Created version 0.1

This is an example of how to use the 4 LED's on the Hobby Components Arduino
compatible Multi Function experimenter shield (HCARDU0085).

This example sketch will repeatedly turn each LED on in sequence to create a 'cylon'
effect.

You may copy, alter and reuse this code in any way you like, but please leave
reference to HobbyComponents.com in your comments if you redistribute this code.
This software may not be used for the purpose of promoting or selling products
that directly compete with Hobby Components Ltd's own range of products.

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/


/* Define the DIO pin numbers for each LED */
const byte LED[] = {13,12,11,10};

void setup()
{
  /* Set each pin to outputs */
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
}


/* Main program */
void loop()
{
  byte Index;
 
  /* Step through each LED and turn it on in sequence */
  for(Index = 0; Index <= 3; Index++)
  {
    /* First turn all the LED's off */
    digitalWrite(LED[0], HIGH);
    digitalWrite(LED[1], HIGH);
    digitalWrite(LED[2], HIGH);
    digitalWrite(LED[3], HIGH);
    /* Then turn the next LED ON */
    digitalWrite(LED[Index], LOW);
    /* Wait a little between each sequence */
    delay(100);   
  }
 
  /* Do the same thing but in reverse order */
  for(Index = 3; Index > 0; Index--)
  {
    /* First turn all the LED's off */
    digitalWrite(LED[0], HIGH);
    digitalWrite(LED[1], HIGH);
    digitalWrite(LED[2], HIGH);
    digitalWrite(LED[3], HIGH);
    /* Then turn the next LED ON */
    digitalWrite(LED[Index], LOW);
    /* Wait a little between each sequence */
    delay(100);   
  }
}