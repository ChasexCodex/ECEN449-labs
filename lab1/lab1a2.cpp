// #include "mbed.h"

// int main()
// {
//     DigitalOut led1(LED1);
//     DigitalIn button1(BUTTON1);
//     led1 = 0;

//     bool pressed = false;

//     while (true) {
//         if (button1 == 0) {
//             pressed = true;
//         }

//         ThisThread::sleep_for(50ms);

//         if (pressed) {
//             led1 = !led1;
//             ThisThread::sleep_for(500ms);
//         }
//     }
// }
