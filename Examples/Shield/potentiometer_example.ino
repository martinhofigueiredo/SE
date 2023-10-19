/* FILE:    ARD_Multifunction_Shield_Potentiometer_Example
   DATE:    28/05/14
   VERSION: 0.1

REVISIONS:

28/05/14 Created version 0.1

This is an example of how to read the position of the 10K potenetiometer
on the Hobby Components Arduino compatible Multi Function experimenter shield
(HCARDU0085).

The sketch will read the current position of the potentiometer and output it to
the serial terminal once every 0.5 seconds. To see the output open up the serial
monitor (Tools-> Serial Monitor) in your Arduino development environment and make
sure the baud rate is set to 9600 Baud.

You may copy, alter and reuse this code in any way you like, but please leave
reference to HobbyComponents.com in your comments if you redistribute this code.
This software may not be used directly for the purpose of selling products that
directly compete with Hobby Components Ltd's own range of products.

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/


/* Define the analogue pin used to read the potentiometer */
#define PotPin 0

void setup()
{
  Serial.begin(9600);
}

/* Main Program */
void loop()
{

  Serial.print("Potentiometer: ");
  Serial.println(analogRead(PotPin));
 
  /* Wait 0.5 seconds before reading again */
  delay(500);
}
	
	