#ifndef LED_H
#define LED_H
#include "driver/gpio.h" // home/victor/.espressif/v6.1/esp-idf/components/esp_driver_gpio/include/driver

#define led_rojo 5

/**
 * @brief init_led ()
 * Resetea, define el pin a usar y el modo de uso del pin
 * (entrada o salida)
 */
esp_err_t init_led(void);

/**
 * @brief blink_led Hace un toggle al pin pasado parámetro y muestra la cuenta que lleva
 * la variable cuenta_blink_led_rojo en entero decimal no signado (%u), en
 * caracter (%c) y en binario (for que convierte a binario y lo muestra en
 * en decimal en al consola). también realiza la conversion a binario, muestra el
 * binario equivalente de la cuenta a traves de la siguiente implementacion
 * TENER EN CUENTA QUE ESTE NIVEL DE DETALLE NORMALENTE NO SE LE INDICA AL USUARIO
 * //   printf("Cuenta Blink como binario: ");
    for (int i = 7; i >= 0; i--) {
        printf("La cuenta conversion: %d", (cuenta_blink_led_rojo >> i) & 1);
        printf("\n");
    }
 * @param Recibe un número de pin
 * @return ok
 */
esp_err_t blink_led(void);

#endif