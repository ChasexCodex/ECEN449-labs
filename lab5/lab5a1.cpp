// #include "mbed.h"

// DigitalOut led(LED1);
// Timeout timeout;
// InterruptIn button(BUTTON1);
// volatile uint8_t state = 0; 

// int main() {
//     button.fall([]{
//         state = (state + 1) % 3;
//     });

//     timeout.attach([]{
//         button.fall(NULL);
//     }, 30s);

//     while (true) {
//         if (state == 0) {
//             led = 1;
//             ThisThread::sleep_for(10ms);
//         } else if (state == 1) {
//             led = !led;
//             ThisThread::sleep_for(200ms);
//         } else {
//             led = 0;
//             ThisThread::sleep_for(10ms);
//         }
//     }
// }
