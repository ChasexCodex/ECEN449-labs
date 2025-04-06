// #include "mbed.h"

// #define SPEED_DIFFICULTY 500ms  // lower this to increase difficulty
// #define NUM_OF_CLICKS 7         // increase this to increase difficulty 

// DigitalOut led(LED1);
// InterruptIn button(BUTTON1);
// Ticker gameTicker;
// Timeout offToggler;

// volatile uint8_t state = 0;
// volatile uint8_t win = false;

// int main() {
//     // decrement the state based on difficulty
//     gameTicker.attach([]{
//         state = (state - 1) >= 0 ? (state - 1) : 0;
//     }, SPEED_DIFFICULTY);

//     button.fall([]{
//         state += 1;
//         led = 1;

//         if (state >= NUM_OF_CLICKS) {
//             gameTicker.detach();
//             button.fall(0);
//         }
//         else offToggler.attach([]{led = 0;}, 50ms);
//     });

//     while (true) {
//         __WFI();
//     }
// }