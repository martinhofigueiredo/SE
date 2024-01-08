
 

// the setup function runs once when you press reset or power the board

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
void t4() {digitalWrite(d4,  digitalRead(A1));delay(80);}

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

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(d4, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d1, OUTPUT);
}


// the loop function runs over and over again forever
void loop() {
  m1();
  delay(100);                       // wait for a second
  m2();
  delay(100);                       // wait for a second
  m3();
  delay(100);                       // wait for a second
  m4();
  delay(100);                       // wait for a second
  m5();
  delay(100);                       // wait for a second
  m6();
  delay(100);                       // wait for a second
}
