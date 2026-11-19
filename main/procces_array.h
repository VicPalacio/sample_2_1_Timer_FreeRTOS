#ifndef PROCCES_ARRAY_H
#define PROCCES_ARRAY_H

#include <stdint.h>
#include <stddef.h>
#include "esp_err.h"

esp_err_t add_arrays(const uint8_t array_a[], const uint8_t array_b[], uint8_t array_result[], uint8_t size);
esp_err_t product_arrays(const uint8_t array_a[], const uint8_t array_b[], uint8_t array_result[], uint8_t size);
esp_err_t subtracion_arrays(const uint8_t array_a[], const uint8_t array_b[], uint8_t array_result[], uint8_t size);
esp_err_t delete_array(uint8_t array[], uint8_t size);
esp_err_t print_arrays(uint8_t array[], uint8_t size);

#endif