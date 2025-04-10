#ifndef ECEN449_VALIDATION_H
#define ECEN449_VALIDATION_H

#include <string>
#include <stack>
#include <set>
#include <map>
#include <numeric>

enum InputType {
	NUMBER = 1 << 0,
	DOT = 1 << 1,
	MINUS = 1 << 2,
	BINARY_OP = 1 << 3,
	STRING = 1 << 4,
	LEFT_BRACKET = 1 << 5,
	RIGHT_BRACKET = 1 << 6,
	INVALID = 0,
	OPERATOR = BINARY_OP | MINUS
};

enum ExpressionState {
	INVALID_EXPRESSION,
	VALID_EXPRESSION,
	PARTIALLY_VALID_EXPRESSION
};

enum InputStatus {
	NEW_EXPRESSION = NUMBER | DOT | LEFT_BRACKET | STRING | MINUS,
	NUMBER_NO_DOT = NUMBER | DOT | OPERATOR | RIGHT_BRACKET,
	NUMBER_DOT_START = NUMBER,
	NUMBER_DOT_MIDDLE = NUMBER | OPERATOR | RIGHT_BRACKET,
	CONSTANT_MATCH_OR_EXPRESSION_FINISH = OPERATOR | RIGHT_BRACKET,
	FUNCTION_MATCH = LEFT_BRACKET,
	STRING_NOMATCH = STRING
};

class InputState
{
private:
	std::stack<int> previous_states;
	std::stack<std::string> previous_strings;

	int current_state = NEW_EXPRESSION;
	std::string current_string;
	int bracket_stack = 0;

	const std::string binary_operators = "+*/^";
	const std::set<std::string> functions = { "sin", "cos", "tan", "sqrt" };
	const std::set<std::string> constants = { "pi" };

	const std::string function_letters = std::accumulate(functions.begin(), functions.end(), std::string{});
	const std::string constant_letters = std::accumulate(constants.begin(), constants.end(), std::string{});
	const std::string letters = function_letters + constant_letters;

	InputType get_input_type(char c);
	void push_new_state(int new_state, bool right_bracket = false);
	void push_new_string(const std::string& old_string, char c, bool clear = true);

public:
	std::string current_input;
	void backspace();
	ExpressionState validate_and_add(char c);
	int length();
	void clear();
};

#endif // ECEN449_VALIDATION_H
