// #include "mbed.h"

// DigitalOut led(LED1);
// BusOut rgb(D5, D9, D8);
// Ticker interval;

// volatile uint8_t state = 0; 

// uint8_t colors[] = {
//     0b000,
//     0b001,
//     0b010,
//     0b011,
//     0b100,
//     0b101,
//     0b110,
// };

// int main() {
//     interval.attach([]{
//         state = (state + 1) % (sizeof(colors) / sizeof(colors[0]));
//     }, 5s);

//     while (true) {
//         rgb = 0b111;
//         ThisThread::sleep_for(500ms);
//         rgb = colors[state];
//         ThisThread::sleep_for(500ms);
//     }
// }
