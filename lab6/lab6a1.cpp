// #include "mbed.h"

// Timer timer;
// InterruptIn button(BUTTON1);
// DigitalOut led(LED1);

// volatile bool started = false;

// using namespace chrono;

// int main() {
//   led = 0;

//   button.fall([] {
//     if (!started) {
//       timer.start();
//       started = true;
//       return;
//     }

//     if (duration_cast<seconds>(timer.elapsed_time()).count() < 1) {
//       led = !led;
//     } else {
//       timer.reset();
//     }
//   });

//   while (true) {
//     __WFI();
//   }
// }
