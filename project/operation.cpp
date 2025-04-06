#include "operation.h"
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <map>

using namespace std;

Operation to_operation(std::string func);

void delete_tree(ExpressionNode* node)
{
	if (!node) return;
	delete_tree(node->left);
	delete_tree(node->right);
	delete node;
}

Operation map_operator(char op)
{
	switch (op)
	{
	case '+':
		return Operation::Add;
	case '-':
		return Operation::Subtract;
	case '*':
		return Operation::Multiply;
	case '/':
		return Operation::Divide;
	case '^':
        return Operation::Exponentiate;
	default:
		return Operation::None;
	}
}

void append_parentheses(std::string& expression) {
    int open_parens = 0;
	for (char c : expression) {
		if (c == '(') open_parens++;
		else if (c == ')') open_parens--;
	}
	while (open_parens-- > 0) {
		expression += ')';
	}
}

void substitute_pi(std::string& expression) {
    size_t pos = 0;
    while ((pos = expression.find("pi", pos)) != string::npos) {
        expression.replace(pos, 2, "(3.14159265358979323846)");
        pos += 22;
    }
}

double evaluate(std::string expression)
{
	append_parentheses(expression);
    substitute_pi(expression);

	stack<Operation> operators;
	stack<ExpressionNode*> operands;

	auto push_node = [&]()
    {
        ExpressionNode* node = new ExpressionNode();
        node->op = operators.top();
        operators.pop();

        if (precedence(node->op) == 4)
        {
            node->left = operands.top(); operands.pop();
            node->right = nullptr;
        }
        else
        {
            node->right = operands.top(); operands.pop();
            node->left = operands.top(); operands.pop();
        }

        operands.push(node);
        return false;
    };

	auto push_operator = [&](Operation op)
	{
		while (!operators.empty() && precedence(operators.top()) >= precedence(op))
		{
			push_node();
		}
		operators.push(op);
	};

	auto push_value = [&](double value)
	{
		ExpressionNode* node = new ExpressionNode();
		node->value = value;
		node->op = Operation::None;
		operands.push(node);
	};

	for (size_t i = 0; i < expression.size(); i++)
	{
		if (isdigit(expression[i]) || (expression[i] == '.' && i + 1 < expression.size() && isdigit(expression[i + 1])) || (expression[i] == '-' && i + 1 < expression.size() && (isdigit(expression[i + 1]) || expression[i + 1] == '.') && (i == 0 || (!isdigit(expression[i - 1]) && expression[i - 1] != ')'))))
		{
			string number_str;
			bool decimal_found = false;

			if (expression[i] == '-')
			{
				number_str += '-';
				i++;
			}

			if (expression[i] == '.')
			{
				decimal_found = true;
				number_str += "0.";  // convert leading '.' to '0.'
				i++;
			}

			while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.'))
			{
				if (expression[i] == '.')
				{
					if (!decimal_found)
					{
						decimal_found = true;
						number_str += '.';
					}
					// else skip extra dots
				}
				else
				{
					number_str += expression[i];
				}
				i++;
			}

			if (!decimal_found && number_str.back() == '.')
			{
				number_str += '0';  // handle '3.' case
			}

			i--; // step back for main loop
			double value = stod(number_str);
			push_value(value);
		} else if (isalpha(expression[i])) {
            string func;
            while (i < expression.size() && isalpha(expression[i])) {
                func += expression[i++];
            }
            i--;

            Operation op = to_operation(func);
            if (op == Operation::None) { // unrecognized input
                printf("Unrecognized function %s\n", func.c_str());
                return NAN;
            }

            operators.push(op); // push the function op
        }
		else if (std::isspace(expression[i]))
		{
			continue;
		}
		else if (expression[i] == '(')
		{
			operators.push(Operation::None); // Use None as a marker for '('
		}
		else if (expression[i] == ')')
        {
            while (!operators.empty() && operators.top() != Operation::None)
            {
                Operation op = operators.top();
                operators.pop();

                ExpressionNode* node = new ExpressionNode();
                node->op = op;

                if (precedence(op))
                {                    
			        node->right = nullptr;
                }
                else
                {
                    node->right = operands.top(); operands.pop();
                }
                node->left = operands.top(); operands.pop();
                operands.push(node);
            }
            if (!operators.empty()) operators.pop();  // pop the '(' marker
        }
		else
		{
			push_operator(map_operator(expression[i]));
		}
	}

	while (!operators.empty())
	{
		push_node();
	}

	ExpressionNode* root = operands.top();
	double result = root->evaluate();
	delete_tree(root);
	return result;
}

Operation to_operation(std::string func) {
    static const std::map<std::string, Operation> opMap = {
        {"sin", Operation::Sin},
        {"cos", Operation::Cos},
        {"tan", Operation::Tan},
        {"sqrt", Operation::Sqrt},
    };

    auto it = opMap.find(func);
    return (it != opMap.end()) ? it->second : Operation::None;
}

double apply_operation(double a, double b, Operation op)
{
	switch (op)
	{
	case Operation::Add: return a + b;
	case Operation::Subtract: return a - b;
	case Operation::Multiply: return a * b;
	case Operation::Divide: return a / b;
	case Operation::Exponentiate: return pow(a, b);
	case Operation::Sin: return sin(a);
	case Operation::Cos: return cos(a);
	case Operation::Tan: return tan(a);
	case Operation::Sqrt:
        if (a < 0) return NAN;
        return sqrt(a);
	default: return a;
	}
}

int precedence(Operation op)
{
	switch (op)
	{
	case Operation::Add:
	case Operation::Subtract:
		return 1;
	case Operation::Multiply:
	case Operation::Divide:
		return 2;
	case Operation::Exponentiate:
		return 3;
    case Operation::Sin:
	case Operation::Cos:
	case Operation::Tan:
	case Operation::Sqrt:
		return 4; // this value is also used to check if the operation is a function
	default:
		return 0;
	}
}

double ExpressionNode::evaluate()
{
	if (op == Operation::None) return value;

	if (precedence(op) == 4) // this a function
		return apply_operation(left->evaluate(), 0, op); // right is ignored

	return apply_operation(left->evaluate(), right->evaluate(), op);
}
