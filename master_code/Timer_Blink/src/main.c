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

// GPIO pin with LED
#define BLINK_GPIO 12

// Tag for use in logging
static const char *TAG = "Timer Blink Example";

// Callback function prototype
static void periodic_timer_callback(void *arg);

// Duration between blinks (ms)
#define LED_DURATION 1000 

// LED states (0/false = off, 1/true = on)
static volatile bool led_state = false;

static void configure_led(void)
{
    ESP_LOGI(TAG, "Configuring to blink GPIO LED!");

    // Reset GPIO to default state
    gpio_reset_pin(BLINK_GPIO);
    // Set the GPIO as a push/pull output
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
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

    // Timer handle struct
    esp_timer_handle_t periodic_timer;

    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    // The timer has been created but is not running yet

    // Start the periodic timer and print a message
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LED_DURATION * 1000));
    ESP_LOGI(TAG, "Started periodic timer, time since boot: %lld us", esp_timer_get_time());
}
// Main method
void app_main(void)
{

    // Config LED
    configure_led();
    // Config Timer
    configure_timer();

    // Idle CPU with empty while loop
    while (1)
    {
    }
}

// Callback function toggles LED at every 1 second interval
static void periodic_timer_callback(void *arg)
{
    // Log time elapsed since timer boot
    int64_t time_since_boot = esp_timer_get_time();
    ESP_LOGI(TAG, "Periodic timer called, time since boot: %lld us", time_since_boot);

    // Toggle LED
    ESP_LOGI(TAG, "Turning the LED at GPIO pin %d %s!", BLINK_GPIO, (led_state) ? "ON" : "OFF"); // Log info
    gpio_set_level(BLINK_GPIO, !led_state);                                                      // Write to GPIO
    led_state = !led_state;                                                                    // Toggle state
}
