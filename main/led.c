#include "led.h" // En: /run/media/victor/VICTORPALACIO/Backup/SEP_08_2026/ESP32_2026/sample_1_1_Timer_FreeRTOS/main
#include "driver/gpio.h"
#include "esp_log.h" // En: /home/victor/.espressif/v6.1/esp-idf/components/log/include

uint8_t led_level = 0, cuenta_blink_led_rojo = 0;
static const char *tag_A = "Timer"; // timer es el módulo donde se está usando la librería

esp_err_t blink_led(void)
{
    led_level = !led_level;
    gpio_set_level(led_rojo, led_level);
    cuenta_blink_led_rojo++;
    ESP_LOGI(tag_A, "Cuenta Blink como no signado decimal entero: %u", cuenta_blink_led_rojo);
    ESP_LOGE(tag_A, "Cuenta Blink como signado decimal entero: %d", cuenta_blink_led_rojo);
    ESP_LOGW(tag_A, "Cuenta Blink como caracter: %c", cuenta_blink_led_rojo);

    //   printf("Cuenta Blink como binario: ");
    for (int i = 7; i >= 0; i--)
    {
        printf("La cuenta conversion: %d", (cuenta_blink_led_rojo >> i) & 1);
        printf("\n");
    }
    return ESP_OK;
}

esp_err_t init_led(void)
{
    gpio_reset_pin(led_rojo);
    gpio_set_direction(led_rojo, GPIO_MODE_OUTPUT);
    return ESP_OK;
}