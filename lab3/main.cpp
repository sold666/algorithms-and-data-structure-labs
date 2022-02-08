#include <iostream>
#include <string>
#include <cmath>
#include "exception.hpp"
#include "Stack.hpp"
#include "StackArray.hpp"
#include "Operator.hpp"

std::string transformInfixExpressionToPostfix(const std::string& text);
int calculatePostfixForm(const std::string& text);
void checkString(const std::string& text);
bool arrayBalanceBrackets(const std::string& text);

int main()
{
  try
  {
    std::string text1 = "7 + 1 * 4";
    std::cout << transformInfixExpressionToPostfix(text1) << " --> " << calculatePostfixForm(transformInfixExpressionToPostfix(text1)) << '\n';
    std::string text2 = "(3 + 5) * ((1 + 2) - 4)";
    std::cout << transformInfixExpressionToPostfix(text2) << " --> " << calculatePostfixForm(transformInfixExpressionToPostfix(text2)) << '\n';
    std::string text3 = "((5 + 5) * 4) / 1";
    std::cout << transformInfixExpressionToPostfix(text3) << " --> " << calculatePostfixForm(transformInfixExpressionToPostfix(text3)) << '\n';
    std::string text4 = "((3 + 9) * 4) / 2 ^ 2";
    std::cout << transformInfixExpressionToPostfix(text4) << " --> " << calculatePostfixForm(transformInfixExpressionToPostfix(text4)) << '\n';
    std::string text5 = "((3 + 2) * 4) * (2 - 1)";
    std::cout << transformInfixExpressionToPostfix(text5) << " --> " << calculatePostfixForm(transformInfixExpressionToPostfix(text5)) << '\n';
    std::string text6 = "((3 + 1) * 3) + ((3 + 1) + (7 - 1))";
    std::cout << transformInfixExpressionToPostfix(text6) << " --> " << calculatePostfixForm(transformInfixExpressionToPostfix(text6)) << '\n';
  }
  catch(const std::invalid_argument &error)
  {
    std::cout << error.what() << '\n';
  }
  catch(const std::logic_error &error)
  {
    std::cout << error.what() << '\n';
  }
  return 0;
}

std::string transformInfixExpressionToPostfix(const std::string& text)
{
  StackArray<char> stack(text.size());
  std::string newExpression = "";
  checkString(text);
  if(!(arrayBalanceBrackets(text)))
  {
    std::cout << text << '\n';
    throw std::logic_error("Check the brackets!");
  }

  for (int i = 0; i < text.size(); ++i)
  {
    if (text[i] == ' ')
    {
      continue;
    }
    if (text[i] >= '0' && text[i] <= '9')
    {
      newExpression += text[i];
      continue;
    }
    else if (text[i] == '+' || text[i] == '-' || text[i] == '*' || text[i] == '/' || text[i] == '^')
    {
      Operator currentOperand(text[i]);
      Operator topOperand(stack.top());

      if ((stack.isEmpty()) || (stack.top() == '('))
      {
        stack.push(text[i]);
      }
      else if (currentOperand.getPriority() > topOperand.getPriority())
      {
        stack.push(text[i]);
      }
      else if (currentOperand.getPriority() <= topOperand.getPriority())
      {
        char temp = stack.top();
        while ((temp != '(' || Operator(temp).getPriority() > Operator(stack.top()).getPriority()) && !(stack.isEmpty()))
        {
          temp = stack.top();
          newExpression += stack.pop();
        }
        stack.push(text[i]);
      }
    }
    else if (text[i] == '(')
    {
      stack.push(text[i]);
      continue;
    }
    else if (text[i] == ')')
    {
      while (stack.top() != '(' && !(stack.isEmpty()))
      {
        newExpression += stack.pop();
      }
      if (stack.top() == '(')
      {
        stack.pop();
      }
      continue;
    }
  }
  while (!(stack.isEmpty()))
  {
    newExpression += stack.pop();
  }
  return newExpression;
}

int calculatePostfixForm(const std::string& text)
{
  StackArray<int> stack(text.size());
  int valueOne = 0;
  int valueTwo = 0;
  int result = 0;

  for (int i = 0; i < text.size(); ++i)
  {
    if (text[i] >= '0' && text[i] <= '9')
    {
      stack.push(text[i] - '0');
    }
    else
    {
      valueTwo = stack.pop();
      valueOne = stack.pop();
      switch (text[i])
      {
        case '+':
          result = valueOne + valueTwo;
          break;
        case '-':
          result = valueOne - valueTwo;
          break;
        case '/':
          if (valueTwo == 0)
          {
            throw std::logic_error("Can't be divided by 0.");
          }
          result = valueOne / valueTwo;
          break;
        case '*':
          result = valueOne * valueTwo;
          break;
        case '^':
          result = pow(valueOne, valueTwo);
          break;

        default:
          break;
      }
      stack.push(result);
    }
  }
  return stack.pop();
}

void checkString(const std::string& text)
{
  for (int i = 0; i < text.size(); ++i)
  {
    if (!(text[i] >= '0' && text[i] <= '9')
        && text[i] != '(' && text[i] != ')'
        && text[i] != ' ' && text[i] != '^'
        && text[i] != '-' && text[i] != '+'
        && text[i] != '*' && text[i] != '/')
    {
      throw std::invalid_argument("Invalid string specified.");
    }
  }
}

bool arrayBalanceBrackets(const std::string& text)
{
  StackArray<char> stack(text.size());

  try
  {
    for (int i = 0; i < text.size(); i++)
    {
      if ((text[i] == '(') || (text[i] == '[') || (text[i] == '{'))
      {
        stack.push(text[i]);
        continue;
      }
      else if ((text[i] == ')') || (text[i] == ']') || (text[i] == '}'))
      {
        if (text[i] == ')')
        {
          if (stack.top() == '(' && (!stack.isEmpty()))
          {
            stack.pop();
            continue;
          }
          else
          {
            return false;
          }
        }
        if (text[i] == ']')
        {
          if (stack.top() == '[' && (!stack.isEmpty()))
          {
            stack.pop();
            continue;
          }
          else
          {
            return false;
          }
        }
        if (text[i] == '}')
        {
          if (stack.top() == '{' && (!stack.isEmpty()))
          {
            stack.pop();
            continue;
          }
          else
          {
            return false;
          }
        }
      }
    }
    if (stack.isEmpty())
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  catch (StackUnderflow)
  {
    return false;
  }
  catch (StackOverflow)
  {
    return false;
  }
}