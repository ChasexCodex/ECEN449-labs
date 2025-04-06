// #include "mbed.h"
// #include <chrono>

// using namespace chrono;
// using namespace ThisThread;

// Timer timer;
// Timeout maxTime;

// InterruptIn button(BUTTON1);
// DigitalOut led(LED1);

// milliseconds signal_starts[10];
// milliseconds signal_durations[10];
// volatile int currentSignalIndex = 0;

// typedef enum { IDLE, START, RECORD, DISPLAY } State;

// volatile State state = IDLE;

// void reset() {
//   state = IDLE;
//   currentSignalIndex = 0;
//   for (int i = 0; i < 10; i++) {
//     signal_starts[i] = milliseconds(0);
//     signal_durations[i] = milliseconds(0);
//   }
//   led = 0;
//   timer.reset();
// }

// void alert() {
//   for (int i = 0; i < 20 * 2; i++) {
//     led = !led;
//     sleep_for(50ms);
//   }
// }

// void display() {
//   if (currentSignalIndex == 0)
//     return;
//   milliseconds previous_time = signal_starts[0];

//   for (int i = 0; i < currentSignalIndex; i++) {
//     sleep_for(signal_starts[i] - previous_time);
//     led = 1;
//     sleep_for(signal_durations[i]);
//     led = 0;
//     previous_time = signal_starts[i] + signal_durations[i];
//   }
// }

// void button_down() {
//   if (state == IDLE) {
//     state = START;
//     timer.start();
//     maxTime.attach([] {
//         timer.stop();
//         if (currentSignalIndex > 0) {
//             state = DISPLAY;
//         } else {
//             state = IDLE;
//         }
//     }, 10s);
//   } else if (state == RECORD) {
//     led = 1;
//     signal_starts[currentSignalIndex] = duration_cast<milliseconds>(timer.elapsed_time());
//   }
// }

// void button_up() {
//   if (state != RECORD)
//     return;

//   led = 0;
//   signal_durations[currentSignalIndex] = 
//     duration_cast<milliseconds>(timer.elapsed_time()) - signal_starts[currentSignalIndex];
//   currentSignalIndex++;
//   if (currentSignalIndex == 10) {
//     state = DISPLAY;
//     maxTime.detach();
//     timer.stop();
//   }
// }

// int main() {
//   button.fall(button_down);
//   button.rise(button_up);

//   while (true) {
//     if (state == START) {
//       alert();
//       state = RECORD;
//     }

//     if (state == DISPLAY) {
//       alert();
//       sleep_for(1s);
//       display();
//       sleep_for(1s);
//       alert();
//       reset();
//     }

//     __WFI();
//   }
// }

