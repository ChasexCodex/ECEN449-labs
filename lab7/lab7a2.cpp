// #include "mbed.h"
// #include <map>

// BusOut rgb_led(D8, D9, D5);

// struct LedState {
//     int color;
//     const char* state;
// };

// std::map<char, LedState> led_map = {
//     {'r', {0b011, "RED"}},
//     {'g', {0b101, "GREEN"}},
//     {'b', {0b110, "BLUE"}},
//     {'w', {0b000, "WHITE"}},
//     {'f', {0b111, "OFF"}}
// };

// const int HIGH_SPEED = 100;
// const int LOW_SPEED = 1000;

// BufferedSerial serial_port(USBTX, USBRX);
// volatile bool read_serial = false; 
// volatile int speed = LOW_SPEED;
// volatile int color = 0b111;

// void on_io() {
//     read_serial = true;
// }

// void read_and_parse() {
//     if (!read_serial && !serial_port.readable()) return;

//     char c;
//     serial_port.read(&c, 1);
//     auto it = led_map.find(c);
//     if (it != led_map.end()) {
//         color = it->second.color;
//         printf("LED is %s\n", it->second.state);
//     } else if (c == '1') {
//         speed = HIGH_SPEED;
//         printf("Blinking fast\n");
//     } else if (c == '2') {
//         speed = LOW_SPEED;
//         printf("Blinking slow\n");
//     } else {
//         printf("Invalid character\n");
//     }

//     read_serial = false;
// }

// int main() {
//     serial_port.set_format();
//     serial_port.set_baud(9600);
//     serial_port.sigio(&on_io);

//     while (true) {
//         read_and_parse();

//         rgb_led = 0b111;
//         ThisThread::sleep_for(chrono::milliseconds(speed));
//         rgb_led = color;
//         ThisThread::sleep_for(chrono::milliseconds(speed));
//     }
// }
