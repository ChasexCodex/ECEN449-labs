// #include "mbed.h"
// #include <chrono>
// #include "mbed.h"
// #include <chrono>

// DigitalOut red(D5);
// AnalogIn pot(A0);

// int main() {
//     while (true) {
//         red = !red;

//         int level = (1 - pot) * 1000;

//         chrono::milliseconds sleepDuration(level < 100 ? 100 : level); // limit the sleep duration to a minimum of 100ms
//         ThisThread::sleep_for(sleepDuration);
//     }
// }
