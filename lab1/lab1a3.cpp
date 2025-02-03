// #include "mbed.h"

// #define GREEN_WAIT 5s
// #define YELLOW_WAIT 2s
// #define RED_WAIT 6s

// int main()
// {
//     DigitalOut red(D5);
//     DigitalOut green(D9);
//     DigitalOut blue(D8);

//     green = red = blue = 1;

//     while (true) {
//         green = 0;
//         ThisThread::sleep_for(GREEN_WAIT);

//         red = 0;
//         ThisThread::sleep_for(YELLOW_WAIT);

//         green = 1;
//         ThisThread::sleep_for(GREEN_WAIT);
//         red = 1;
//     }
// }
