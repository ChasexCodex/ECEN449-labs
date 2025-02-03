// #include "mbed.h"


// // Blinking rate in milliseconds
// #define BLINKING_RATE 500ms

// DigitalOut led1(LED1);
// InterruptIn button(BUTTON1);

// volatile bool is_pressed = false;

// void button_down() {
//     is_pressed = true;
// }

// void button_up() {
//     is_pressed = false;
// }


// int main()
// {
//     button.fall(&button_down);
//     button.rise(&button_up);

//     while (true) {
//         if (is_pressed) {
//             led1 = 1;
//         }
//         else {
//             led1 = !led1;
//         }

//         ThisThread::sleep_for(500ms);
//     }
// }

