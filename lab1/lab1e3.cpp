// #include "mbed.h"


// // Blinking rate in milliseconds
// #define BLINKING_RATE 500ms


// int main()
// {
//     DigitalOut red(D5);
//     DigitalOut green(D9);
//     DigitalOut blue(D8);

//     red = green = blue = 1;

//     while (true) {
//         for (int i = 0; i < 10; i++) {
//             red = !red;
//             ThisThread::sleep_for(BLINKING_RATE);
//         }

//         for (int i = 0; i < 10; i++) {
//             green = !green;
//             ThisThread::sleep_for(BLINKING_RATE);
//         }

//         for (int i = 0; i < 10; i++) {
//             blue = !blue;
//             ThisThread::sleep_for(BLINKING_RATE);
//         }
//     }
// }
