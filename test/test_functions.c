#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"

#include "functions.h"

void setUp(void) {}

void tearDown(void) {}

void test_invert_case()
{
    char in[6] = {'a', 'B', 'c', 'D', '1', '!'};
    char expected[6] = {'A', 'b', 'C', 'd', '1', '!'};

    char out;

    for (uint8_t i = 0; i < 6; i++)
    {
        invert_case(in[i], &out);
        TEST_ASSERT_TRUE_MESSAGE(expected[i] == out, "Case inversion returned wrong value");
    }
}

int main (void)
{
    stdio_init_all();
    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_invert_case);
    sleep_ms(5000);
    return UNITY_END();
}