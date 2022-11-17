

void Sched_Init(){
  
}

int Sched_AddT(
    void (*f)(void),int d, int p){
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

void Sched_Add(){

}
void Sched_Schedule(void){
    for(int x=0; x<NT; x++) {
        if !Tasks[x].func continue;
        if Tasks[x].delay {
            Tasks[x].delay--;
        } else {
        /* Schedule Task */
        Tasks[x].exec++;
        Tasks[x].delay =
        Tasks[x].period;
        }
    }
};

void Sched_Dispatch(void){
    int prev_task = cur_task;
    for(int x=0; x<cur_task; x++){
        if Tasks[x].exec {
            Tasks[x].exec=0;
            cur_task = x;
            enable_interrupts();
            Tasks[x].func();
            disable_interrupts();
            cur_task = prev_task;
            /*Delete if one-shot */
            if !Tasks[x].period
            Tasks[x].func = 0;
            return;
        }
    }
};