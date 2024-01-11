#include <stdio.h>
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "esp_netif.h"
#include "esp_eth.h"
#include "protocol_examples_common.h"

#include <esp_https_server.h>
#include "esp_tls.h"
#include "sdkconfig.h"

#include "include/website.h"
#include "driver/gpio.h"
#include "esp_intr_alloc.h"

#include "include/esp32-triac-dimmer-driver.h" 

#define AC_LOAD 7   // GPIO number for the TRIAC control
//#define AC_LOAD GPIO_NUM_7   // GPIO number for the TRIAC control
#define ZERO_CROSS 8  // GPIO number for the zero-crossing interrupt

#define LCD_BUT 41

//#define ZERO_CROSS GPIO_NUM_8  // GPIO number for the zero-crossing interrupt
#define AC_FREQUENCY 50  // AC Frequency in Hertz (either 50 or 60)
#define _50Hz 50
typedef struct {
    bool is_on;
    uint32_t range;
} ControlData;

ControlData global_control_data;

bool read_and_log_button_state(gpio_num_t button_pin, const char* button_name) {
    bool button_state = gpio_get_level(button_pin);
    ESP_LOGI("App", "Button %s: %d\n", button_name, button_state);
    return button_state;
}

void tarefaLeituraBotoes(void *pvParameters) {
    while (1) {
        if(!read_and_log_button_state(LCD_BUT, "BUTTON LCD")){
            global_control_data.is_on = !global_control_data.is_on;}
        vTaskDelay(pdMS_TO_TICKS(100)); // Add a small delay
    }
}

/* Route handler for button 1 */
static esp_err_t button1_handler(httpd_req_t *req)
{
    ESP_LOGI("BUTTONS", "Button ON pressed\n");
    global_control_data.is_on = true;
    return ESP_OK;
}

/* Route handler for button 2 */
static esp_err_t button2_handler(httpd_req_t *req)
{
    ESP_LOGI("BUTTONS", "Button OFF pressed\n");
    global_control_data.is_on = false;
    return ESP_OK;
}

/* Route handler for button 3 */
void button3_task(void* arg) {
    vTaskDelay(pdMS_TO_TICKS(2000)); // Wait for 2 seconds
    global_control_data.is_on = false;
    ESP_LOGI("BUTTONS", "Button OFF pressed after 2 seconds\n");
    vTaskDelete(NULL); // Delete this task after it's done
}
static esp_err_t button3_handler(httpd_req_t *req)
{
    xTaskCreate(button3_task, "ButtonHandlerTask", 4096, NULL, tskIDLE_PRIORITY, NULL);
    return ESP_OK;
}

/* Route handler for button 4 */
void button4_task(void* arg) {
    vTaskDelay(pdMS_TO_TICKS(5000)); // Wait for 5 seconds
    global_control_data.is_on = false;
    ESP_LOGI("BUTTONS", "Button OFF pressed after 5 seconds\n");
    vTaskDelete(NULL); // Delete this task after it's done
}
static esp_err_t button4_handler(httpd_req_t *req)
{
    xTaskCreate(button4_task, "ButtonHandlerTask", 4096, NULL, tskIDLE_PRIORITY, NULL);
    return ESP_OK;
}

/* Route handler for button 5 */
void button5_task(void* arg) {
    vTaskDelay(pdMS_TO_TICKS(10000)); // Wait for 10 seconds
    global_control_data.is_on = false;
    ESP_LOGI("BUTTONS", "Button OFF pressed after 10 seconds\n");
    vTaskDelete(NULL); // Delete this task after it's done
}

static esp_err_t button5_handler(httpd_req_t *req)
{
    xTaskCreate(button5_task, "ButtonHandlerTask", 4096, NULL, tskIDLE_PRIORITY, NULL);
    return ESP_OK;
}

static esp_err_t slider_handler(httpd_req_t *req)
{
    char*  buf;
    size_t buf_len;

    buf_len = httpd_req_get_url_query_len(req) + 1;
    buf = malloc(buf_len);
    if (buf == NULL) {
        ESP_LOGE("Slider", "Out of memory");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
        char param[32];
        if (httpd_query_key_value(buf, "value", param, sizeof(param)) == ESP_OK) {
            global_control_data.range = atoi(param);
            
        }
    }
    free(buf);
    httpd_resp_sendstr(req, "OK");
    return ESP_OK;
}


static esp_err_t hello_get_handler(httpd_req_t *req)
{
    char*  buf;
    size_t buf_len;

    /* Get header value string length and allocate memory for length + 1,
     * extra byte for null termination */
    buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1;
    if (buf_len > 1) {
        buf = malloc(buf_len);
        /* Copy the header value in the buffer */
        if (httpd_req_get_hdr_value_str(req, "Host", buf, buf_len) == ESP_OK) {
            ESP_LOGI("APP", "Found header => Host: %s", buf);
        }
        free(buf);
    }

    httpd_resp_send(req, webpage, strlen(webpage));

    return ESP_OK;
}

void wifi_setup(){
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "esp",
            .ssid_len = strlen("esp"),
            .password = "1234567891",
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };
    if (strlen("1234567891") == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.uri_match_fn = httpd_uri_match_wildcard;

    
    httpd_uri_t button1 = {
        .uri       = "/button1",
        .method    = HTTP_GET,
        .handler   = button1_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t button2 = {
        .uri       = "/button2",
        .method    = HTTP_GET,
        .handler   = button2_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t button3 = {
        .uri       = "/button3",
        .method    = HTTP_GET,
        .handler   = button3_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t button4 = {
        .uri       = "/button4",
        .method    = HTTP_GET,
        .handler   = button4_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t button5 = {
        .uri       = "/button5",
        .method    = HTTP_GET,
        .handler   = button5_handler,
        .user_ctx  = NULL
    };
 
    httpd_uri_t slider = {
        .uri       = "/slider",
        .method    = HTTP_GET,
        .handler   = slider_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t hello = {
        .uri       = "/hello",
        .method    = HTTP_GET,
        .handler   = hello_get_handler,
        .user_ctx  = NULL
    };

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &hello); 
        httpd_register_uri_handler(server, &button1);
        httpd_register_uri_handler(server, &button2);
        httpd_register_uri_handler(server, &button3);
        httpd_register_uri_handler(server, &button4);
        httpd_register_uri_handler(server, &button5);
        httpd_register_uri_handler(server, &slider);
    }
}


void app_main(void)
{
    global_control_data.is_on = false;
    global_control_data.range = 50;
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    dimmertyp *ptr_dimmer; 
    wifi_setup();
    // Create the dimming task
    ptr_dimmer = createDimmer(AC_LOAD, ZERO_CROSS);
    begin(ptr_dimmer, TOGGLE_MODE, ON, AC_FREQUENCY);
    
    setState(ptr_dimmer, OFF);
    
    gpio_config_t lcd_but = {
        .pin_bit_mask = (1ULL << LCD_BUT),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&lcd_but);
    
    xTaskCreate(tarefaLeituraBotoes, "LeituraBotoes", 4096, NULL, tskIDLE_PRIORITY + 1, NULL);

    while(1){
        ESP_LOGI("RANGE", "%d", (int) global_control_data.range);
        ESP_LOGI("IS_ON", "%d", (int) global_control_data.is_on);
        if(global_control_data.is_on){
            setState(ptr_dimmer, ON);
            setPower(ptr_dimmer, global_control_data.range);
        }else{
            setState(ptr_dcimmer, OFF);
            setPower(ptr_dimmer, 0);
        }
        // wait
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

