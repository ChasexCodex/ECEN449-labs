// #include "mbed.h"
// #include <chrono>

// DigitalOut red(D5);
// AnalogIn pot1(A0);
// AnalogIn pot2(A1);


// int main() {
//     while (true) {

//         int onLevel = (1 - pot1) * 1000;
//         int offLevel = (1 - pot2) * 1000;
        

//         chrono::milliseconds onDuration(onLevel < 100 ? 100 : onLevel);
//         chrono::milliseconds offDuration(offLevel < 100 ? 100 : offLevel);

//         red = !red;
//         ThisThread::sleep_for(onDuration);
//         red = !red;
//         ThisThread::sleep_for(offDuration);
//     }
// }
