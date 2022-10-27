#include "ukernel.c"

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

void Sched_Init();

void Sched_Add();