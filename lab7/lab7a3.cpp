// #include "mbed.h"
// #include "C12832.h"

// C12832 lcd(D11, D13, D12, D7, D10);
// BufferedSerial serial_port(USBTX, USBRX);

// int main()
// {
//     serial_port.set_format();
//     serial_port.set_baud(9600);
//     lcd.cls();
//     lcd.locate(0,3);
//     while(true) {
//         char c;
//         serial_port.read(&c, 1);
//         lcd.printf("%c", c);
//     }
// }
