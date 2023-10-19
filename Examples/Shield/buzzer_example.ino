/* FILE:    ARD_Multifunction_Shield_Buzzer_Example
   DATE:    28/05/14
   VERSION: 0.1

REVISIONS:
28/05/14 Created version 0.1

This is an example of how to use the buzzer on the Hobby Components Arduino compatible

Multi Function experimenter shield (HCARDU0085).

The sketch will use the buzzer to create 'pings' at a repetition rate dependant on
the current position of the 10K potentiometer.

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
#define POT_DIO 0

/* Define the digital pin used to control the buzzer */
#define BUZZER_DIO 3

#define OFF HIGH
#define ON LOW

void setup()
{
  /* Set the buzzer pin to an output and turn the buzzer off */
  pinMode(BUZZER_DIO, OUTPUT);
  digitalWrite(BUZZER_DIO, OFF);
}

/* Main Program */
void loop()
{
  /* Read the current position of the 10K potentiometer and use it
     as a time delay */
  delay(analogRead(POT_DIO));
 
  /* Turn the buzzer on for 20ms and then turn it back off again */
  digitalWrite(BUZZER_DIO, ON);
  delay(20);
  digitalWrite(BUZZER_DIO, OFF);
}