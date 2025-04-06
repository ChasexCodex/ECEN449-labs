// #include "mbed.h"

// DigitalOut led(LED1);

// const int HIGH_SPEED = 100;
// const int LOW_SPEED = 1000;

// BufferedSerial serial_port(USBTX, USBRX);
// volatile int speed = LOW_SPEED;
// volatile bool blink = true;
// volatile bool read_serial = false;


// char input() {
//     char c;
//     serial_port.read(&c, 1);
//     return c;
// }

// void on_io() {
//     read_serial = true;
// }

// void read_and_parse() {
//     if (!read_serial && !serial_port.readable()) return;

//     char c = input();
//     switch (c) {
//         case 'f':
//             speed = HIGH_SPEED;
//             blink = true;
//             printf("Blinking is HIGH\n");
//         break;
//         case 's':
//             speed = LOW_SPEED;
//             blink = true;
//             printf("Blinking is LOW\n");
//         break;
//         case 'n':
//             blink = false;
//             printf("Not blinking\n");
//         break;
//         default:
//             printf("Invalid character");
//         break;
//     }

//     read_serial = false;
// }


// int main()
// {
//     serial_port.set_format();
//     serial_port.set_baud(9600);
//     serial_port.sigio(&on_io);

//     while(true) {
//         read_and_parse();

//         if (blink) {
//             led = !led;
//             ThisThread::sleep_for(chrono::milliseconds(speed));
//         } else {
//             ThisThread::sleep_for(10ms);
//         }
//    }
// }