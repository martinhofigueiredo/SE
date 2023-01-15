// #include <Arduino.h>
// #include "clock_app.hpp"
// #include "weather_app.hpp"


// weatherApp weather;
// clockApp clock_app;

// int counter = 0;
// int setup_executed = 1;

// void setup()
// {
//     Serial.begin(9600);
//     while (!Serial)
//     ;
//     tft.init();
//     tft.print("Connecting to Internet");
//     WiFi.mode(WIFI_STA);

//     WiFiManager wm;
//     // wm.resetSettings(); // Comment for production

//     bool auto_connect_res;
//     auto_connect_res = wm.autoConnect("weather AP connect");
//     if(!auto_connect_res)
//     {
//     Serial.println("Failed to connect");
//     tft.println("");
//     tft.println("Failed to connect");
//     WiFi.setAutoReconnect(true);
//     // ESP.restart();
//     }
//     else
//     Serial.println("Connected");
//     tft.println("");
//     tft.println("WiFi connected.");
//     tft.println("IP address: ");
//     tft.println(WiFi.localIP());

//   pinMode(27,INPUT);
//   pinMode(25,OUTPUT);
// }
// int loop_count=0;
// long int time_loop=0;
// long int init_time;
// long int total_time_weather = 0, total_time_clock = 0;
// double avg_time_task_wheather, avg_time_task_clock;
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
//       //Serial.println("GET INTO SWITCH CASE 1 clock game");
//       if(setup_executed == 0) {weather.weather_set(); setup_executed = 1; loop_count = 0;}
//       if(setup_executed == 1) weather.weather_routine(); 
//       loop_count++;
//     } else if (counter == 2)
//     {
//       //Serial.println("GET INTO SWITCH CASE 2 wheather app");
//       if(setup_executed == 0) {clock_app.clock_setup(); setup_executed = 1; loop_count = 0;}
//       if(setup_executed == 1) clock_app.clock_routine();
//       loop_count++;
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
//         Serial.print(" of wheather_task_time");
  
//       }else if(counter == 2)
//       {
//         Serial.print(" of smartclock_task_time");
//       }
//       Serial.println();
//     }

// }