// #include "mbed.h"
// #include <chrono>

// BusOut rgb_led(D8, D9, D5);

// InterruptIn joystick_up(A2);
// InterruptIn joystick_down(A3);

// int blink_rates[] = {100, 200, 400, 800, 1600};
// volatile int current_rate_index = 2;

// void on_up() {
//     if (current_rate_index > 0) current_rate_index--;
// }

// void on_down() {
//     if (current_rate_index < 4) current_rate_index++;
// }

// int main() {
//     joystick_up.fall(&on_up);
//     joystick_down.fall(&on_down);

//     while (true) {
//         rgb_led = 0b100; // cyan
//         ThisThread::sleep_for(chrono::milliseconds(blink_rates[current_rate_index]));
        
//         rgb_led = 0b111; // off
//         ThisThread::sleep_for(chrono::milliseconds(blink_rates[current_rate_index]));
//     }
// }
