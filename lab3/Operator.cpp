#include "Operator.hpp"

Operator::Operator():
  operand_('\0'),
  priority_(-1)
{}

Operator::Operator(char operand):
  operand_(operand),
  priority_(-1)
{
  switch (operand)
  {
    case '(':
      priority_ = 1;
      break;
    case ')':
      priority_ = 1;
      break;
    case '-':
      priority_ = 2;
      break;
    case '+':
      priority_ = 3;
      break;
    case '/':
      priority_ = 4;
      break;
    case '*':
      priority_ = 5;
      break;
    case '^':
      priority_ = 6;
      break;

    default:
      break;
  }
}

char Operator::getOperand() const
{
  return operand_;
}

int Operator::getPriority() const
{
  return priority_;
}