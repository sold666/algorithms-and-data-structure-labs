#ifndef LAB3_OPERATOR_HPP
#define LAB3_OPERATOR_HPP

class Operator
{
public:
  Operator();
  Operator(char operand);

  char getOperand() const;
  int getPriority() const;

private:
  char operand_;
  int priority_;
};

#endif
