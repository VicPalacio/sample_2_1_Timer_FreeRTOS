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
#include "freertos/FreeRTOS.h" // /home/victor/.espressif/v6.1/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
#include "freertos/task.h"     // /home/victor/.espressif/v6.1/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
#include "freertos/timers.h"   // /home/victor/.espressif/v6.1/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
#include "esp_log.h"           // /home/victor/.espressif/v6.1/esp-idf/components/log/include
#include "led.h"               // /run/media/victor/VICTORPALACIO/Backup/SEP_08_2026/ESP32_2026/sample_1_1_Timer_FreeRTOS/main
#include "procces_array.h"     // /run/media/victor/VICTORPALACIO/Backup/SEP_08_2026/ESP32_2026/sample_1_1_Timer_FreeRTOS/main

#define PRUEBAS_ARRAY 10
#define NUM_TIMERS 5
uint8_t cuenta_app_main = 0;
static const char *tag = "MAIN";           // Main es el módulo donde se está usando la librería, en este caso el main
TimerHandle_t xTimers[NUM_TIMERS];         // Crea un vector (arreglo) con los identificadores de cada temporizador
int32_t lExpireCounters[NUM_TIMERS] = {0}; // Es para almacenar cuantas veces ha expirado cada temporizador

uint8_t pares_array[PRUEBAS_ARRAY] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};  // Declaración e inicializacion del array
uint8_t impares_array[PRUEBAS_ARRAY] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}; // Declaración e inicializacion del array
uint8_t resultado_suma_array[PRUEBAS_ARRAY];                                // Declaracion
uint8_t resultado_producto_pares[PRUEBAS_ARRAY];                            // Declaracion

esp_err_t multiplicar_arrays(void);

esp_err_t set_timer(void);
/**
 * @brief vTimerCallback
 * Esta funcion se llama cuando cada temporizador expira y adicional
 * cuenta la cantidad de veces que el temporizador asociado expira y lo detiene
 * una vez que ha expirado 10 veces, este control se hace con ayuda de la
 * variable xMaxExpiryCountBeforeStopping
 */
void vTimerCallback(TimerHandle_t pxTimer)
{
    int32_t lArrayIndex;
    static uint8_t contadorFuncion = 0; // Variable estatica para contar las veces que se entra en la función
    contadorFuncion++;
    ESP_LOGI(tag, "Entrando en la función vTimerCallback: %u veces", (int)contadorFuncion);
    const int32_t xMaxExpiryCountBeforeStopping = 10;
    configASSERT(pxTimer);                             // Which timer expired?
    lArrayIndex = (int32_t)pvTimerGetTimerID(pxTimer); // Increment the number of times that pxTimer has expired.
    lExpireCounters[lArrayIndex] += 1;                 // If the timer has expired 10 times then stop it from running.
    ESP_LOGW(tag, "Temporizador ID: %d | Expiraciones: %d", (int)lArrayIndex, (int)lExpireCounters[lArrayIndex]);

    if (lExpireCounters[lArrayIndex] == xMaxExpiryCountBeforeStopping)
    {
        // Do not use a block time if calling a timer API function from a
        // timer callback function, as doing so could cause a deadlock!
        xTimerStop(pxTimer, 0);
    }

    switch (lArrayIndex)
    {
    case 0:
        DesbordadoTimer0();
        if ((lArrayIndex == 0) & (lExpireCounters[lArrayIndex] == 10))
        {
            add_arrays(pares_array, impares_array, resultado_suma_array, PRUEBAS_ARRAY);
        }
        break;
    case 1:
        DesbordadoTimer1();
        if ((lArrayIndex == 1) & (lExpireCounters[lArrayIndex] == 10))
        {
            product_arrays(pares_array, impares_array, resultado_suma_array, PRUEBAS_ARRAY);
        }
        break;
    case 2:
        DesbordadoTimer2();
        if ((lArrayIndex == 2) & (lExpireCounters[lArrayIndex] == 10))
        {
            printf("El timer 2 ha expirado 10 veces\n");
            multiplicar_arrays();
        }
        break;
    case 3:
        DesbordadoTimer3();
        break;
    case 4:
        DesbordadoTimer4();
        break;
    default:
        printf("Esta impresion nunca se deberia ejecutar\n");
        break;
    }
}
/**
 * @brief app_main
 * Configura los pin(es) a usar
 * Configura el timer
 */
void app_main(void)
{
    init_led();
    set_timer();
}
/**
 * set_timer
 * @brief Configura el timer así:
 * Funcion xTimerCreate crea y configura el timer
 * "Timer": es el nombre, no es usado por el Kernel
 * (pdMS_TO_TICKS(interval)): función alternativa que pasa de ms a ticks para definir
 * pdFALSE, este parámetro hace que solo se ejecute una vez y se validó operación
 * es una alternativa a (100 * (x + 1)), este el periodo en ticks.
 * vTimerCallback: función definida en la libreria "timers.h"
 * pdTRUE: Este parametro afirma que se debe recargar el timer
 * @return ok
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
        xTimers[x] = xTimerCreate("Timer",
                                  (100 * (x + 1)), // The timer period in ticks.
                                  pdTRUE,          // El timer se autorecargará cuando expire.
                                  (void *)x,       // Assign each timer a unique id equal to its array index.
                                  vTimerCallback); // Cada timer llama la misma función callback cuando termina
        if (xTimers[x] == NULL)
        {
            ESP_LOGE(tag, "The timer was not created.");
        }
        else
        {
            if (xTimerStart(xTimers[x], 0) != pdPASS)
            {
                ESP_LOGE(tag, "The timer could not be set into the active state");
            }
        }
    }
    return ESP_OK;
}

/* esp_err_t multiplicar_arrays(void)
{
    uint8_t iteration = 0;
    printf("\n");
    ESP_LOGI(tag, "***Entra en la funcion multiplicar***");

    while (iteration < PRUEBAS_ARRAY)
    {
        resultado_producto_pares[iteration] = pares_array[iteration] * 2;
        printf("Indice pares_array: %d | Contenido pares_array: %d \n", (uint8_t)iteration, (uint8_t)pares_array[iteration]);
        iteration++;
    }
    print_arrays(resultado_producto_pares, PRUEBAS_ARRAY);
    return ESP_OK;
} */