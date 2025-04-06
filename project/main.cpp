#include "mbed.h"
#include "C12832.h"
#include "operation.h"
#include <cstdio>
#include <string>
#include <sstream>

#define ENTER '\n'
#define RETURN '\r'
#define MAX_INPUT 30
#define BACKSPACE 127
#define UP 'w'
#define DOWN 's'
#define RESET 'z'
#define IDLE_TIMEOUT_CLEAR_DURATION 60s

// C12832 lcd(D11, D13, D12, D7, D10);
BufferedSerial serial_port(USBTX, USBRX);

DigitalOut led(LED1);
// AnalogIn pot(A0);
// InterruptIn joystick_up(A2);
// InterruptIn joystick_down(A3);

Timeout blink_alert_timeout;
Timeout idle_timeout;

std::string input("");
bool is_evaluated = false;
double result = 0;
bool is_stored = false;
double stored_result = 0;
bool read_flag = false;
bool clear_flag = false;

bool is_expression_input(char c) {
    return std::isdigit(c) || (std::string("+-*/^.()sincostansqrtpi").find(c) != std::string::npos);
}

void display_input() {
    // lcd.cls();
    // lcd.printf("%s", input.c_str());
    printf("\x1B[2J\x1B[H%s\n", input.c_str());
}

void display_result(double result) {
    // lcd.cls();
    // int decimal_points = static_cast<int>(pot.read() * 5);
    // char format[20];
    // sprintf(format, "%%.%df", decimal_points);
    // lcd.printf(format, result);
    printf("\x1B[2J\x1B[H%.2lf\n", result);
}

void blink_invalid_key() {
    led = 1;
    blink_alert_timeout.attach([]{ led = 0; }, 50ms);
}

void check_input_alert() {
    led = (int) (input.length() == MAX_INPUT);
}

void backspace() {
    if (!input.empty()) {
        input.pop_back();
        display_input();
    }
    check_input_alert();
    is_evaluated = false;
}

void invalid_input() {
    // lcd.cls();
    // lcd.printf("Invalid input or math error");
    printf("Invalid input or math error");
}

void enter() {
    if (!input.empty()) {
        result = evaluate(input);
        if (isnan(result)) {
            invalid_input();
        } else {
            is_evaluated = true;
            display_result(result);
        }
    }
    input.clear();
    check_input_alert();
}

void store() {
    if (is_evaluated) {
        stored_result = result;
        is_stored = true;
    }
}

void use_result() {
    if (is_stored) {
        std::stringstream s;
        s << input << stored_result;
        is_stored = false;
        input = s.str();
        display_input();
    }
}

void reset() {
    input.clear();
    is_evaluated = false;
    display_input();
}

void on_input() {
    read_flag = true;
}

void setup() {
    serial_port.set_format();
    serial_port.set_baud(9600);

    serial_port.sigio(on_input);

    // joystick_up.fall([]{
    //     input = previous;
    //     display_input();
    // });
    // joystick_down.fall([]{
    //     input.clear();
    //     display_input();
    // });
}

void loop() {
    if (clear_flag) {
        input.clear();
        display_input();
        clear_flag = false;
    }

    if (!read_flag || !serial_port.readable()) return;
    read_flag = false;

    char c;

    serial_port.read(&c, 1);
    idle_timeout.attach([]{ clear_flag = true; }, IDLE_TIMEOUT_CLEAR_DURATION);

    if (is_expression_input(c)) {
        if (input.length() < MAX_INPUT) {
            input += c;
            display_input();
        } 
        check_input_alert();
        is_evaluated = false;
    }
    else switch (c) {
        case ENTER:
        case RETURN: enter(); break;
        case BACKSPACE: backspace(); break;
        case UP: store(); break;
        case DOWN: use_result(); break;
        case RESET: reset(); break;
        default:
            blink_invalid_key();
            is_evaluated = false;
        break;
    }
}

int main() {
    setup();

    while (true) {
        loop();
        __WFI();
    }
}
