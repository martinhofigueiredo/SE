/* FILE:    ARD_Multifunction_Shield_Seven_Segment_Example
   DATE:    28/05/14
   VERSION: 0.1
   
REVISIONS:

28/05/14 Created version 0.1

This is an example of how to use the 4 digit seven segment display on the Hobby
Components Arduino compatible Multi Function experimenter shield (HCARDU0085).

This example sketch will display a decimal number on the seven segment LED display
which will increment by one wever 100ms.

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


/* Define shift register pins used for seven segment display */
#define LATCH_DIO 4
#define CLK_DIO 7
#define DATA_DIO 8
 
/* Segment byte maps for numbers 0 to 9 */
const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
/* Byte maps to select digit 1 to 4 */
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};


unsigned long Cur_ms_Count; // Stores the current time in ms
unsigned long Last_ms_Count; // Stores the last time in ms the counter was last updated
int Count; // Stores the value that will be displayed

void setup ()
{
  /* Set DIO pins to outputs */
  pinMode(LATCH_DIO,OUTPUT);
  pinMode(CLK_DIO,OUTPUT);
  pinMode(DATA_DIO,OUTPUT);
 
  /* Initiliase the registers used to store the crrent time and count */
  Cur_ms_Count = millis();
  Last_ms_Count = 0;
  Count = 0;
}

/* Main program */
void loop()
{
 
  /* Get how much time has passed in milliseconds */
  Cur_ms_Count = millis();
 
  /* If 100ms has passed then add one to the counter */
  if(Cur_ms_Count - Last_ms_Count > 100)
  {

    Last_ms_Count = Cur_ms_Count;
   
    if(Count < 9999)
    {
      Count++;
    } else
    {
      Count = 0;
    }
  }
 
  /* Update the display with the current counter value */
  WriteNumber(Count);
}


/* Write a decimal number between 0 and 9999 to the display */
void WriteNumber(int Number)
{
  WriteNumberToSegment(0 , Number / 1000);
  WriteNumberToSegment(1 , (Number / 100) % 10);
  WriteNumberToSegment(2 , (Number / 10) % 10);
  WriteNumberToSegment(3 , Number % 10);
}

/* Wite a ecimal number between 0 and 9 to one of the 4 digits of the display */
void WriteNumberToSegment(byte Segment, byte Value)
{
  digitalWrite(LATCH_DIO,LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
  digitalWrite(LATCH_DIO,HIGH);    
}