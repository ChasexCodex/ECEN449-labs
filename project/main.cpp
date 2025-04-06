#include "mbed.h"
#include "C12832.h"
#include "operation.h"
#include "main.h"

#include <cstdio>
#include <string>
#include <sstream>

// pin mappings
C12832 lcd(D11, D13, D12, D7, D10); // the LCD panel
BufferedSerial serial_port(USBTX, USBRX); // UART communication port

// DigitalOut led(LED1); // was used for testing
BusOut rgb_led(D5, D9, D8); // used for signaling max/bad input  
AnalogIn pot(A0); // used to adjust decimal points
InterruptIn joystick_up(A2); // used to store evaluated results
InterruptIn joystick_down(A3); // used to insert previously evaluated results

// a timeout to clear the input after IDLE_TIMEOUT_CLEAR_DURATION
Timeout idle_timeout;

std::string input("");
volatile bool read_flag = false;
double result = 0;
bool is_evaluated = false;
volatile bool is_stored = false;
double stored_result = 0;
bool clear_flag = false;
bool refresh_input_flag = false;
bool invalid_flag = false;
int decimals = 2;

void render_lcd() {
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf("%s\n", input.c_str());
    printf("\x1B[2J\x1B[H%s\n", input.c_str());

    if (is_evaluated) {
        display_result();
    }
}

void display_result() {
    if (input.size() < MAX_LINE) {
        lcd.printf("\n");
    }
    char format[25];
    sprintf(format, "%%.%df", decimals);
    lcd.printf(format, result);
    printf("\x1B[2J\x1B[H%.2lf", result);
}

bool is_expression_input(char c) {
    return std::isdigit(c) || (std::string("+-*/^.()sincostansqrtpi").find(c) != std::string::npos);
}

void check_input_alert() {
    rgb_led = input.length() == MAX_INPUT ? 0b100 : 0b111;
}

void blink_invalid_key() {
    int temp = rgb_led;
    rgb_led = 0b110;
    ThisThread::sleep_for(50ms);
    rgb_led = temp;
}

void check_decimal_points_change() {
    int temp = (int)(pot.read() * MAX_DECIMALS);
    if (decimals == temp) return;

    decimals = temp;
    render_lcd();
}

void handle_input(char c) {
    if (is_evaluated) {
        input.clear();
    }

    is_evaluated = false;
    if (input.length() < MAX_INPUT) {
        input += c;
        render_lcd();
    }
    check_input_alert();
}

void backspace() {
    is_evaluated = false;
    if (!input.empty()) {
        input.pop_back();
        render_lcd();
    }
    check_input_alert();
}

void enter() {
    if (!input.empty()) {
        result = evaluate(input);
        if (isnan(result)) {
            invalid_expression();
        } else {
            is_evaluated = true;
            render_lcd();
        }
    }
    check_input_alert();
}

void clear_input() {
    input.clear();
    render_lcd();
}

void store_result() {
    if (is_evaluated) {
        stored_result = result;
        is_stored = true;
    }
}

void use_result() {
    if (!is_stored) return;

    std::stringstream s;
    s << input << stored_result;
    is_stored = false;
    input = s.str();
    refresh_input_flag = true;
}

void invalid_expression() {
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf("Invalid input or math error\n");
    printf("Invalid input or math error\n");
}

void handle_flags() {
    if (invalid_flag) {
        blink_invalid_key();
        invalid_flag = false;
    }

    if (clear_flag) {
        clear_input();
        clear_flag = false;
    }

    if (refresh_input_flag) {
        render_lcd();
        refresh_input_flag = false;
    }

    if (is_evaluated) {
        check_decimal_points_change();
    }
}

void setup() {
    // turn off the rgb led
    rgb_led = 0b111;

    // serial port config
    serial_port.set_format();
    serial_port.set_baud(9600);
    serial_port.sigio([] {
        read_flag = true;
    });

    // controls for using previous result
    joystick_up.fall([] {
        store_result();
    });
    joystick_down.fall([] {
        use_result();
    });

    lcd.printf("Type an expression:");
}

void loop() {
    handle_flags();

    if (!read_flag || !serial_port.readable()) return;
    read_flag = false;

    char c;

    serial_port.read( & c, 1);
    idle_timeout.attach([] {
        clear_flag = true;
    }, IDLE_TIMEOUT_CLEAR_DURATION);

    if (is_expression_input(c)) {
        handle_input(c);
    } else switch (c) {
    case ENTER:
    case RETURN:
        enter();
        break;
    case BACKSPACE:
        backspace();
        break;
        // case UP: store_result(); break; // was used to test without lcd
        // case DOWN: use_result(); break;
    case RESET:
        is_evaluated = false;
        clear_input();
        break;
    default:
        invalid_flag = true;
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