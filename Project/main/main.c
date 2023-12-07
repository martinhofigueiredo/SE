/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_task_wdt.h"
#include <freertos/task.h>
#include <driver/gpio.h>

#define BUTTON1_PIN GPIO_NUM_2
#define BUTTON2_PIN GPIO_NUM_41
#define BUTTON3_PIN GPIO_NUM_5

void read_and_log_button_state(gpio_num_t button_pin, const char* button_name) {
    bool button_state = gpio_get_level(button_pin);
    ESP_LOGI("App", "Button %s: %d\n", button_name, button_state);
}

void tarefaLeituraBotoes(void *pvParameters) {
    while (1) {
        //read_and_log_button_state(BUTTON1_PIN, "1");
        read_and_log_button_state(BUTTON2_PIN, "2");
        //read_and_log_button_state(BUTTON3_PIN, "3");

        vTaskDelay(pdMS_TO_TICKS(100)); // Add a small delay
    }
}

void app_main(void) {
    gpio_config_t configButton1 = {
        .pin_bit_mask = (1ULL << BUTTON1_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config_t configButton2 = {
        .pin_bit_mask = (1ULL << BUTTON2_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config_t configButton3 = {
        .pin_bit_mask = (1ULL << BUTTON3_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&configButton1);
    gpio_config(&configButton2);
    gpio_config(&configButton3);

    // Create a task that reads the buttons
    xTaskCreate(tarefaLeituraBotoes, "LeituraBotoes", 4096, NULL, tskIDLE_PRIORITY + 1, NULL);
}