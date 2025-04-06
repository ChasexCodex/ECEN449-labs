#ifndef ECEN449_OPERATION_H
#define ECEN449_OPERATION_H

#include <stack>
#include <stdexcept>
#include <cstring>

enum class Operation
{
	Add, Subtract, Multiply, Divide, 
    Exponentiate, Sqrt,
	Sin, Cos, Tan, 
	None
};


double apply_operation(double a, double b, Operation op);

struct ExpressionNode
{
	ExpressionNode* left, * right;
	double value;
	Operation op;


	double evaluate();
};

int precedence(Operation op);

double apply_operation(double a, double b, Operation op);

Operation map_operator(char op);

double evaluate(std::string& expression);

void delete_tree(ExpressionNode* node);

#endif //ECEN449_OPERATION_H
