// #include <Arduino.h>
// #include "TTGOAlienAttack.hpp"

// AlienAttack alien;

// int counter = 0;
// int setup_executed = 1;

// void setup()
// {
//     Serial.begin(9600);
//     while (!Serial)
//     ;
//     alien.game_setup();
// }
// int loop_count=0;
// long int time_loop=0;
// long int init_time;
// void loop()
// {
//   init_time = micros();
//   alien.game_routine(); 
//   time_loop = micros() - init_time;
//   if(loop_count % 100 == 0)
//     {
//       Serial.print("Loop number: ");
//       Serial.print(loop_count);
//       Serial.print(" time of loop(us): ");
//       Serial.print(time_loop);
//       Serial.print(" of alien_task_time ");
//       Serial.println();
//     }
//   loop_count++;
// }