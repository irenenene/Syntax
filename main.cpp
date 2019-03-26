#include "GenStack.h"
#include <iostream>

using namespace std;

int main (int argc, char **argv)
{
  GenStack<char> theStack(5);

  theStack.push('c');
  theStack.push('o');
  theStack.push('o');

  theStack.getInfo();
  theStack.growArray();
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
  }
  return 0;
}
