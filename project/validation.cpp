#include "validation.h"
#include <string>
#include <set>
#include <map>
#include <numeric>


enum AllowedInput
{
	NUMBER = 1 << 0,
	DOT = 1 << 1,
	BINARY_OPERATOR = 1 << 2,
	FUNCTION = 1 << 3,
	LEFT_BRACKET = 1 << 4,
	RIGHT_BRACKET = 1 << 5,
	CONSTANT = 1 << 6,
	MINUS = 1 << 7,
	OPERATOR = MINUS | BINARY_OPERATOR,
};

bool is_expression_input(char c)
{
	return isdigit(c) || (string("+-*/^.()sincostansqrtpi").find(c) != std::string::npos);
}

bool is_valid_partial_expression(const string& current_input, const char c)
{
	const string binary_operators = "+*/^";

	const set <string> functions = {
			"sin", "cos", "tan", "sqrt"
	};

	const set <string> constants = {
			"pi"
	};

	// possible letters from functions and constants (mapped directly from functions and constants)
	string function_letters = accumulate(functions.begin(), functions.end(), string{});
	string constant_letters = accumulate(constants.begin(), constants.end(), string{});
	string letters = function_letters + constant_letters;

	string current_function, current_constant;

	int bracket_stack = 0;

	// the input can start with any of these
	const int new_expression = NUMBER | DOT | FUNCTION | LEFT_BRACKET | CONSTANT | MINUS;
	int allowed_input = new_expression;

	// the current_input is assumed to be valid
	// we just need to set up the flags for the allowed next character
	for (char input_letter: current_input)
	{
		if (isdigit(input_letter))
		{
			allowed_input = RIGHT_BRACKET * (bracket_stack > 0);
			allowed_input |= NUMBER | DOT | OPERATOR;
		}

		else if (input_letter == '.')
		{
			allowed_input = RIGHT_BRACKET * (bracket_stack > 0);
			allowed_input |= NUMBER | OPERATOR;
		}

		else if (binary_operators.find(input_letter) != string::npos)
		{
			current_constant.clear();
			allowed_input |= NUMBER | FUNCTION | LEFT_BRACKET | CONSTANT | MINUS;
		}

		else if (input_letter == '-')
		{
			current_constant.clear();
			allowed_input = NUMBER | FUNCTION | LEFT_BRACKET | CONSTANT;
		}

		// if the character is part of a function or constant, we can only have the remaining letters of that or a left bracket
		else if (letters.find(input_letter) != string::npos)
		{
			allowed_input = 0;
			if (function_letters.find(input_letter) != string::npos)
			{
				current_function += input_letter;
				allowed_input |= FUNCTION;
				if (functions.find(current_function) != functions.end())
				{
					allowed_input |= LEFT_BRACKET;
				}
			}
			if (constant_letters.find(input_letter) != string::npos)
			{
				current_constant += input_letter;
				allowed_input |= CONSTANT;
				if (constants.find(current_constant) != constants.end())
				{
					allowed_input |= OPERATOR | RIGHT_BRACKET * (bracket_stack > 0);
				}
			}
		}

		else if (input_letter == '(')
		{
			bracket_stack++;
			current_function.clear();
			allowed_input = new_expression | RIGHT_BRACKET;
		}
		else if (input_letter == ')')
		{
			bracket_stack--;
			allowed_input = OPERATOR;
			if (bracket_stack > 0)
			{
				allowed_input = OPERATOR | RIGHT_BRACKET;
			}
		}
	}

	auto is_part_of_function = [&](const string& function)
	{
		return function.find(current_function + c) == 0;
	};

	auto is_part_of_constant = [&](const string& constant)
	{
		return constant.find(current_constant + c) == 0;
	};

	map<bool, int> condition_map{
			{ isdigit(c),                                                      NUMBER },
			{ c == '.',                                                        DOT },
			{ binary_operators.find(c) != string::npos,                        BINARY_OPERATOR },
			{ c == '-',                                                        MINUS },
			{ c == '(',                                                        LEFT_BRACKET },
			{ c == ')',                                                        RIGHT_BRACKET },
			{ any_of(functions.begin(), functions.end(), is_part_of_function), FUNCTION },
			{ any_of(constants.begin(), constants.end(), is_part_of_constant), CONSTANT },
	};

	auto true_condition = condition_map.find(true);
	if (true_condition == condition_map.end())
	{
		return false;
	}

	return true_condition->second & allowed_input;
}