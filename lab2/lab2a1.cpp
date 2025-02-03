// #include "mbed.h"

// DigitalOut led1(LED1);
// InterruptIn button(BUTTON1);

// volatile bool on = false;

// void button_down() { 
//     on = !on;
// }

// int main() {
//   button.fall(&button_down);

//   while (true) {
//     if (on) {
//       led1 = 0;
//       ThisThread::sleep_for(50ms);
//     } else if (on) {
//       led1 = !led1;
//       ThisThread::sleep_for(500ms);
//     }
//   }
// }
