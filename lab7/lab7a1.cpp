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

// BufferedSerial serial_port(USBTX, USBRX);

// int main() {
//     serial_port.set_format();
//     serial_port.set_baud(9600);

//     rgb_led = 0b111;

//     while (true) {
//         char c;
//         serial_port.read(&c, 1);
//         auto it = led_map.find(c);
//         if (it != led_map.end()) {
//             rgb_led = it->second.color;
//             printf("LED is %s\n", it->second.state);
//         } else {
//             printf("Invalid character\n");
//         }
//     }
// }
