// #include "mbed.h"

// PwmOut red(D8);
// PwmOut green(D9);
// PwmOut blue(D5);

// InterruptIn joystick_up(A2);
// InterruptIn joystick_left(A4);
// InterruptIn joystick_right(A5);

// volatile int color_state = 0b001;
// AnalogIn pot(A0);

// void set_color(int state) {
//     color_state = state;
// }

// int main() {
//     joystick_up.fall([] { color_state = 0b100; });
//     joystick_left.fall([] { color_state = 0b001; });
//     joystick_right.fall([] { color_state = 0b010; });

//     while (true) {
//         float alpha = pot.read();
//         red.write(1 - alpha * ((color_state >> 2) & 1));
//         green.write(1 - alpha * ((color_state >> 1) & 1));
//         blue.write(1 - alpha * (color_state & 1));

//         ThisThread::sleep_for(20ms);
//     }
// }
