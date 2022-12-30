#include <Arduino.h>
#include "TTGOAlienAttack.hpp"
#include "igraLORA.hpp"

loraGame lora;

void setup()
{
    //alien.game_setup();
    lora.game_setup();
}

void loop()
{
    //alien.game_routine();
    lora.game_routine();
}