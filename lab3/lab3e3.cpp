// #include "mbed.h"

// BusOut rgb_led(D8, D9, D5);

// InterruptIn joystick_up(A2);
// InterruptIn joystick_left(A4);
// InterruptIn joystick_right(A5);

// volatile int current_color = 0b011;

// void on_up() {
//     current_color = 0b011; // red
// }

// void on_right() {
//     current_color = 0b110; // blue
// }

// void on_left() {            
//     current_color = 0b101; // green
// }


// int main() {
//     joystick_up.fall(&on_up);
//     joystick_left.fall(&on_left);
//     joystick_right.fall(&on_right);
    

//     while (true) {
//         rgb_led = current_color;
//         ThisThread::sleep_for(500ms);
//         rgb_led = 0b111;
//         ThisThread::sleep_for(500ms);
//     }
// }
