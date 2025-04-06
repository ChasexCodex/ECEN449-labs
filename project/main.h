#ifndef ECEN449_MAIN_H
#define ECEN449_MAIN_H

// config constants
#define ENTER '\n'
#define RETURN '\r'
#define MAX_LINE 25
#define MAX_INPUT (MAX_LINE * 2)
#define MAX_DECIMALS 7
#define BACKSPACE 127
// #define UP 'w'
// #define DOWN 's'
#define RESET 'z'
#define IDLE_TIMEOUT_CLEAR_DURATION 60s

// UI
void render_lcd();
void display_result();

// utility
bool is_expression_input(char c);
void check_input_alert();
void blink_invalid_key();
void check_decimal_points_change();

// input handling
void handle_input(char c);
void backspace();
void enter();
void clear_input();
void store_result();
void use_result();
void invalid_expression();
void handle_flags();

// setup & main loop
void setup();
void loop();

#endif