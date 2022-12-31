#include <Arduino.h>
#include "TTGOAlienAttack.hpp"
#include "igraLORA.hpp"


loraGame lora;
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
    //alien.game_setup();
    lora.game_setup();
    xTaskCreate(
    lora_task,    // Function that should be called
    "Lora Game Task",   // Name of the task (for debugging)
    5000,            // Stack size (bytes) Need to know if is enough
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
}