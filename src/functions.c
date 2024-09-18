#include "functions.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

int count = 0;
bool on = false;

void blink()
{
    // Update the GPIO LED pin to current LED state
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
        
    // Do not toggle every 11th pulse
    if (count++ % 11)
        // Toggle LED state
        on = !on;

        // Delay 1 second
        vTaskDelay(1000);
}