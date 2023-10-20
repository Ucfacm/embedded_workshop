// Author: Aly Megahed
// ESP-32 Code written using ESP-IDF

/* Description: Blink Example with 1 LED connected to GPIO pin 1.
   Toggles the LED every 1000 ms. Uses FreeRTOS ticks to generate delay.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

// GPIO pin with LED
#define BLINK_GPIO 1

// Number of Tick periods in 1000 ms
#define TICK_PERIODS 1000 / portTICK_PERIOD_MS

// Tag for use in logging
static const char *TAG = "Simple Blink Example";

// Resets GPIO pin and sets as output
void config_led()
{
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}


void app_main()
{
    volatile bool led_state = false;

    config_led();

    while (1)
    {
        ESP_LOGI(TAG, "Turning the LED at GPIO pin %d %s!", BLINK_GPIO, (led_state) ? "ON" : "OFF"); // Log info
        gpio_set_level(BLINK_GPIO, led_state); // Write to  LED
        vTaskDelay(TICK_PERIODS); // Delay for tick periods
        led_state = !led_state; // Toogle state

    }
}