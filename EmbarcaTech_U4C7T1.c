#include "pico/stdlib.h"  // Biblioteca padrão do Pico
#include "hardware/pwm.h" // Biblioteca para controle do PWM

#define PWM_PIN 22 // Pino do servo motor

#define WRAP_VALUE 20000 // Valor do WRAP do PWM
#define DIVIDER_VALUE 125.0f // Valor do divisor do PWM

#define PULSE_MAX 2400  // Valor do pulso para 180 graus
#define PULSE_90 1470  // Valor do pulso para 90 graus
#define PULSE_MIN 500  // Valor do pulso para 0 graus

#define SWEEP_STEP 5   // Valor de incremento do pulso
#define SWEEP_DELAY 10 // Delay entre incrementos

uint slice; // Slice do PWM

// Função para configurar o PWM
void setup_pwm(){
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
    slice = pwm_gpio_to_slice_num(PWM_PIN);
    pwm_set_wrap(slice, WRAP_VALUE);
    pwm_set_clkdiv(slice, DIVIDER_VALUE);
    pwm_set_enabled(slice, true);
}

// Função principal
int main()
{
    stdio_init_all(); // Inicializa a comunicação serial
    setup_pwm(); // Configura o PWM

    // Ajusta a posição do braço do servo motor para 180 graus
    pwm_set_gpio_level(PWM_PIN, PULSE_MAX);
    sleep_ms(5000);

    // Ajusta a posição do braço do servo motor para 90 graus
    pwm_set_gpio_level(PWM_PIN, PULSE_90);
    sleep_ms(5000);

    // Ajusta a posição do braço do servo motor para 0 graus
    pwm_set_gpio_level(PWM_PIN, PULSE_MIN);
    sleep_ms(5000);

    // Loop infinito para varrer o servo motor
    while (true){
        // Varre o servo motor de 0 a 180 graus
        for (uint16_t pulse = PULSE_MIN; pulse <= PULSE_MAX; pulse += SWEEP_STEP){
            pwm_set_gpio_level(PWM_PIN, pulse);
            sleep_ms(SWEEP_DELAY);
        }
        // Varre o servo motor de 180 a 0 graus
        for (uint16_t pulse = PULSE_MAX; pulse >= PULSE_MIN; pulse -= SWEEP_STEP){
            pwm_set_gpio_level(PWM_PIN, pulse);
            sleep_ms(SWEEP_DELAY);
        }
    }
}