// Author: Aly Megahed
// ESP-32 Code written using ESP-IDF

/* Description Blink Example with 4 LEDs connected to GPIO pins 1,0,3 and 2.
   Toggles the LEDs simultaenously every 1000 ms. Uses timer to generate delay.
 */

#include <stdio.h>
#include <unistd.h>
#include "esp_timer.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "sdkconfig.h"
#include "led_strip.h"

// Tag for use in logging
static const char *TAG = "Timer Blink Example";

// Callback function prototype
static void periodic_timer_callback(void *arg);

#define LED_DURATION 1000 // Duration between blinks (ms)

// Array of GPIO pin numbers
const uint8_t blinkGPIO[] = {1,0,3,2};

// Array of respective LED states for each of those numbers (0 = off, 1 = on)
static bool s_led_state = false;

static void toggle_led(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        ESP_LOGI(TAG, "Turning the LED at GPIO pin %d %s!", blinkGPIO[i], (s_led_state) ? "ON" : "OFF"); // Log info
        gpio_set_level(blinkGPIO[i], !s_led_state);   // Write to GPIO
    }
    s_led_state = !s_led_state; // Toggle state
}


static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LEDs!");
    
    // Apply to each GPIO pin
    for(uint8_t i = 0; i < 4; i++)
    {
        // Reset GPIO to default state
        gpio_reset_pin(blinkGPIO[i]);
        // Set the GPIO as a push/pull output
        gpio_set_direction(blinkGPIO[i], GPIO_MODE_OUTPUT);
    }

}

// Main method
void app_main(void)
{

    // Config LEDs
    configure_led();

    /* Create 1 timer:
     * 1. a periodic timer which will run every 0.5s, and print a message
    */

    // Set fields/arguments for timer
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &periodic_timer_callback,
        /* name is optional, but may help identify the timer when debugging */
        .name = "periodic",
        .skip_unhandled_events = true};

    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    /* The timer has been created but is not running yet */

    /* Start the periodic timer */
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LED_DURATION * 1000));
    ESP_LOGI(TAG, "Started periodic timer, time since boot: %lld us", esp_timer_get_time());

while(1)
{
    
}
}

static void periodic_timer_callback(void *arg)
{
    int64_t time_since_boot = esp_timer_get_time();
    ESP_LOGI(TAG, "Periodic timer called, time since boot: %lld us", time_since_boot);
    toggle_led();
    
}