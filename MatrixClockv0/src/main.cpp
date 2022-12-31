#include <Arduino.h>
#include "TTGOAlienAttack.hpp"
#include "igraLORA.hpp"

loraGame lora;
weatherApp weather;
clockApp smart_clock;
AlienAttack alien;

char buffer;

TaskHandle_t loraHandle = NULL;
TaskHandle_t timingHandle = NULL;

void lora_task(void* parameter){
    lora.game_routine();
}

void timing_task(void* parameter){
    vTaskGetRunTimeStats(&buffer);
    Serial.println(buffer);
    vTaskDelete(timingHandle);   
}

void setup()
{
    Serial.begin(9600);
    //alien.game_setup();
    lora.game_setup();
    //smart_clock.clock_setup();
    //weather.weather_setup();

    xTaskCreate(
    lora_task,    // Function that should be called
    "Lora Game Task",   // Name of the task (for debugging)
    1000,            // Stack size (bytes) Need to know if is enough
    NULL,            // Parameter to pass
    2,               // Task priority
    &loraHandle             // Task handle
  );
    //xTaskCreatePinnedToCore(
    //timing_task,    // Function that should be called
    //"Timing Task",   // Name of the task (for debugging)
    //1000,            // Stack size (bytes) Need to know if is enough
    //NULL,            // Parameter to pass
    //1,               // Task priority
    //&timingHandle,             // Task handle
    //1 // Core 1
  //);
}

void loop()
{
    //alien.game_routine();
    //lora.game_routine();
    //smart_clock.clock_routine();
    //weather.weather_routine();
}