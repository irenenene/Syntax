/*
Irene Liu
irliu@chapman.edu
2313260
CPSC 350-02
Assignment 3

main.cpp uses GenStack.h to implement a syntax checker for mismatched delimiters
*/

#include "GenStack.h"
#include <iostream>
#include <fstream>

using namespace std;

char getExpected(char); //helper method should only be used on opening delimiters
string strLower(string);

int main (int argc, char **argv)
{
  GenStack<char> *theStack;
  ifstream inputFile;
  bool userExit = false;
  string fileName = "";
  if(argc > 1)
  {
    fileName = argv[1];
  }

  while(!userExit)
  {
    inputFile.open(fileName);
    int lineCount = 0;

    if (inputFile.is_open())
    {
      theStack = new GenStack<char> ();
      string line;

      while (getline(inputFile, line))
      {
        lineCount++;

        for (int i = 0; i < line.length(); i++)
        {
          char theChar = line.at(i);
          if((theChar == '(') || (theChar == '{') || (theChar == '['))
          {
            theStack->push(theChar);
          }
          else if ((theChar == ')') || (theChar == '}') || (theChar == ']'))
          {
            try
            {
              char expected = getExpected(theStack->peek());
              if(expected == theChar)
              {
                theStack->pop();
              }
              else
              {
                cout << "Line " << lineCount << ": Expected " << expected << " and found " << theChar << endl;

                delete theStack;
                inputFile.close();
                return 0;
              }
            }
            catch(GenStack<char>::EmptyStackException stackErr)
            {
              cout << stackErr.getError() << endl;
            }
          }
        }
      }

      if(theStack->isEmpty())
      {
        cout << "Analyzed successfully.\nWould you like to analyze another file (yes/no)? ";
        bool validInput = false;

        while(!validInput)
        {
          string input;
          getline(cin, input);
          input = strLower(input);

          if(input == "no")
          {
            userExit = true;
            validInput = true;
          }
          else if (input == "yes")
          {
            cout << "Enter a filepath:";
            getline(cin, fileName);
            validInput = true;
          }
          else
          {
            cout << "Please enter \"yes\" or \"no\"" << endl;
          }
        }
      }
      else
      {
        cout << "Reached end of file: Missing a " << getExpected(theStack->peek()) << endl;
        userExit = true;
      }

      delete theStack;
      inputFile.close();
    }
    else
    {
      cout << "Error reading from file." << endl;
      userExit = true;
    }
  }

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
    return '\0'; //should not reach this block
}

string strLower(string input)
{
  string newString = "";

  for (int i = 0; i < input.length(); i++ )
  {
    char letter = tolower(input.at(i));
    newString += letter;
  }
  return newString;
}
