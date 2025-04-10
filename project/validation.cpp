#include "validation.h"
#include <string>
#include <set>
#include <map>
#include <numeric>
#include <stack>
#include <algorithm>

using namespace std;

InputType InputState::get_input_type(const char c)
{
	if (isdigit(c)) return NUMBER;
	if (c == '.') return DOT;
	if (c == '-') return MINUS;
	if (binary_operators.find(c) != string::npos) return BINARY_OP;
	if (letters.find(c) != string::npos) return STRING;
	if (c == '(') return LEFT_BRACKET;
	if (c == ')') return RIGHT_BRACKET;
	return INVALID;
}

void InputState::push_new_state(int new_state, bool right_bracket)
{
	previous_states.push(current_state);
	if (right_bracket) new_state &= ~(RIGHT_BRACKET * (bracket_stack == 0));
	current_state = new_state;
}

void InputState::push_new_string(const string& old_string, char c, bool clear)
{
	previous_strings.push(old_string);
	if (clear) current_string.clear();
	else current_string = old_string + c;
}

void InputState::backspace()
{
	if (current_input.empty()) return;

	char c = current_input.back();
	current_input.pop_back();
	current_state = previous_states.top();
	previous_states.pop();

	if (!current_string.empty())
	{
		current_string.pop_back();
		previous_strings.pop();
	}
	else if (isalpha(c))
	{
		current_string = previous_strings.top();
		previous_strings.pop();
	}
}

ExpressionState InputState::validate_and_add(const char c)
{
	InputType input_type = get_input_type(c);

	if (!(input_type & current_state)) return ExpressionState::INVALID_EXPRESSION;

	if (input_type == NUMBER)
	{
		current_input += c;
		if ((current_state | MINUS) == NEW_EXPRESSION) push_new_state(NUMBER_NO_DOT, true);
		else if ((current_state | MINUS) == NUMBER_NO_DOT || (current_state | MINUS | RIGHT_BRACKET) == NUMBER_DOT_MIDDLE)
			push_new_state(current_state, true);
		else if (current_state == NUMBER_DOT_START) push_new_state(NUMBER_DOT_MIDDLE, true);

		return ExpressionState::VALID_EXPRESSION;
	}
	else if (input_type == DOT)
	{
		current_input += c;
		if ((current_state | MINUS) == NEW_EXPRESSION)
		{
			push_new_state(NUMBER_DOT_START);
			return ExpressionState::PARTIALLY_VALID_EXPRESSION;
		}
		if ((current_state | MINUS) == (NUMBER_NO_DOT & ~(RIGHT_BRACKET * (bracket_stack == 0))))
		{
			push_new_state(NUMBER_DOT_MIDDLE, true);
			return ExpressionState::VALID_EXPRESSION;
		}
	}
	else if (input_type == LEFT_BRACKET)
	{
		bracket_stack++;
		push_new_state(NEW_EXPRESSION, true);
		current_input += c;
		return ExpressionState::PARTIALLY_VALID_EXPRESSION;
	}
	else if (input_type == RIGHT_BRACKET)
	{
		if (bracket_stack == 0) return ExpressionState::INVALID_EXPRESSION;
		bracket_stack--;
		push_new_state(CONSTANT_MATCH_OR_EXPRESSION_FINISH, true);
		current_input += c;
		return ExpressionState::VALID_EXPRESSION;
	}
	else if (input_type == STRING)
	{
		auto is_part_of_function = [&](const string& function)
		{
			return function.find(current_string + c) == 0;
		};

		auto is_part_of_constant = [&](const string& constant)
		{
			return constant.find(current_string + c) == 0;
		};

		if (functions.find(current_string + c) != functions.end())
		{
			push_new_state(FUNCTION_MATCH);
			push_new_string(current_string, c);
		}
		else if (constants.find(current_string + c) != constants.end())
		{
			push_new_state(CONSTANT_MATCH_OR_EXPRESSION_FINISH);
			push_new_string(current_string, c);
			current_input += c;
			return ExpressionState::VALID_EXPRESSION;
		}
		else if (any_of(functions.begin(), functions.end(), is_part_of_function)
				 || any_of(constants.begin(), constants.end(), is_part_of_constant))
		{
			push_new_state(STRING_NOMATCH);
			push_new_string(current_string, c, false);
		}
		else return ExpressionState::INVALID_EXPRESSION;
		current_input += c;
		return ExpressionState::PARTIALLY_VALID_EXPRESSION;
	}
	else if (input_type & OPERATOR)
	{
		current_input += c;
		push_new_state(NEW_EXPRESSION & ~(MINUS * (input_type == MINUS)));
		return ExpressionState::PARTIALLY_VALID_EXPRESSION;
	}

	printf("Should not be here: %c\n", c);
	return ExpressionState::INVALID_EXPRESSION;
}

int InputState::length() {
	return current_input.length();
}

void InputState::clear() {
	current_state = NEW_EXPRESSION;
	current_input.clear();
	current_string.clear();
	bracket_stack = 0;
	while (!previous_states.empty()) previous_states.pop();
	while (!previous_strings.empty()) previous_strings.pop();
}