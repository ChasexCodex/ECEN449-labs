// #include "mbed.h"

// DigitalOut led(LED1);

// BufferedSerial serial_port(USBTX, USBRX);

// char input() {
//     char c;
//     serial_port.read(&c, 1);
//     return c;
// }

// int main()
// {
//     serial_port.set_format();
//     serial_port.set_baud(9600);

//     while(true) {
//         char c = input();
//         switch (c) {
//             case 'o':
//                 led = 1;
//                 printf("LED is ON\n");
//             break;
//             case 'f':
//                 led = 0;
//                 printf("LED is OFF\n");
//             break;
//             case 't':
//                 led = !led;
//                 printf("LED is toggled\n");
//             break;
//             default:
//                 printf("Invalid character\n");
//             break;
//         }
//     }
// }