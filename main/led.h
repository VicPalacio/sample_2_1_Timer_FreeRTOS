#ifndef LED_H
#define LED_H
#include "driver/gpio.h" // home/victor/.espressif/v6.1/esp-idf/components/esp_driver_gpio/include/driver

#define led_azul 4 // 09/11/2026 pendiente por implementar
#define led_rojo 5
#define led_verde 6 // 09/11/2026 pendiente por implementar

/**
 * @brief init_led ()
 * Resetea, define el pin a usar y el modo de uso del pin
 * (entrada o salida)
 */
esp_err_t init_led(void);

/**
 * @brief Configures the RGB LED according to timer 0 expiration.
 *
 * Common anode RGB leds are assigned following logic state:
 *
 * - R: 0
 * - G: 1
 * - B: 1
 * @return ESP_OK if the operation is successful.
 */
esp_err_t DesbordadoTimer0(void);

/**
 * @brief Configures the RGB LED according to timer 1 expiration.
 *
 * Common anode RGB leds are assigned following logic state:
 *
 * - R: 1
 * - G: 0
 * - B: 1
 * @return ESP_OK if the operation is successful.
 */
esp_err_t DesbordadoTimer1(void);

/**
 * @brief Configures the RGB LED according to timer 2 expiration.
 *
 * Common anode RGB leds are assigned following logic state:
 *
 * - R: 1
 * - G: 1
 * - B: 0
 * @return ESP_OK if the operation is successful.
 */
esp_err_t DesbordadoTimer2(void);

/**
 * @brief Configures the RGB LED according to timer 3 expiration.
 *
 * Common anode RGB leds are assigned following logic state:
 *
 * - R: 0
 * - G: 0
 * - B: 1
 * @return ESP_OK if the operation is successful.
 */
esp_err_t DesbordadoTimer3(void);

/**
 * @brief Configures the RGB LED according to timer 4 expiration.
 *
 * Common anode RGB leds are assigned following logic state:
 *
 * - R: 1
 * - G: 0
 * - B: 0
 * @return ESP_OK if the operation is successful.
 */
esp_err_t DesbordadoTimer4(void);

#endif