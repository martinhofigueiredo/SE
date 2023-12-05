/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"

void myTask() {
    ESP_LOGI("APP", "calou");    
}

extern void app_main(void)
{
    ESP_LOGI("MAIN", "calou1");    
    xTaskCreate(myTask, "Tarefa1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();

}