#include <assert.h>
#include <bitset>
#include <iostream>
#include <unistd.h>

#define growCoefficient 2
#define initSize 1
#define success 0

using namespace std;

template <class T>
class MyDArray {
public:
MyDArray()
: buffer(nullptr)
, bufferCapacity(0)
, bufferSize(0)
{
}
~MyDArray()
{
delete[] buffer;
}
int getSize() const
{
return bufferSize;
}
T& getAt(int index)
{
assert(index >= 0 && "index >= 0");
assert(index < bufferSize && "index <= bufferSize");
assert(buffer != nullptr && "buffer != nullptr");
return buffer[index];
}
T& operator[](int index)
{
return getAt(index);
}
void Add(T element)
{
if (bufferSize == bufferCapacity) {
_grow();
}
assert(buffer != nullptr && "buffer != nullptr");
buffer[bufferSize] = element;
++bufferSize;
}
void printArr()
{
for (int i = 0; i < bufferSize; ++i) {
cout << buffer[i] << " ";
}
cout << endl;
}

private:
T* buffer;
int bufferCapacity;
int bufferSize;
void _grow()
{
T* newBuffer = new T[std::max(bufferCapacity * growCoefficient, initSize)];
for (int i = 0; i < bufferCapacity; ++i) {
newBuffer[i] = this->buffer[i];
}
bufferCapacity = std::max(bufferCapacity * growCoefficient, initSize);
delete[] buffer;
buffer = newBuffer;
}
};
void print64(uint64_t el)
{
std::bitset<64> x { el };
std::cout << x << endl;
}
template <class T>
void binPartition(T* arr, size_t begin, size_t end, size_t bitNumber)
{
if (begin == end) {
return;
}
if (begin == end - 1) {
return;
}
uint64_t pivot = uint64_t(1) << bitNumber;
size_t i = begin, j = begin;
for (size_t k = begin; k < end; ++k) {
if ((arr[j] & (pivot)) == uint64_t(0)) {
std::swap(arr[j], arr[i]);
++i;
++j;
} else {
++j;
}
}
if (bitNumber == 0) {
return;
}
binPartition(arr, begin, i, bitNumber - 1);
binPartition(arr, i, end, bitNumber - 1);
return;
}
template <class T>
void initArr(MyDArray<T>& arr)
{
size_t size = 0;
cin >> size;
for (int i = 0; i < size; ++i) {
size_t element;
cin >> element;
arr.Add(element);
}
}
int main()
{
MyDArray<uint64_t> arr;
initArr(arr);
binPartition(&arr[0], 0, arr.getSize(), size_t(63));
arr.printArr();
}