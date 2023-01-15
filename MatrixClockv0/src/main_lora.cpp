// #include <Arduino.h>
// #include "igraLORA.hpp"

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
//     lora.game_set();
// }
// int loop_count=0;
// long int time_loop=0;
// long int init_time;
// void loop()
// {
//     init_time = micros();
//     lora.game_routine();
//     loop_count++;
//     time_loop = micros() - init_time;
//     if(loop_count % 100 == 0)
//     {
//         Serial.print("Loop number: ");
//         Serial.print(loop_count);
//         Serial.print(" time of loop(us): ");
//         Serial.print(time_loop);
//         Serial.print(" of lora_game_task_time: ");
//         Serial.println();
//     }

// }