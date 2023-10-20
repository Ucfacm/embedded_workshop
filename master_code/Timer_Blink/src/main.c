// Author: Aly Megahed
// ESP-32 Code written using ESP-IDF

/* Description: Blink Example with 1 LED connected to GPIO pins 1.
   Toggles the LED every 1000 ms. Uses hardware timer to generate delay.
 */

#include <stdio.h>
#include <unistd.h>
#include "esp_timer.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "sdkconfig.h"

// Tag for use in logging
static const char *TAG = "Timer Blink Example";

// Callback function prototype
static void periodic_timer_callback(void *arg);

#define LED_DURATION 1000 // Duration between blinks (ms)

// GPIO pin number
const uint8_t blinkGPIO = 1;

// Array of respective LED states for each of those numbers (0 = off, 1 = on)
static volatile bool s_led_state = false;


static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    
    // Reset GPIO to default state
    gpio_reset_pin(blinkGPIO);
    // Set the GPIO as a push/pull output
    gpio_set_direction(blinkGPIO, GPIO_MODE_OUTPUT);

}

static void configure_timer()
{
    // Create periodic timer which will run every 1s, and toggle the LED
     

    // Set fields/arguments for timer (args struct)
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &periodic_timer_callback,
        // name is optional, but may help identify the timer when debugging 
        .name = "periodic",
        .skip_unhandled_events = true};

    // handle struct 
    esp_timer_handle_t periodic_timer;

    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    /* The timer has been created but is not running yet */

    // Start the periodic timer and print a message
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LED_DURATION * 1000));
    ESP_LOGI(TAG, "Started periodic timer, time since boot: %lld us", esp_timer_get_time());
}
// Main method
void app_main(void)
{

    // Config LEDs
    configure_led();
    // Config Tiemer
    configure_timer();
    
    // Idle CPU with empty while loop
    while(1)
    {
    
    }
}

// Callback function toggles LED at every 1 second interval
static void periodic_timer_callback(void *arg)
{
    ESP_LOGI(TAG, "Turning the LED at GPIO pin %d %s!", blinkGPIO, (s_led_state) ? "ON" : "OFF"); // Log info
    gpio_set_level(blinkGPIO, !s_led_state);                                                      // Write to GPIO
    s_led_state = !s_led_state;                                                                   // Toggle state
}

