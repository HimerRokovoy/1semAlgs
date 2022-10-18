#include <assert.h>
#include <iostream>

#define growCoefficient 2
#define initSize 1

#define success 0
#define inStackZero 1

using namespace std;

class Stack {
int* buffer;
int capacity;
int size;

public:
explicit Stack(int bufferSize)
{
buffer = new int[bufferSize];
capacity = bufferSize;
size = 0;
}
Stack()
{
buffer = nullptr;
capacity = 0;
size = 0;
}
void grow()
{
int* newBuffer = new int[std::max(capacity * growCoefficient, initSize)];
for (int i = 0; i < capacity; ++i) {
newBuffer[i] = this->buffer[i];
}
capacity = std::max(capacity * growCoefficient, initSize);
delete[] buffer;
buffer = newBuffer;
}
bool isEmpty()
{
if (size == 0) {
return true;
}
return false;
}
void Push(int element)
{
if (size == capacity) {
grow();
}
buffer[size] = element;
size += 1;
}
int Pop()
{
if (isEmpty()) {
return -1;
}
size = size - 1;
return buffer[size];
}
int GetSize()
{
return size;
}
int* GetBuffer()
{
return buffer;
}
int CutStack(Stack& source)
{
if (source.GetSize() == 0)
return inStackZero;
int sourceStartSize = source.GetSize();
for (int i = 0; i < sourceStartSize; ++i) {
Push(source.Pop());
}
return success;
}
void Clear()
{
size = 0;
}
void Print()
{
for (int i = 0; i < GetSize(); ++i) {
cout << (GetBuffer())[i];
}
cout << endl;
}
~Stack()
{
delete[] buffer;
}
};
class Queue {
Stack inStack, outStack;

public:
explicit Queue(int size)
: inStack(size)
, outStack(size)
{
}
Queue()
: inStack(0)
, outStack(0)
{
}
void PushBack(int element)
{

inStack.Push(element);
}
int PopFront()
{
if (outStack.GetSize() == 0) {
if (outStack.CutStack(inStack) == inStackZero) {
return -1;
};
}

return outStack.Pop();
}
bool IsEmpty()
{
if (inStack.GetSize() == 0 || outStack.GetSize() == 0) {
return true;
}
return false;
}
};

int main()
{
Queue queue;
int commands_quanity = 0;
cin >> commands_quanity;
int command = 0, value = 0;
for (int i = 0; i < commands_quanity; ++i) {
cin >> command;
cin >> value;
if (command == 3) {
queue.PushBack(value);
};
if (command == 2) {
if (queue.PopFront() != value) {
cout << "NO" << endl;
return 0;
};
};
}
cout << "YES" << endl;
return 0;
}