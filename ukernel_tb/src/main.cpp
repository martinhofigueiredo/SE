#include <Arduino.h>

/* Define shift register pins used for seven segment display */
#define LATCH_DIO 4
#define CLK_DIO 7
#define DATA_DIO 8
 
/* Segment byte maps for numbers 0 to 9 */
const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
/* Byte maps to select digit 1 to 4 */
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};

#define d1 13 
#define d2 12 
#define d3 11
#define d4 10

#define NT 20
Sched_Task_t Tasks [NT];

typedef struct {
   /* period in ticks    */
int period;
   /* ticks to activate  */
int delay;
   /* function pointer   */
void (*func)(void);
   /* activation counter */
int exec;
} Sched_Task_t;

int count;

volatile int go = 0; //Volatile makes the variable change without the compiler knowing about it
int c = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(d4, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d1, OUTPUT);

  pinMode(LATCH_DIO, OUTPUT); pinMode(CLK_DIO, OUTPUT); pinMode(DATA_DIO, OUTPUT);

  Sched_Init();
  Sched_Add(t1, 0, 10);
  Sched_Add(t2, 1, 20);
  Sched_Add(t3, 2, 30);
  Sched_Add(t4, 3, 100);
  Sched_Add(t5, 4, 10);
  //Setup Timer 1
  noInterrupts(); // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  //OCR1A = 31250; // compare match register 16MHz/256/2Hz
  OCR1A = 312;    // compare match register 16MHz/256/2kHz
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS12); // 256 prescaler
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  interrupts(); // enable all interrupts

  count = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  t1();t2();t3();t4(); t5();
  sync();
}


void t1(void) {
  static int c = 0;
  if(c++ == 10)
    {
      digitalWrite(d1, !digitalRead(d1));  c=0; 
    }
    count++;
  }
void t2(void) {digitalWrite(d2, !digitalRead(d2));}
void t3(void) {digitalWrite(d3, !digitalRead(d3)); }
void t4(void) {digitalWrite(d4, !digitalRead(A1)); }
void t5(void) {
  static int seg = 0;
  switch(seg)
  {
    case 0: WriteNumberToSegment(0 , count / 1000); seg=1; break;
    case 1: WriteNumberToSegment(1 , (count / 100) % 10); seg=2; break;
    case 2: WriteNumberToSegment(2 , (count / 10) % 10); seg=3; break;
    case 3: WriteNumberToSegment(3 , count % 10); seg=0; break;
  }
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt
go = 1; // toggle LED pin
Sched_Schedule();
}

void sync (void) 
{
  while(!go); //wait
  go = 0;     //reset flag
}


/* Wite a ecimal number between 0 and 9 to one of the 4 digits of the display */
void WriteNumberToSegment(byte Segment, byte Value)
{
  digitalWrite(LATCH_DIO,LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
  digitalWrite(LATCH_DIO,HIGH);    
}