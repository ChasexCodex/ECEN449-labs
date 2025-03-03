// #include "mbed.h"

// BusOut rgb_led(D8, D9, D5);

// InterruptIn joystick_up(A2);
// InterruptIn joystick_right(A5);

// int color_sequence[] = {0b011, 0b001, 0b101, 0b100, 0b110, 0b010, 0b000};
// int num_colors = 7;
// int blink_rates[] = {100, 200, 400, 800, 1600};
// int num_rates = 5;

// volatile int color_index = 0;
// volatile int rate_index = 2;

// void on_up() {
//     rate_index = (rate_index - 1 + num_rates) % num_rates;
// }

// void on_right() {
//     color_index = (color_index + 1) % num_colors;
// }

// int main() {
//     joystick_up.fall(&on_up);
//     joystick_right.fall(&on_right);

//     while (true) {
//         rgb_led = color_sequence[color_index];
//         ThisThread::sleep_for(chrono::milliseconds(blink_rates[rate_index]));
//         rgb_led = 0b111;
//         ThisThread::sleep_for(chrono::milliseconds(blink_rates[rate_index]));
//     }
// }
