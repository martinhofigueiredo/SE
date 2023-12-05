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

/* Route handler for button 1 */
static esp_err_t button1_handler(httpd_req_t *req)
{
    ESP_LOGI("BUTTONS", "Button 1 pressed\n");
    return ESP_OK;
}

/* Route handler for button 2 */
static esp_err_t button2_handler(httpd_req_t *req)
{
    ESP_LOGI("BUTTONS", "Button 2 pressed\n");
    return ESP_OK;
}

static esp_err_t slider_handler(httpd_req_t *req)
{
    char*  buf;
    size_t buf_len;

    buf_len = httpd_req_get_url_query_len(req) + 1;
    buf = malloc(buf_len);
    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
        char param[32];
        if (httpd_query_key_value(buf, "value", param, sizeof(param)) == ESP_OK) {
            ESP_LOGI("Slider", "Found URL query parameter => value=%s", param);
        }
    }
    free(buf);
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

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

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
        httpd_register_uri_handler(server, &slider);
    }
}