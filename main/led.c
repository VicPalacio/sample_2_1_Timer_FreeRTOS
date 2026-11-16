#include "led.h" // En: /run/media/victor/VICTORPALACIO/Backup/SEP_08_2026/ESP32_2026/sample_1_1_Timer_FreeRTOS/main
#include "driver/gpio.h"
#include "esp_log.h" // En: /home/victor/.espressif/v6.1/esp-idf/components/log/include

static uint8_t cuenta_timer_0 = 0;
static uint8_t cuenta_timer_1 = 0;
static uint8_t cuenta_timer_2 = 0;
static uint8_t cuenta_timer_3 = 0;
static uint8_t cuenta_timer_4 = 0;

static const char *tag_A = "LEDC"; // led.c es el módulo donde se está usando la librería

esp_err_t init_led(void)
{
    gpio_reset_pin(led_rojo);
    gpio_set_direction(led_rojo, GPIO_MODE_INPUT_OUTPUT);

    gpio_reset_pin(led_azul);
    gpio_set_direction(led_azul, GPIO_MODE_INPUT_OUTPUT);

    gpio_reset_pin(led_verde);
    gpio_set_direction(led_verde, GPIO_MODE_INPUT_OUTPUT);
    return ESP_OK;
}

esp_err_t DesbordadoTimer0(void)
{
    gpio_set_level(led_rojo, 0);  // Led activo en bajo
    gpio_set_level(led_verde, 1); // Led activo en bajo
    gpio_set_level(led_azul, 1);  // Led activo en bajo
    cuenta_timer_0++;
    ESP_LOGE(tag_A, "El timer 0 se ha desboradado: %u veces", cuenta_timer_0);
    return ESP_OK;
}

esp_err_t DesbordadoTimer1(void)
{
    gpio_set_level(led_rojo, 1);  // Led activo en bajo
    gpio_set_level(led_verde, 0); // Led activo en bajo
    gpio_set_level(led_azul, 1);  // Led activo en bajo
    cuenta_timer_1++;
    ESP_LOGE(tag_A, "El timer 1 se ha desboradado: %u veces", cuenta_timer_1);
    return ESP_OK;
}

esp_err_t DesbordadoTimer2(void)
{
    gpio_set_level(led_rojo, 1);  // Led activo en bajo
    gpio_set_level(led_verde, 1); // Led activo en bajo
    gpio_set_level(led_azul, 0);  // Led activo en bajo
    cuenta_timer_2++;
    ESP_LOGE(tag_A, "El timer 2 se ha desboradado: %u veces", cuenta_timer_2);
    return ESP_OK;
}

esp_err_t DesbordadoTimer3(void)
{
    gpio_set_level(led_rojo, 0);  // Led activo en bajo
    gpio_set_level(led_verde, 0); // Led activo en bajo
    gpio_set_level(led_azul, 1);  // Led activo en bajo
    cuenta_timer_3++;
    ESP_LOGE(tag_A, "El timer 3 se ha desboradado: %u veces", cuenta_timer_3);
    return ESP_OK;
}

esp_err_t DesbordadoTimer4(void)
{
    gpio_set_level(led_rojo, 1);  // Led activo en bajo
    gpio_set_level(led_verde, 0); // Led activo en bajo
    gpio_set_level(led_azul, 0);  // Led activo en bajo
    cuenta_timer_4++;
    ESP_LOGE(tag_A, "El timer 4 se ha desboradado: %u veces", cuenta_timer_4);
    return ESP_OK;
}
