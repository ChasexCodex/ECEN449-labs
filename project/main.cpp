#include "mbed.h"
#include "C12832.h"
#include "operation.h"
#include "validation.h"
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

string input;
string previous_input;
volatile bool read_flag = false;
double result = 0;
bool evaluated_flag = false; // used to indicate the expression is evaluated
volatile bool stored_flag = false; // used to indicate a result is stored
double stored_result = 0;
bool clear_flag = false;
bool refresh_input_flag = false;
bool invalid_flag = false;
int decimal_points = 2; // decimal_points to display

// renders the input and result (if available)
void render_lcd(string current_input) {
	lcd.cls(); // clear screen
	lcd.locate(0, 3); // change cursor
	lcd.printf("%s\n", current_input.c_str()); // print number
	
    #if ECEN449_DEBUG
    printf("\x1B[2J\x1B[H%s\n", current_input.c_str());
    #endif

	if (evaluated_flag) {
		display_result();
	}
}

void display_result() {
	if (input.size() < MAX_LINE) {
		lcd.printf("\n");
	}
	char format[25];
	sprintf(format, "%%.%df", decimal_points);
	lcd.printf(format, result);
	printf("\x1B[2J\x1B[H%.2lf", result);
}

// shows yellow if max input reached
void check_input_alert() {
	rgb_led = input.length() == MAX_INPUT ? 0b100 : 0b111;
}

// blinks on invalid input
void blink_invalid() {
	int temp = rgb_led;
	rgb_led = 0b110;
	ThisThread::sleep_for(50ms);
	rgb_led = temp;
}

void check_decimal_points_change() {
	int temp = (int)(pot.read() * MAX_DECIMALS);
	if (decimal_points == temp) return;

	decimal_points = temp;
	render_lcd(previous_input);
}

void handle_input(char c) {
	evaluated_flag = false;
	if (input.length() < MAX_INPUT) {
		input += c;
		render_lcd(input);
	}
	check_input_alert();
}

void backspace() {
	evaluated_flag = false;
	if (!input.empty()) {
		input.pop_back();
		render_lcd(input);
	}
	check_input_alert();
}

void enter() {
	if (!input.empty()) {
		result = evaluate(input);
		if (isnan(result)) {
			invalid_expression();
		} else {
			evaluated_flag = true;
			render_lcd(input);
			previous_input = input;
		}
	}
	input.clear();
	check_input_alert();
}

void clear_screen() {
	input.clear();
	evaluated_flag = false;
	render_lcd(input);
}

void store_result() {
	if (evaluated_flag) {
		stored_result = result;
		stored_flag = true;
	}
}

void use_result() {
	if (!stored_flag) return;

	stringstream s;
	s << input << stored_result;
	stored_flag = false;
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
		blink_invalid();
		invalid_flag = false;
	}

	if (clear_flag) {
		clear_screen();
		clear_flag = false;
	}

	if (refresh_input_flag) {
		render_lcd(input);
		refresh_input_flag = false;
	}

	if (evaluated_flag) {
		check_decimal_points_change();
	}
}

void setup() {
	// turn off the rgb led
	rgb_led = 0b111;

	// serial port config
	serial_port.set_format();
	serial_port.set_baud(9600);
	serial_port.sigio([] { read_flag = true; });

	// controls for using previous result
	joystick_up.fall([] { store_result(); });
	joystick_down.fall([] { use_result(); });

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

	if (is_expression_input(c) && is_valid_partial_expression(input, c)) {
		handle_input(c);
	} else switch (c) {
		case ENTER:
		case RETURN: enter(); break;
		case BACKSPACE: backspace(); break;
//      case UP: store_result(); break; // was used to test without lcd
//      case DOWN: use_result(); break;
		case RESET:
			clear_screen();
			break;
		default:
			invalid_flag = true;
			evaluated_flag = false;
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