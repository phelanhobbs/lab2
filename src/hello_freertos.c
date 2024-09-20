#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

#include "functions.h"

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void blink_task(__unused void *params)
{
    // Initialize wireless hardware and check okay
    hard_assert(cyw43_arch_init() == PICO_OK);

    int count = 0;
    bool on = false;

    while (true) {
        blink_update(&count, &on);

        printf(on ? "true": "false");
        // printf("%d", count);

        // Update the GPIO LED pin to current LED state
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
    }
}


void main_task(__unused void *params)
{
    // Create a task called BlinkThread
    xTaskCreate(blink_task, "BlinkThread", BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    
    // Initialize local vars
    char in, out;
    
    // Loop through all characters until getchar is false
    while(in = getchar()) {
        invert_case(in, &out);
	    putchar(out);
    }
}

int main( void )
{
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t task;

    // Create a task called mainThread
    xTaskCreate(main_task, "MainThread", MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    
    // Start the task scheduler
    vTaskStartScheduler();
    return 0;
}
