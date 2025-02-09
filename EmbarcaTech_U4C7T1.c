#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

const uint LED_PIN = 12;
const uint SERVO_PIN = 22;
const uint16_t PWM_WRAP = 2000;
const float PWM_DIVISER = 2.0f;
const uint16_t STEP = 5;

int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
