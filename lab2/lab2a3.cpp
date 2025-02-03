// #include "mbed.h"

// DigitalOut led1(LED1);
// InterruptIn button(BUTTON1);

// int state = 0;

// void button_down() {
//   if (state == 0) {
//     state = 1;
//   } else if (state == 1) {
//     state = 2;
//   } else if (state == 2) {
//     state = 0;
//   }
// }

// int main() {
//   button.fall(&button_down);

//   while (true) {
//     if (state == 0) {
//       led1 = 0;
//     } else if (state == 1) {
//       led1 = 1;
//     } else if (state == 2) {
//       led1 = !led1;
//     }

//     ThisThread::sleep_for(500ms);
//   }
// }
