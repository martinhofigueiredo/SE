// #include <Arduino.h>
// #include "TTGOAlienAttack.hpp"
// #include "igraLORA.hpp"
// //#include "weather_app.hpp"
// //#include "clock_app.hpp"
// // #include <freertos/FreeRTOS.h>
// // #include <freertos/task.h>

// AlienAttack alien;
// loraGame lora;

// int counter = 0;
// int setup_executed = 1;

// void setup()
// {
//     Serial.begin(9600);
//     while (!Serial)
//     ;
//     tft.init();
//     tft.fillScreen(TFT_BLACK);
//     tft.print("Click on the button to start an application");
//     pinMode(27,INPUT);
//     pinMode(25,OUTPUT);
// }
// int loop_count=0;
// long int time_loop=0;
// long int init_time;
// long int total_time_alien = 0, total_time_lora = 0;
// double avg_time_task_alien, avg_time_task_lora;
// void loop()
// {
//   init_time = micros();
//   if(digitalRead(27)){
//       counter++;
//       Serial.println("TOUCHED PIN 27, counter = ");
//       Serial.print(counter);
//       Serial.println();
//       setup_executed = 0;
//       delay(500);
//     } 
//     if(counter == 1){
//       //Serial.println("GET INTO SWITCH CASE 1 lora game");
//       if(setup_executed == 0) {alien.game_setup(); setup_executed = 1; loop_count = 1;}
//       if(setup_executed == 1) 
//       {
//         alien.game_routine(); 
//         loop_count++;
//       }
//     } else if (counter == 2)
//     {
//       //Serial.println("GET INTO SWITCH CASE 2 wheather app");
//       if(setup_executed == 0) {lora.game_set(); setup_executed = 1; loop_count = 1;}
//       if(setup_executed == 1) 
//       {
//         lora.game_routine();
//         loop_count++;
//       }
//     } else
//     {
//       counter = 0;
//     }
//     time_loop = micros() - init_time;
//     if(loop_count % 100 == 0)
//     {
//       Serial.print("Loop number: ");
//       Serial.print(loop_count);
//       Serial.print(" time of loop(us): ");
//       Serial.print(time_loop);
//       if(counter == 1) 
//       {
//         Serial.print(" of alien_task_time ");

//       }else if(counter == 2)
//       {
//         Serial.print(" of lora_game_task_time: ");
//       }
//       Serial.println();
//     }

// }