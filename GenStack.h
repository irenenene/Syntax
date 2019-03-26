#ifndef GEN_STACK
#define GEN_STACK

#include <iostream>

using namespace std;

template <class T>
class GenStack {

  static const int ARR_SIZE = 10;

public:
  class EmptyStackException
  {
  public:
    EmptyStackException(const string& err) : errMsg(err) { }
    string getError() { return errMsg; }
  private:
    string errMsg;
  };
  GenStack();
  GenStack(int initSize);
  ~GenStack();
  void push(T data);
  T pop() throw(EmptyStackException);
  T peek() throw(EmptyStackException);
  bool isEmpty();
  bool isFull();
  void growArray();
  void getInfo() { cout << size << " " << maxSize << endl; } // for debugging

private:
  T* stackArray;
  int size;
  int maxSize;

};

template<class T>
GenStack<T>::GenStack()
{
  maxSize = ARR_SIZE;
  stackArray = new T[maxSize];
  size = 0;
}

template<class T>
GenStack<T>::GenStack(int initSize)
{
  maxSize = initSize;
  stackArray = new T[maxSize];
  size = 0;
}

template<class T>
GenStack<T>::~GenStack()
{
  delete [] stackArray;
  cout << "Destructor";
}

template<class T>
void GenStack<T>::push(T data)
{
  if (isFull())
    growArray();
  stackArray[size++] = data;
}

template<class T>
T GenStack<T>::pop() throw(EmptyStackException)
{
  if (isEmpty())
    throw EmptyStackException("Could not pop from empty stack");
  return stackArray[--size];
}

template<class T>
T GenStack<T>::peek() throw(EmptyStackException)
{
  if (isEmpty())
    throw EmptyStackException("Could not peek at empty stack");
  return stackArray[size-1];

}

template<class T>
bool GenStack<T>::isEmpty()
{
  return (size == 0);
}

template<class T>
bool GenStack<T>::isFull()
{
  return (size >= maxSize);
}

template<class T>
void GenStack<T>::growArray()
{
  maxSize *= 2;
  T* newArray = new T[maxSize];
  for (int i = 0; i < size; i++)
  {
    newArray[i] = stackArray[i];
  }
  delete [] stackArray;
  stackArray = newArray;
}

#endif
