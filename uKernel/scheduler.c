typedef struct {
    int period;
    int delat;
    void (*func) (void);
    int exec;
}   Sched_Task_t;

void init_handler(void){
    Sched_Schedule();
}


int Sched_AddT(void (*f) void, int d, 
)

void Sched_Schedule(void){
    for(int x=0;x<NT; x++){
        if(Task[x].func){
            if 
        }
    }
}


void Sched_Dispatch(void){
    for(int x=0;x<NT; x++){
        if(Task[x].func){
            if 
        }
    }
}