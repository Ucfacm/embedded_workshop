// Author: Aly Megahed
// ESP-32 Code written using ESP-IDF

/* Description: Turns on LED when pushbutton is pressed. 
   Uses polling to check if pusbutton is pressed. Pushbutton
   is configured as pull-down (1 = pressed, 0 = not pressed). 
 */

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN 1
#define PUSH_BUTTON_PIN 2

void conifg_gpio()
{
    // Reset GPIO pins and then set their directions
    gpio_reset_pin(LED_PIN);
    gpio_reset_pin(PUSH_BUTTON_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); // LED is output 
    gpio_set_direction(PUSH_BUTTON_PIN, GPIO_MODE_INPUT); // Pushbutton is input
}

void app_main(void)
{
    // Config GPIO pins
    config_gpio();

    // Polling pushbutton to see if it is pressed
    while (1)
    {
        if (gpio_get_level(PUSH_BUTTON_PIN) == 1)
        {
            gpio_set_level(LED_PIN, 1);
        }
        else
        {
            gpio_set_level(LED_PIN, 0);
        }

        vTaskDelay(1);
    }
}