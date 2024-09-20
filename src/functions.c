#include "FreeRTOS.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

#include "functions.h"

void invert_case(char in, char *out)
{
    if (in <= 'z' && in >= 'a') // Char is lowercase
        *out = (in - 32); // Set char uppercase
    else if (in >= 'A' && in <= 'Z') // Char is uppercase
        *out = (in + 32); // Set char lowercase
    else 
        *out = in; // Do not modify char
}

void blink_update(int *counter, bool *state)
{
    // Do not toggle every 11th pulse
    if ((*counter)++ % 11)
    {
        // Toggle LED state
        *state = !(*state);
    }

    // Delay 0.5 second
    vTaskDelay(500);
}