#include <Arduino.h>
//#include "TTGOAlienAttack.hpp"
#include "igraLORA.hpp"
#include "weather_app.hpp"
//#include "clock_app.hpp"
// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>

//AlienAttack alien;
weatherApp weather;
loraGame lora;

int counter = 0;
int setup_executed = 1;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    ;
    tft.init();
    tft.print("Connecting to Internet");
    WiFi.mode(WIFI_STA);

    WiFiManager wm;
    // wm.resetSettings(); // Comment for production

    bool auto_connect_res;
    auto_connect_res = wm.autoConnect("weather AP connect");
    if(!auto_connect_res)
    {
    Serial.println("Failed to connect");
    tft.println("");
    tft.println("Failed to connect");
    WiFi.setAutoReconnect(true);
    // ESP.restart();
    }
    else
    Serial.println("Connected");
    tft.println("");
    tft.println("WiFi connected.");
    tft.println("IP address: ");
    tft.println(WiFi.localIP());

  pinMode(27,INPUT);
  pinMode(25,OUTPUT);
}
int loop_count=0;
long int time_loop=0;
long int init_time;
long int total_time_weather = 0, total_time_lora = 0;
double avg_time_task_wheather, avg_time_task_lora;
void loop()
{
  init_time = micros();
  if(digitalRead(27)){
      counter++;
      Serial.println("TOUCHED PIN 27, counter = ");
      Serial.print(counter);
      Serial.println();
      setup_executed = 0;
      delay(500);
    } 
    if(counter == 1){
      //Serial.println("GET INTO SWITCH CASE 1 lora game");
      if(setup_executed == 0) {weather.weather_set(); setup_executed = 1; loop_count = 1; total_time_weather = 0;}
      if(setup_executed == 1) weather.weather_routine(); 
      total_time_weather +=  time_loop;
      avg_time_task_wheather = total_time_weather / loop_count;
      loop_count++;
    } else if (counter == 2)
    {
      //Serial.println("GET INTO SWITCH CASE 2 wheather app");
      if(setup_executed == 0) {lora.game_set(); setup_executed = 1; loop_count = 1; total_time_lora = 0;}
      if(setup_executed == 1) lora.game_routine();
      total_time_lora +=  time_loop;
      avg_time_task_lora = total_time_lora / loop_count;
      loop_count++;
    } else
    {
      counter = 0;
    }
    time_loop = micros() - init_time;
    if(loop_count % 100 == 0)
    {
      Serial.print("Loop number: ");
      Serial.print(loop_count);
      Serial.print(" time of loop(us): ");
      Serial.print(time_loop);
      if(counter == 1) 
      {
        Serial.print(" Average_wheather_task_time: ");
        Serial.print(avg_time_task_wheather);
  
      }else if(counter == 2)
      {
        Serial.print(" Average_smartclock_task_time");
        Serial.print(avg_time_task_lora);
      }
      Serial.println();
    }

}