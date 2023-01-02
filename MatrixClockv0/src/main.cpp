#include <Arduino.h>
#include "TTGOAlienAttack.hpp"
#include "igraLORA.hpp"
#include "weather_app.hpp"
#include "clock_app.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

weatherApp weather;
AlienAttack alien;

int counter = 0;

TaskHandle_t alienHandle = NULL;
TaskHandle_t weatherHandle = NULL;
TaskHandle_t pin_taskHandle = NULL;

void alien_task(void* parameter){
    alien.game_routine();
}


void weather_task(void* parameter){
    weather.weather_routine();
}


void pin_task(void* parameter){
  if(!digitalRead(27)){counter++;}
}

void setup()
{

    Serial.begin(9600);
    alien.game_setup();
    weather.weather_setup();
    xTaskCreate(
    pin_task,    // Function that should be called
    "Pin Task",   // Name of the task (for debugging)
    1000,            // Stack size (bytes) Need to know if is enough
    NULL,            // Parameter to pass
    1,               // Task priority
    &pin_taskHandle             // Task handle
  );
    xTaskCreate(
    weather_task,    // Function that should be called
    "Weather Task",   // Name of the task (for debugging)
    1000,            // Stack size (bytes) Need to know if is enough
    NULL,            // Parameter to pass
    0,               // Task priority
    &weatherHandle             // Task handle
  );
    xTaskCreate(
    alien_task,    // Function that should be called
    "Alien Task",   // Name of the task (for debugging)
    1000,            // Stack size (bytes) Need to know if is enough
    NULL,            // Parameter to pass
    0,               // Task priority
    &alienHandle             // Task handle
  );
}



void loop()
{
  
 switch(counter){
    case 0:{
      vTaskSuspend(&weatherHandle);
      vTaskResume(&alienHandle);
    }
    case 1:{
      vTaskSuspend(&alienHandle);
      vTaskResume(&weatherHandle);
    }
    case 3:{
      vTaskSuspend(&weatherHandle);
      vTaskSuspend(&alienHandle);
      char * buffer[256]; 
      //vTaskGetRunTimeStats(*buffer); // needs to be turned on in the kernel
      Serial.println(*buffer);
    }
    case 4:{
      counter = 0;
    }
  }
}