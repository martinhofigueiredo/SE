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

#include <freertos/task.h>
#include <driver/gpio.h>

#define BUTTON1_PIN GPIO_NUM_2
#define BUTTON2_PIN GPIO_NUM_4
#define BUTTON3_PIN GPIO_NUM_5

// Função da tarefa que lê o estado do botão
void tarefaLeituraBotoes() {
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

  while (1) {
    // Ler o estado do botão 1
    bool estadoBotao1 = gpio_get_level(BUTTON1_PIN);
    ESP_LOGI("App","Botão 1: %d\n", estadoBotao1);

    // Ler o estado do botão 2
    bool estadoBotao2 = gpio_get_level(BUTTON2_PIN);
    ESP_LOGI("App","Botão 2: %d\n", estadoBotao2);

    // Ler o estado do botão 3
    bool estadoBotao3 = gpio_get_level(BUTTON3_PIN);
    ESP_LOGI("App","Botão 3: %d\n", estadoBotao3);

    vTaskDelay(pdMS_TO_TICKS(100)); // Adicionar um pequeno atraso
  }
}

extern void app_main(void) {
  // Configurar a tarefa que lê os botões
  xTaskCreate(tarefaLeituraBotoes, "LeituraBotoes", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
  vTaskStartScheduler();
}

