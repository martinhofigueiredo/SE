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

<<<<<<< Updated upstream
=======
class app_screen {
  public:

};

TaskHandle_t loraHandle = NULL;
TaskHandle_t timingHandle = NULL;
>>>>>>> Stashed changes
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

void screen_schedule(TFT_eSPI tft)
{
  
}

void setup()
{

    Serial.begin(9600);
<<<<<<< Updated upstream
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
=======
    while (!Serial)
    ;

    tft.print("Connecting to Internet");
    //tft.println(ssid);
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

    // alien.game_setup();
    // lora.game_setup();
    
    

  //   xTaskCreate(
  //   lora_task,    // Function that should be called
  //   "Lora Game Task",   // Name of the task (for debugging)
  //   1000,            // Stack size (bytes) Need to know if is enough
  //   NULL,            // Parameter to pass
  //   1,               // Task priority
  //   &loraHandle             // Task handle
  // );

  //   xTaskCreate(
  //   weather_task,    // Function that should be called
  //   "Weather Task",   // Name of the task (for debugging)
  //   2000,            // Stack size (bytes) Need to know if is enough
  //   NULL,            // Parameter to pass
  //   1,               // Task priority
  //   &weatherHandle             // Task handle
  // );

>>>>>>> Stashed changes
}

int time_btn_pressed;
int setup_executed = 0;
void loop()
{
<<<<<<< Updated upstream
  
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
=======
  if(digitalRead(27)){
    time_btn_pressed = millis() + 100;
    if(time_btn_pressed < millis()) //To protect from multiples presses of a button
    {
      counter++;
      Serial.println("TOUCHED PIN 27, counter = ");
      Serial.print(counter);
      Serial.println();
      setup_executed = 0;
      time_btn_pressed = millis() + 500; //To not allow multiples presses to give time to the application
    }


    }   
  switch(counter){
    // case 0:{
    //   // vTaskSuspend(&loraHandle);
    //   // vTaskSuspend(&timingHandle);
    //   // vTaskSuspend(&smartclockHandle);
    //   // vTaskSuspend(&weatherHandle);
    //   // vTaskResume(&alienHandle);
    //   alien.game_routine();
    // }
    // case 1:{
    //   // vTaskSuspend(&timingHandle);
    //   // vTaskSuspend(&alienHandle);
    //   // vTaskSuspend(&smartclockHandle);
    //   // vTaskSuspend(&weatherHandle);
    //   // vTaskResume(&loraHandle);
    //   lora.game_routine();
    // }
    case 2:{
      // vTaskSuspend(&loraHandle);
      // vTaskSuspend(&timingHandle);
      // vTaskSuspend(&alienHandle);
      // vTaskSuspend(&weatherHandle);
      // vTaskResume(&smartclockHandle);
      if(setup_executed == 0) {smart_clock.clock_setup(); setup_executed = 1;}
      smart_clock.clock_routine();
    }
    case 3:{
      // vTaskSuspend(&loraHandle);
      // vTaskSuspend(&timingHandle);
      // vTaskSuspend(&alienHandle);
      // vTaskSuspend(&smartclockHandle);
      // vTaskResume(&weatherHandle);
      if(setup_executed == 0) {weather.weather_setup(); setup_executed = 1;}
      weather.weather_routine();
>>>>>>> Stashed changes
    }
    case 4:{
      counter = 0;
    }
  }
}