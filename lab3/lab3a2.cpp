// #include "mbed.h"

// BusOut rgb_led(D8, D9, D5);
// InterruptIn joystick_center(D4);

// int color_sequence[] = {0b011, 0b001, 0b101, 0b100, 0b110, 0b010, 0b000};
// int num_colors = 7;
// volatile bool reverse_order = false;

// void on_center() {
//     reverse_order = !reverse_order;
// }


// int main() {
//     joystick_center.fall(&on_center);
//     int index = 0;

//     while (true) {
//         rgb_led = color_sequence[index];
//         ThisThread::sleep_for(500ms);
//         rgb_led = 0b111;
//         ThisThread::sleep_for(500ms);

//         if (reverse_order) {
//             index = (index - 1 + num_colors) % num_colors;
//         } else {
//             index = (index + 1) % num_colors;
//         }
//     }
// }
