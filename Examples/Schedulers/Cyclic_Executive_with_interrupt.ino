



#define d1 13
#define d2 12
#define d3 11
#define d4 10

/* 4 Tasks:
 *     T1 - T = 100ms   -> Led d1 toggle
 *     T2 - T = 200ms   -> Led d2 toggle
 *     T3 - T = 600ms   -> Led d3 toggle
 *     T4 - T = 100ms   -> Led d4 copied from button A1
 */

void t1() {digitalWrite(d1, !digitalRead(d1));}
void t2() {digitalWrite(d2, !digitalRead(d2));}
void t3() {digitalWrite(d3, !digitalRead(d3));}
void t4() {digitalWrite(d4,  digitalRead(A1));}

void m1() {
 t1();
 t2();
 t3();
 t4();
}

void m2() {
 t3();
 t4();
}

void m3() {
 t2();
 t3();
 t4();
}

void m4() {
 t3();
 t4();
}

void m5() {
 t2();
 t3();
 t4();
}

void m6() {
 t3();
 t4();
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(d4, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d1, OUTPUT);

  noInterrupts(); // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
 
  OCR1A = 6250; // compare match register 16MHz/256/10Hz
//OCR1A = 31250; // compare match register 16MHz/256/2Hz
//OCR1A = 31;    // compare match register 16MHz/256/2kHz
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS12); // 256 prescaler
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  interrupts(); // enable all interrupts  
}

volatile int go = 0;

ISR(TIMER1_COMPA_vect){//timer1 interrupt
  go = 1;
}

void wait() {
  while (go == 0);
  go = 0;
}

// the loop function runs over and over again forever
void loop() {
  m1();
  wait();
  m2();
  wait();
  m3();
  wait();
  m4();
  wait();
  m5();
  wait();
  m6();
  wait();
}
