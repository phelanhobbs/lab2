

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "FreeRTOS.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

void blink_update(int *counter, bool *state);

void invert_case(char in, char *out);

#endif