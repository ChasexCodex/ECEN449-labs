#ifndef ECEN449_MAIN_H
#define ECEN449_MAIN_H

#include <string>

// config constants
#define ENTER '\n'
#define RETURN '\r'
#define MAX_LINE 25
#define MAX_INPUT (MAX_LINE * 2)
#define MAX_DECIMALS 7
#define BACKSPACE 127
#define UP '['
#define DOWN ']'
#define RESET 'z'
#define IDLE_TIMEOUT_CLEAR_DURATION 60s

// UI
void render_lcd(std::string current_input);
void display_result();

// utility
void check_input_alert();
void blink_invalid();
void check_decimal_points_change();

// input handling
void handle_input(char c);
void backspace();
void enter();
void clear_screen();
void store_result();
void use_result();
void invalid_expression();
void handle_flags();

// setup & main loop
void setup();
void loop();

#endif