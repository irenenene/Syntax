/*
Irene Liu
irliu@chapman.edu
2313260
CPSC 350-02
Assignment 3

main.cpp contains the definition of a syntaxChecker class
note that it does not check for brackets that are enclosed within single/double quotes OR comments
*/

#include "GenStack.h"
#include <iostream>
#include <fstream>

using namespace std;

//uses GenStack.h to check for mismatched delimiters
class syntaxChecker
{
public:
  char getExpected(char); //helper method should only be used on opening delimiters
  string strLower(string);
  syntaxChecker();
  ~syntaxChecker();
  GenStack<char> *theStack;
  bool checkFile(string); //returns true if there are no errors
};

syntaxChecker::syntaxChecker()
{
  theStack = NULL;
}

syntaxChecker::~syntaxChecker()
{
  delete theStack;
}

char syntaxChecker::getExpected(char lastChar)
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

string syntaxChecker::strLower(string input)
{
  string newString = "";

  for (int i = 0; i < input.length(); i++ )
  {
    char letter = tolower(input.at(i));
    newString += letter;
  }
  return newString;
}

bool syntaxChecker::checkFile(string path)
{
  ifstream inputFile;
  inputFile.open(path);

  int lineCount = 0;

  if(inputFile.is_open())
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

              inputFile.close();
              delete theStack;
              return false;
            }
          }
          catch(GenStack<char>::EmptyStackException stackErr)
          {
            cout << stackErr.getError() << endl;
          }
        }
      }
    }

    inputFile.close();
    //assumes the program didn't exit prematurely
    if(theStack->isEmpty())
    {
      cout << "No errors found." << endl;
      delete theStack;
      return true;
    }
    else
    {
      cout << "Reached end of file: Missing a " << getExpected(theStack->peek()) << endl;
      delete theStack;
      return false;
    }
  }
  else
  {
    cout << "Error reading from file." << endl;
    return false;
  }
}

//main will prompt the user for the pathname and execute the checkFile method
int main (int argc, char **argv)
{
  syntaxChecker *check = new syntaxChecker();
  string theFile = "";
  bool userExit = false;
  if(argc > 1)
  {
    theFile = argv[1];
  }

  while(check->checkFile(theFile) && !userExit)
  {
    cout << "Would you like to analyze another file (yes/no)? ";
    bool validInput = false;

    while(!validInput)
    {
      string input;
      getline(cin, input);
      input = check->strLower(input);

      if(input == "no")
      {
        userExit = true;
        validInput = true;
      }
      else if(input == "yes")
      {
        validInput = true;
        cout << "Enter a filepath: ";
        getline(cin, theFile);
      }
      else
      {
        cout << "Please enter \"yes\" or \"no\"" << endl;
      }
    }
  }

  return 0;
}
