#include <iostream>
#include <string>
#include "exception.hpp"
#include "Stack.hpp"
#include "StackArray.hpp"
#include "StackList.hpp"

bool arrayBalanceBrackets(const std::string& text);
bool listBalanceBrackets(const std::string& string);
bool isCorrect( const std::string& str, bool stackType = false);

int main()
{
  StackArray<int> testArray;
  testArray.push(5);
  testArray.push(10);
  testArray.push(2);
  testArray.push(1);

  std::cout << "StackArray: " << testArray.pop() << ' ' << testArray.pop()
            << ' ' << testArray.pop() << ' ' << testArray.pop() << "\n";

  std::string text1 = "( ) ok ";
  std::cout << text1 << ": " << (isCorrect(text1, false) ? "right" : "wrong") << "\n";
  std::string text2 = "( ( [ ] ) ) ok ";
  std::cout << text2 << ": " << (isCorrect(text2, false) ? "right" : "wrong") << "\n";
  std::string text3 = "( ( [{}]([ ]) ) ) OK";
  std::cout << text3 << ": " << (isCorrect(text3, false) ? "right" : "wrong") << "\n";
  std::string text4 = "( ( [ { } [ ] ( [ ] ) ] ) ) ) extra right parenthesis ";
  std::cout << text4 << ": " << (isCorrect(text4, true) ? "right" : "wrong") << "\n";
  std::string text5 = "( ( [{ }[ ]([ ])] ) extra left parenthesis ";
  std::cout << text5 << ": " << (isCorrect(text5, true) ? "right" : "wrong") << "\n";
  std::string text6 = "( ( [{ ][ ]([ ])]) ) unpaired bracket ";
  std::cout << text6 << ": " << (isCorrect(text6, true) ? "right" : "wrong") << "\n";

  return 0;
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

bool listBalanceBrackets(const std::string& string)
{
  Stack<char> *stack = new StackList<char>();

  bool isBalanceBrackets = true;
  try
  {
    char cText = '\0';

    for (int i = 0; ((cText = string[i]) != '\0') && isBalanceBrackets; i++)
    {
      switch (cText)
      {
        case '(':
        case '[':
        case '{':
          stack->push(cText);
          break;
        case ')':
          if (stack->pop() != '(')
          {
            isBalanceBrackets = false;
          }
          break;
        case ']':
          if (stack->pop() != '[')
          {
            isBalanceBrackets = false;
          }
          break;
        case '}':
          if (stack->pop() != '{')
          {
            isBalanceBrackets = false;
          }
          break;
      }
    }
    isBalanceBrackets = isBalanceBrackets && stack->isEmpty();
  } catch (StackUnderflow &)
  {
    isBalanceBrackets = false;
  } catch (StackOverflow &)
  {
    isBalanceBrackets = false;
  }
  return isBalanceBrackets;
}

bool isCorrect(const std::string& str, bool stackType)
{
  if (stackType)
  {
    return arrayBalanceBrackets(str);
  }
  else
  {
    return listBalanceBrackets(str);
  }
};
