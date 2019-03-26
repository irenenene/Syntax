#include "GenStack.h"
#include <iostream>
#include <fstream>

using namespace std;

char getExpected(char);

int main (int argc, char **argv)
{
  GenStack<char> theStack(5);
/*
  theStack.push('c');
  theStack.push('o');

  theStack.getInfo();

  cout << theStack.pop() << endl;
  cout << theStack.pop() << endl;
  try {
    theStack.pop();
    theStack.peek();
  }
  catch(GenStack<char>::EmptyStackException stackErr)
  {
    cout << stackErr.getError() << endl;
  }*/

  string fileName = argv[1];
  ifstream inputFile;
  int lineCount = 0;


  inputFile.open(fileName);
  if (inputFile.is_open())
  {
    string line;

    while (getline(inputFile, line))
    {
      lineCount++;

      for (int i = 0; i < line.length(); i++)
      {
        char theChar = line.at(i);
        if((theChar == '(') || (theChar == '{') || (theChar == '['))
        {
          theStack.push(theChar);
        }
        else if ((theChar == ')') || (theChar == '}') || (theChar == ']'))
        {
          char expected = getExpected(theStack.peek());
          if(expected == theChar)
          {
            theStack.pop();
          }
          else
          {
            cout << "Line " << lineCount << ": Expected " << expected << " and found " << theChar << endl;
            inputFile.close();
            return 0;
          }
        }

      }
    }
  }
  cout << "Analyzed successfully." << endl;
  inputFile.close();
  return 0;
}

char getExpected(char lastChar)
{
  if(lastChar == '(')
    return ')';
  else if(lastChar == '{')
    return '}';
  else if(lastChar == '[')
    return ']';
  else
    return 'x'; //for testing. please delete
}
