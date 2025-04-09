#ifndef ECEN449_VALIDATION_H
#define ECEN449_VALIDATION_H

#include <string>

using namespace std;

bool is_expression_input(char c);
bool is_valid_partial_expression(const string& current_input, const char c);

#endif // ECEN449_VALIDATION_H