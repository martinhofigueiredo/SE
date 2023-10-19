/* FILE:    ARD_Multifunction_Shield_Push_Button_Example
   DATE:    28/05/14
   VERSION: 0.1
   
REVISIONS:

28/05/14 Created version 0.1

This is an example of how to use the 3 push buttons on the Hobby Components Arduino
compatible Multi Function experimenter shield (HCARDU0085).

This example sketch will continuously read the state of the 3 push buttons and
output it to the serial terminal. To see the output open up the serial
monitor (Tools-> Serial Monitor) in your Arduino development environment and make
sure the baud rate is set to 9600 Baud.

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


/* Define pin numbers used to read the state of the buttons.
   The buttons are connected to the Arduino's analogue pins but
   because they only have two states we will read them as digital
   inputs */
#define BUTTON1 A1
#define BUTTON2 A2
#define BUTTON3 A3

void setup()
{
  Serial.begin(9600);
}

/* Main program */
void loop()
{
  /* Has button one been pressed? */
  if(!digitalRead(BUTTON1))
    /* If so then send a message to the serial port */
    Serial.println("Button 1 Pressed!");
  /* Has button two been pressed? */
  if(!digitalRead(BUTTON2))
    /* If so then send a message to the serial port */
    Serial.println("Button 2 Pressed!");
  /* Has button three been pressed? */
  if(!digitalRead(BUTTON3))
    /* If so then send a message to the serial port */
    Serial.println("Button 3 Pressed!");
}
	
	