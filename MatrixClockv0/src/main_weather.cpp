// #include <Arduino.h>
// #include "weather_app.hpp"


// weatherApp weather;

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
//   weather.weather_set();
// }
// int loop_count=0;
// long int time_loop=0;
// long int init_time;

// void loop()
// {
//     init_time = micros(); 
//     weather.weather_routine(); 
//     time_loop = micros() - init_time;
//     if(loop_count % 100 == 0)
//     {
//         Serial.print("Loop number: ");
//         Serial.print(loop_count);
//         Serial.print(" time of loop(us): ");
//         Serial.print(time_loop);
//         Serial.print(" of wheather_task_time");
//         Serial.println();
//     }
//     loop_count++;
// }