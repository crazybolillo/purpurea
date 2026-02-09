#include <stm32f0xx_ll_gpio.h>

int main(void) {
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);

    while (1) {
        for (int i = 0; i < INT32_MAX; i++) {
            LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
        }
    }
}
