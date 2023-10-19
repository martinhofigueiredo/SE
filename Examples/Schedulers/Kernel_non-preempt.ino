

const byte LED[] = {10,11,12,13};
const byte BUTTON[] = {A1,A2,A3};
/* 4 Tasks:
 *     T1 - T = 100ms   -> Led LED[3] toggle
 *     T2 - T = 200ms   -> Led LED[2] toggle
 *     T3 - T = 600ms   -> Led LED[1] toggle
 *     T4 - T = 100ms   -> Led LED[0] copied from button A1
 */

void t1(void) {digitalWrite(LED[3], !digitalRead(LED[3])); delay(5);}
void t2(void) {digitalWrite(LED[2], !digitalRead(LED[2]));}
void t3(void) {digitalWrite(LED[1], !digitalRead(LED[1]));}
void t4(void) {digitalWrite(LED[0],  digitalRead(BUTTON[0]));}





typedef struct {
  /* period in ticks */
  int period;
  /* ticks until next activation */
  int delay;
  /* function pointer */
  void (*func)(void);
  /* activation counter */
  int exec;
} Sched_Task_t;

#define NT 20
Sched_Task_t Tasks[NT];


int Sched_Init(void){
    for(int x=0; x<NT; x++)
        Tasks[x].func = 0;
        /* Also configures interrupt that periodically calls Sched_Schedule(). */
        noInterrupts(); // disable all interrupts
        TCCR1A = 0;
        TCCR1B = 0;
        TCNT1 = 0;
        OCR1A = 6250; // compare match register 16MHz/256/10Hz
        //OCR1A = 31250; // compare match register 16MHz/256/2Hz
        //OCR1A = 31;    // compare match register 16MHz/256/2kHz
        //OCR1A = 31250; // compare match register 16MHz/256/2Hz
        TCCR1B |= (1 << WGM12); // CTC mode
        TCCR1B |= (1 << CS12); // 256 prescaler
        TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
        interrupts(); // enable all interrupts  
}

int Sched_AddT(void (*f)(void), int d, int p){
  for(int x=0; x<NT; x++)
    if (!Tasks[x].func) {
      Tasks[x].period = p;
      Tasks[x].delay = d;
      Tasks[x].exec = 0;
      Tasks[x].func = f;
      return x;
    }
  return -1;
}


void Sched_Schedule(void){
  for(int x=0; x<NT; x++) {
    if(Tasks[x].func){
      if(Tasks[x].delay){
        Tasks[x].delay--;
      } else {
        /* Schedule Task */
        Tasks[x].exec++;
        Tasks[x].delay = Tasks[x].period-1;
      }
    }
  }
}


void Sched_Dispatch(void){
  for(int x=0; x<NT; x++) {
    if((Tasks[x].func)&& (Tasks[x].exec)) {
      Tasks[x].exec=0;
      Tasks[x].func();
      /* Delete task if one-shot */
      if(!Tasks[x].period) Tasks[x].func = 0;
      return; // fixed priority version!
    }
  }
}


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
  
  Sched_Init();

  Sched_AddT(t4, 0 /* delay */, 4 /* period */);
  Sched_AddT(t3, 1 /* delay */, 4 /* period */);
  Sched_AddT(t2, 2 /* delay */, 4 /* period */);
  Sched_AddT(t1, 3 /* delay */, 4 /* period */);
  Serial.begin(9600);
}



ISR(TIMER1_COMPA_vect){//timer1 interrupt
  Sched_Schedule();
}




// the loop function runs over and over again forever
void loop() {
  Sched_Dispatch();
}
