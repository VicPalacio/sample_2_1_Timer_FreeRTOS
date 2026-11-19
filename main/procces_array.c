#include <stdio.h>   // /home/victor/.espressif/v6.1/esp-idf/components/esp_libc/platform_include
#include "esp_log.h" // /home/victor/.espressif/v6.1/esp-idf/components/log/include
#include "procces_array.h"

static const char *tag = "PROCCES_ARRAY"; // led.c es el módulo donde se está usando la librería

esp_err_t add_arrays(const uint8_t array_a[], const uint8_t array_b[], uint8_t array_result[], uint8_t size)
{
    uint8_t iteration = 0;
    printf("\n");
    ESP_LOGI(tag, "***Entra en la funcion sumar***");

    while (iteration < size)
    {
        array_result[iteration] = array_a[iteration] + array_b[iteration];
        printf("Indice resultado_suma: %d | Contenido resultado_suma: %d \n", (uint8_t)iteration, (uint8_t)array_result[iteration]);
        iteration++;
    }
    printf("\n");
    return ESP_OK;
}

esp_err_t subtracion_arrays(const uint8_t array_a[], const uint8_t array_b[], uint8_t array_result[], uint8_t size)
{
    uint8_t iteration = 0;
    printf("\n");
    ESP_LOGI(tag, "***Entra en la función restar***");

    while (iteration < size)
    {
        array_result[iteration] = array_a[iteration] - array_b[iteration];
        printf("Indice resultado_resta: %d | Contenido resultado_resta: %d \n", (uint8_t)iteration, (uint8_t)array_result[iteration]);
        iteration++;
    }
    printf("\n");
    return ESP_OK;
}

esp_err_t delete_array(uint8_t array[], uint8_t size)
{
    printf("\n");
    ESP_LOGI(tag, "***Entra en la funcion borrar***");

    for (size_t iteration = 0; iteration < size; iteration++)
    {
        array[iteration] = 0;
    }
    printf("Array borrada\n");
    return ESP_OK;
}

esp_err_t product_arrays(const uint8_t array_a[], const uint8_t array_b[], uint8_t array_result[], uint8_t size)
{
    uint8_t iteration = 0;
    printf("\n");
    ESP_LOGI(tag, "***Entra en la funcion producto matrices***");

    while (iteration < size)
    {
        array_result[iteration] = array_a[iteration] * array_b[iteration];
        printf("Indice resultado_product: %d | Contenido resultado_product: %d \n", (uint8_t)iteration, (uint8_t)array_result[iteration]);
        iteration++;
    }
    printf("\n");
    return ESP_OK;
}

esp_err_t print_arrays(uint8_t array[], uint8_t size)
{
    int i = 0;

    printf("\n");
    ESP_LOGI(tag, "***Entra en la funcion print_arrays***");

    printf("Result ={");

    while (i < size)
    {
        if (i < size - 1)
        {
            printf("%d, ", array[i]);
        }
        else
        {
            printf("%d}\n", array[i]);
        }
        i++;
    }
    printf("\n");
    return ESP_OK;
}