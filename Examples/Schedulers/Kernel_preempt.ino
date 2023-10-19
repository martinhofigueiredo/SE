


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

int Sched_AddT(void (*f)(void), int d, int p);

void toggle(void) {digitalWrite(d4, !digitalRead(d4));}

void t0(void) {
  static int A1_old;
  int A1_new = digitalRead(A1); 
  
  if (A1_new != A1_old)
    Sched_AddT(toggle, 2000 /* delay */, 0 /* period */);
    
  A1_old = A1_new;
}

void t1(void) {digitalWrite(d1, !digitalRead(d1)); delay(700);}
void t2(void) {digitalWrite(d2, !digitalRead(d2));}
void t3(void) {digitalWrite(d3, !digitalRead(d3));}
void t4(void) {digitalWrite(d4,  digitalRead(A1));}





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
int cur_task = NT;


int Sched_Init(void){
  for(int x=0; x<NT; x++)
    Tasks[x].func = 0;
  /* Also configures interrupt that periodically calls Sched_Schedule(). */
  noInterrupts(); // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
 
//OCR1A = 6250; // compare match register 16MHz/256/10Hz
//OCR1A = 31250; // compare match register 16MHz/256/2Hz
  OCR1A = 31;    // compare match register 16MHz/256/2kHz
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
  int prev_task = cur_task;
  for(int x=0; x<cur_task; x++) {
    if((Tasks[x].func)&&(Tasks[x].exec)) {
      Tasks[x].exec=0;
      cur_task = x;
      interrupts();
      Tasks[x].func();
      noInterrupts();
      cur_task = prev_task;
      /* Delete task if one-shot */
      if(!Tasks[x].period) Tasks[x].func = 0;
    }
  }
}


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(d4, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d1, OUTPUT);
  Sched_Init();

  Sched_AddT(t0, 1 /* delay */,   10 /* period */);
  Sched_AddT(t3, 1 /* delay */,  200 /* period */);
  Sched_AddT(t2, 1 /* delay */,  500 /* period */);

  /* add a bunch of one-shot tasks, that will temporarily take up space in the TCB array */
  /* This forces task t1 to have a lower priority, and leave empty TCB entries for the 
   *  toggle task added by t0.
   */
  Sched_AddT(toggle, 10 /* delay */,  0 /* period */);
  Sched_AddT(toggle, 20 /* delay */,  0 /* period */);
  Sched_AddT(toggle, 30 /* delay */,  0 /* period */);
  Sched_AddT(toggle, 40 /* delay */,  0 /* period */);
  Sched_AddT(toggle, 50 /* delay */,  0 /* period */);
  Sched_AddT(toggle, 60 /* delay */,  0 /* period */);
  Sched_AddT(toggle, 70 /* delay */,  0 /* period */);
  Sched_AddT(toggle, 80 /* delay */,  0 /* period */);
  
  Sched_AddT(t1, 1 /* delay */, 1000 /* period */);
}



ISR(TIMER1_COMPA_vect){//timer1 interrupt
  Sched_Schedule();
  Sched_Dispatch();
}




// the loop function runs over and over again forever
void loop() {
  /* nothing to do */
}
