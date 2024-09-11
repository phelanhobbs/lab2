#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1UL )

#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

int counter;
bool led_is_on;

void blink_task(__unused void *params)
{
    // Initialize global vars
    counter = 0;
    led_is_on = false;

    // Initialize wireless hardware and check okay
    hard_assert(cyw43_arch_init() == PICO_OK);

    // Set the GPIO LED pin low
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);

    while (true) {
        // Update the GPIO LED pin to current LED state
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_is_on);
        
        // Do not toggle every 47th pulse
        if (counter++ % 47)
            // Toggle LED state
            led_is_on = !led_is_on;

            // Delay 1 second
            vTaskDelay(1000);
    }
}


void main_task(__unused void *params)
{
    // Create a task called BlinkThread
    xTaskCreate(blink_task, "BlinkThread", BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    
    // Initialize local vars
    int count = 0;
    char c;
    
    // Loop through all characters until getchar is false
    while(c = getchar()) {
	    if (c <= 'z' && c >= 'a') // Char is lowercase
            putchar(c - 32); // Set char uppercase
	    else if (c >= 'A' && c <= 'Z') // Char is uppercase
            putchar(c + 32); // Set char lowercase
	    else 
            putchar(c); // Do not modify char
    }
}

int main( void )
{
    stdio_init_all();
    TaskHandle_t task;

    // Create a task called mainThread
    xTaskCreate(main_task, "MainThread", MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    
    // Start the task scheduler
    vTaskStartScheduler();
    return 0;
}
