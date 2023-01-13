#include <Arduino.h>
#include "TTGOAlienAttack.hpp"
#include "igraLORA.hpp"
#include "weather_app.hpp"
#include "clock_app.hpp"
#include "arduino/freertos.h"

loraGame lora;
weatherApp weather;
clockApp smart_clock;
AlienAttack alien;

char* buffer[256];
int counter = 0;

TaskHandle_t loraHandle = NULL;
TaskHandle_t timingHandle = NULL;
TaskHandle_t alienHandle = NULL;
TaskHandle_t smartclockHandle = NULL;
TaskHandle_t weatherHandle = NULL;
TaskHandle_t touchCHandle = NULL;

void lora_task(void* parameter){
    lora.game_routine();
}

void alien_task(void* parameter){
    alien.game_routine();
}

void smartclock_task(void* parameter){
    smart_clock.clock_setup();
}

void weather_task(void* parameter){
    weather.weather_setup();
}

void timing_task(void* parameter){
    //vTaskGetRunTimeStats(* buffer);
    //Serial.println(*buffer);
    //vTaskDelete(timingHandle);   
}

void touchCS_task(void* parameter){
  if(digitalRead(27)){
    counter++;
    Serial.println("TOUCHED PIN 27");
  }   
}

void setup()
{
    pinMode(27, INPUT);
    Serial.begin(9600);
    alien.game_setup();
    lora.game_setup();
    smart_clock.clock_setup();
    weather.weather_setup();

    xTaskCreate(
    lora_task,    // Function that should be called
    "Lora Game Task",   // Name of the task (for debugging)
    1000,            // Stack size (bytes) Need to know if is enough
    NULL,            // Parameter to pass
    1,               // Task priority
    &loraHandle             // Task handle
  );

    xTaskCreate(
    weather_task,    // Function that should be called
    "Weather Task",   // Name of the task (for debugging)
    2000,            // Stack size (bytes) Need to know if is enough
    NULL,            // Parameter to pass
    1,               // Task priority
    &weatherHandle             // Task handle
  );

}



void loop()
{
  switch(counter){
    case 0:{
      vTaskSuspend(&loraHandle);
      vTaskSuspend(&timingHandle);
      vTaskSuspend(&smartclockHandle);
      vTaskSuspend(&weatherHandle);
      vTaskResume(&alienHandle);
      //alien.game_routine();
    }
    case 1:{
      vTaskSuspend(&timingHandle);
      vTaskSuspend(&alienHandle);
      vTaskSuspend(&smartclockHandle);
      vTaskSuspend(&weatherHandle);
      vTaskResume(&loraHandle);
      //lora.game_routine();
    }
    case 2:{
      vTaskSuspend(&loraHandle);
      vTaskSuspend(&timingHandle);
      vTaskSuspend(&alienHandle);
      vTaskSuspend(&weatherHandle);
      vTaskResume(&smartclockHandle);
      //smart_clock.clock_routine();
    }
    case 3:{
      vTaskSuspend(&loraHandle);
      vTaskSuspend(&timingHandle);
      vTaskSuspend(&alienHandle);
      vTaskSuspend(&smartclockHandle);
      vTaskResume(&weatherHandle);
      //weather.weather_routine();
    }
    case 4:{
      counter = 0;
    }
  }

}