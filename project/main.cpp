#include "mbed.h"
#include "C12832.h"
#include "operation.h"
#include "validation.h"
#include "main.h"

#include <cstdio>
#include <string>
#include <sstream>

// #define ECEN449_DEBUG // enable to see output on the serial monitor as well
// #define F429 // the other board used to test this code

// pin mappings
C12832 lcd(D11, D13, D12, D7, D10); // the LCD panel
BufferedSerial serial_port(USBTX, USBRX); // UART communication port

#ifdef F429
DigitalOut led(LED1); // was used for testing
#endif

BusOut rgb_led(D5, D9, D8); // used for signaling max/bad input  
AnalogIn pot(A0); // used to adjust decimal points

#ifndef F429
// must wrap in an `if` directive because it causes pin conflict on F429 board 
InterruptIn joystick_up(A2); // used to store evaluated results
InterruptIn joystick_down(A3); // used to insert previously evaluated results
#endif

// a timeout to clear the input after IDLE_TIMEOUT_CLEAR_DURATION
Timeout idle_timeout;

InputState input_state;
string previous_input;
volatile bool read_flag = false;
double result = 0;
bool evaluated_flag = false; // used to indicate the expression is evaluated
ExpressionState expr_state = ExpressionState::INVALID_EXPRESSION;
volatile bool stored_flag = false; // used to indicate a result is stored
double stored_result = 0;
bool clear_flag = false;
bool refresh_input_flag = false;
bool invalid_flag = false;
int decimal_points = 2; // decimal_points to display
float last_pot_value = 0.0f; // used to stablize the readings

// renders the input (and result if available)
void render_lcd(string current_input) {
	lcd.cls(); // clear screen
	lcd.locate(0, 3); // change cursor
	lcd.printf("%s\n", current_input.c_str()); // print number
	
#ifdef ECEN449_DEBUG
    printf("\x1B[2J\x1B[H%s\n", current_input.c_str());
#endif

	if (evaluated_flag) {
		display_result();
	}
}

void display_result() {
	if (input_state.length() < MAX_LINE) {
		lcd.printf("\n");
	}
	char format[25];
	sprintf(format, "%%.%df\n", decimal_points);
	lcd.printf(format, result);
#ifdef ECEN449_DEBUG
	printf(format, result);
#endif
}

// shows yellow if max input reached
void check_input_alert() {
	rgb_led = input_state.length() == MAX_INPUT - 1 ? 0b100 : 0b111;
}

// blinks on invalid input
void blink_invalid() {
	int temp = rgb_led;
	rgb_led = 0b110;
	ThisThread::sleep_for(50ms);
	rgb_led = temp;
}

void check_decimal_points_change() {
    float current_value = pot.read();
    const float threshold = 0.05f;

    if (fabs(current_value - last_pot_value) < threshold) // mechanism to minimize noise
        return;

    last_pot_value = current_value;

    int temp = (int)(current_value * MAX_DECIMALS);
    if (decimal_points != temp) {
        decimal_points = temp;
        render_lcd(previous_input);
    }
}

void handle_input(char c) {
	evaluated_flag = false;

    if (input_state.validate_and_add(c) != ExpressionState::INVALID_EXPRESSION) {
        if (input_state.length() < MAX_INPUT) {
    		render_lcd(input_state.current_input);
        } else {
            input_state.backspace();
        }
    } else {
        invalid_flag = true;
    }
	check_input_alert();
}

// on press backspace
void backspace() {
	evaluated_flag = false;
	if (input_state.length() > 0) {
        input_state.backspace();
		render_lcd(input_state.current_input);
	}
	check_input_alert();
}

// on press enter
void enter() {
	if (input_state.length() > 0 && input_state.current_expression_state == ExpressionState::VALID_EXPRESSION) {
		// evaluate only for a valid input
        result = evaluate(input_state.current_input);
		if (isnan(result) || isinf(result)) {
			invalid_expression();
		} else {
			evaluated_flag = true;
			render_lcd(input_state.current_input);
			previous_input = input_state.current_input;
		}
    	input_state.clear();
	} else {
        invalid_flag = true;
    }
	check_input_alert();
}

// clears the screen and input
void clear_screen() {
	input_state.clear();
	evaluated_flag = false;
    lcd.cls();
	lcd.printf("Type an expression:");
}

// stores result
void store_result() {
	if (!evaluated_flag) return;

    stored_result = result;
    stored_flag = true;
}

// uses stored result
void use_result() {
	if (!stored_flag) return;

	stored_flag = false;
	stringstream ss;
	ss << input_state.current_input << stored_result;
    string str = ss.str();
    for (int i = 0; i < str.size(); i++) 
        input_state.validate_and_add(str[i]);
	refresh_input_flag = true;
}

// display message to user
void invalid_expression() {
	lcd.cls();
	lcd.locate(0, 3);
	lcd.printf("Invalid input or math error\n");
	printf("Invalid input or math error\n");
}

// all flag handlers are processed here
void handle_flags() {
	if (invalid_flag) {
		blink_invalid();
		invalid_flag = false;
	}

	if (clear_flag) {
		clear_screen();
		clear_flag = false;
	}

	if (refresh_input_flag) {
		render_lcd(input_state.current_input);
		refresh_input_flag = false;
	}
#ifndef F429
	if (evaluated_flag) {
		check_decimal_points_change();
	}
#endif
}

void setup() {
	// turn off the rgb led
	rgb_led = 0b111;

	// serial port config
	serial_port.set_format();
	serial_port.set_baud(9600);
	serial_port.sigio([] { read_flag = true; });

	// controls for using previous result
#ifndef F429
    joystick_up.fall([] { store_result(); });
	joystick_down.fall([] { use_result(); });
#endif

	// initial message
	lcd.printf("Type an expression:");
}

void loop() {
	handle_flags();

	if (!read_flag || !serial_port.readable()) return;
	read_flag = false;

	char c;

	serial_port.read(&c, 1);
	idle_timeout.attach([] { clear_flag = true; }, IDLE_TIMEOUT_CLEAR_DURATION);

    switch (c) {
		case ENTER:
		case RETURN: enter(); break;
		case BACKSPACE: backspace(); break;
        
#ifdef ECEN449_DEBUG
        case UP: store_result(); break; // was used to test without lcd
        case DOWN: use_result(); break;
#endif

        case RESET: clear_screen(); break;
		default: handle_input(c); break;
    } 
}

int main() {
	setup();

	while (true) {
		loop();
		__WFI();
	}
}