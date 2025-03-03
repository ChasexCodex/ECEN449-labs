// #include "mbed.h"
// #include <chrono>

// #define BLINKING_RATE 500ms

// DigitalOut red(D5);
// AnalogIn pot(A0);

// int main() {
//     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
//     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
//     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

//     GPIOA->MODER &= ~(3 << (9 * 2));
//     GPIOA->MODER |= (1 << (9 * 2));
//     GPIOB->MODER &= ~(3 << (4 * 2));
//     GPIOB->MODER |= (1 << (4 * 2));
//     GPIOC->MODER &= ~(3 << (7 * 2));
//     GPIOC->MODER |= (1 << (7 * 2));

//     while (true) {
//         for (int i = 0; i < 3; i++) { // loop the pins
//             GPIOB->BSRR = (1 << (4 + 16));
//             ThisThread::sleep_for(BLINKING_RATE);
//             GPIOB->BSRR = (1 << 4);
//             ThisThread::sleep_for(BLINKING_RATE);
//         }
//         for (int i = 0; i < 3; i++) { // loop the pins
//             GPIOC->BSRR = (1 << (7 + 16));
//             ThisThread::sleep_for(BLINKING_RATE);
//             GPIOC->BSRR = (1 << 7);
//             ThisThread::sleep_for(BLINKING_RATE);
//         }
//         for (int i = 0; i < 3; i++) { // loop the pins
//             GPIOA->BSRR = (1 << (9 + 16));
//             ThisThread::sleep_for(BLINKING_RATE);
//             GPIOA->BSRR = (1 << 9);
//             ThisThread::sleep_for(BLINKING_RATE);
//         }
//     }
// }
