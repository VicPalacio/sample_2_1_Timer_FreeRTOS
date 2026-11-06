/* File:   sample_2_1_Timer_FreeRTOS
 *
 * Author: Victor Adolfo Palacio Bastidas
 *
 * Este proyecto es creado para ilustrar el uso de timers en su forma más básica, hace un toggle
 * sobre un pin y representa una cuenta a traves de una salida por consola, usando para esto la
 * librería incluida en ESP-IDF, la librería es esp_log.h
 * Created on 22 de Agosto de 2026  
*/
#include <stdio.h>             // /home/victor/.espressif/v6.1/esp-idf/components/esp_libc/platform_include
#include "freertos/FreeRTOS.h" //En: /home/victor/.espressif/v6.1/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
#include "freertos/task.h"     //En: /home/victor/.espressif/v6.1/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
#include "freertos/timers.h"   //En: /home/victor/.espressif/v6.1/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
#include "esp_log.h"           // En: /home/victor/.espressif/v6.1/esp-idf/components/log/include
#include "led.h"               // En: /run/media/victor/VICTORPALACIO/Backup/SEP_08_2026/ESP32_2026/sample_1_1_Timer_FreeRTOS/main

#define led_1 4 // Pin_06 = Pin compartido con la memoria Flash, no puede ser usado como un pin Input / Output ordinario
#define led_2 5 // Pin_06 = Pin compartido con la memoria Flash, no puede ser usado como un pin Input / Output ordinario
#define NUM_TIMERS 5
uint8_t led_level = 0, cuenta_blink_Led_2 = 0, contadorFuncion = 0;
uint8_t cuenta_app_main = 0;
static const char *tag = "Main";           // Main es el módulo donde se está usando la librería, en este caso el main
TimerHandle_t xTimers;                     // Este tipo de variable existe dentro del timers.h
int interval = 100, interval_ms = 50;      // Intervalo de tiempo para el timer, o el evento
int timerId = 1, timerId2_2 = 2;           // Identificador del timer
int32_t lExpireCounters[NUM_TIMERS] = {0}; // Segun la IA esto es para almacenar cuantas veces ha expirado cada temporizador

/*Funciones creadas*/
esp_err_t init_led(void);
esp_err_t blink_led(void);
esp_err_t blink_led_1(void);
esp_err_t set_timer(void);
/* vTimerCallback
* timers.h: línea 161: Each timer calls the same callback when it expires.
Define una función de devolución de llamada que será utilizada por varias
instancias del temporizador.
La función de devolución de llamada no hace nada más que contar la cantidad de
veces que el temporizador asociado expira y lo detiene una vez que ha expirado
10 veces, este control solo aplica cuando se usa la variable
xMaxExpiryCountBeforeStopping, en esta aplicación NO se está usando
*/
void vTimerCallback(TimerHandle_t pxTimer)
{
    int32_t lArrayIndex;
    contadorFuncion++;
    ESP_LOGI(tag, "Contador de función vTimerCallback: %u", contadorFuncion);
    const int32_t xMaxExpiryCountBeforeStopping = 10;
    ESP_LOGI(tag, "Event was called from timer");
    // blink_led();
    blink_led_1();                                     // Optionally do something if the pxTimer parameter is NULL.
    configASSERT(pxTimer);                             // Which timer expired?
    lArrayIndex = (int32_t)pvTimerGetTimerID(pxTimer); // Increment the number of times that pxTimer has expired.
    lExpireCounters[lArrayIndex] += 1;                 // If the timer has expired 10 times then stop it from running.
    if (lExpireCounters[lArrayIndex] == xMaxExpiryCountBeforeStopping)
    {
        // Do not use a block time if calling a timer API function from a
        // timer callback function, as doing so could cause a deadlock!
        xTimerStop(pxTimer, 0);
    }
}
/* app_main
 *Configura los pin(es) a usar
 *Configura el timer*/
void app_main(void)
{
    init_led();
    set_timer();
}
/* init_led
Resetea, define el pin a usar y el modo de uso del pin
(entrada o salida) */
esp_err_t init_led(void)
{
    gpio_reset_pin(led_1);
    gpio_set_direction(led_1, GPIO_MODE_OUTPUT);
    gpio_reset_pin(led_2);
    gpio_set_direction(led_2, GPIO_MODE_OUTPUT);
    return ESP_OK;
}
/* blink_led
/// @brief Hace un toggle al pin pasado parámetro
/// @param Recibe un número de pin
/// @return ok
*/
esp_err_t blink_led(void)
{
    led_level = !led_level;
    gpio_set_level(led_2, led_level);
    cuenta_blink_Led_2++;
    ESP_LOGI(tag, "Cuenta Blink LED azul: %u", cuenta_blink_Led_2);
    return ESP_OK;
}
esp_err_t blink_led_1(void)
{
    led_level = !led_level;
    gpio_set_level(led_1, led_level);
    return ESP_OK;
}
/* set_timer
/// @brief Configuura el timer así:
* Funcion xTimerCreate crea y configura el timer
* "Timer": es el nombre, no es usado por el Kernel
* (pdMS_TO_TICKS(interval)): función que pasa de ms a ticks para definir
el PERIODO de duración del timer.
* vTimerCallback: función definida en la libreria "timers.h"
* pdTRUE: Este parametro afirma que se debe recargar el timer
/// @param No recibe nada
/// @return ok
*/
esp_err_t set_timer(void)
{
    int32_t x;
    /* Crea y luego inicia los timers. Inicia los timers antes que el programa
    inicie, significa que los timers iniciarán inmediatamente el programa inicie
    */
    for (x = 0; x < NUM_TIMERS; x++)
    {
        ESP_LOGW(tag, "Timer init configuration");
        xTimers = xTimerCreate("Timer",
                               // Solo es un nombre, no es usado por el kernel.
                               //(pdMS_TO_TICKS(interval)), // Conversión de ms a Ticks.
                               (100 * (x + 1)), // The timer period in ticks.
                               // pdFALSE,
                               // El parámetro pdFALSE hace que solo se ejecute una vez y se validó operación
                               pdTRUE, // El timer se autorecargará cuando expire. linea nueva 10082024
                               //(void *)timerId, // Asigna un unico ID para igual para indice del array
                               (void *)x,
                               // Assign each timer a unique id equal to its array index.
                               vTimerCallback); // Cada timer llama la misma función callback cuando termina
        // Aquí sería muy interesante saber que valor recibe xTimers
        if (xTimers == NULL)
        {
            ESP_LOGE(tag, "The timer was not created.");
        }
        else
        {
            if (xTimerStart(xTimers, 0) != pdPASS)
            {
                ESP_LOGE(tag, "The timer could not be set into the active state");
            }
        }
    }
    return ESP_OK;
}