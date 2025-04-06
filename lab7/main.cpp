// #include "mbed.h"
// #include "C12832.h"

// // Using notation
// C12832 lcd(D11, D13, D12, D7, D10);


// int main()
// {
//     int j=0;
//     lcd.cls();
//     lcd.locate(0,3);
//     lcd.printf("mbed application shield!");

//     while(true) {   // this is the main thread
//         lcd.locate(0,15);
//         lcd.printf("Counting : %d",j);
//         j++;
//         ThisThread::sleep_for(1000ms);
//     }
// }