#include <Arduino.h>
#include "TTGOAlienAttack.hpp"
#include "igraLORA.hpp"

loraGame lora;

TaskHandle_t loraHandle = NULL;

void lora_task(void* parameter){
    lora.game_routine();
}

void setup()
{
    //alien.game_setup();
    lora.game_setup();
    xTaskCreate(
    lora_task,    // Function that should be called
    "Lora Game Task",   // Name of the task (for debugging)
    1000,            // Stack size (bytes) Need to know if is enough
    NULL,            // Parameter to pass
    1,               // Task priority
    &loraHandle             // Task handle
  );
}

void loop()
{
    //alien.game_routine();
    //lora.game_routine();
}