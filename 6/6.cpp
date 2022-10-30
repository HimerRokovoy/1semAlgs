#include <assert.h>
#include <iostream>

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
cout << "bufferSize = " << bufferSize << endl;
cout << "bufferCapacity = " << bufferCapacity << endl;
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
bool ascending(const size_t& element1, const size_t& element2)
{
if (element1 <= element2) {
return true;
}
return false;
}
bool descending(const size_t& element1, const size_t& element2)
{
if (element1 >= element2) {
return true;
}
return false;
}
template <class T>
T mediana(T el1, T el2, T el3, bool (*compare)(const T&, const T&) = descending)
{
if (compare(el1, el2)) {
if (compare(el2, el3)) {
return el2;
} else {
if (compare(el1, el3)) {
return el3;
} else {
return el1;
}
}
} else {
if (compare(el3, el1)) {
if (compare(el2, el3)) {
return el3;
} else {
return el2;
}
} else {
return el1;
}
}
}

template <class T>
size_t partition(T* arr, size_t begin, size_t end, bool (*compare)(const T&, const T&) = ascending)
{
T pivot = mediana(arr[begin], arr[(begin + end) / 2], arr[end - 1], compare);
size_t pivotI;
if (pivot == arr[begin]) {
std::swap(arr[begin], arr[end - 1]);
} else {
if (pivot == arr[(begin + end) / 2]) {
std::swap(arr[(begin + end) / 2], arr[end - 1]);
}
}
size_t i = begin, j = begin;
for (size_t k = begin; k < end - 1; ++k) {
if (compare(arr[j], pivot)) {
std::swap(arr[j], arr[i]);
++i;
++j;
} else {
++j;
}
}
std::swap(arr[i], arr[end - 1]);
return i;
}
template <class T>
T kOrdinalStatistics(T* arr, size_t size, size_t k, bool (*compare)(const T&, const T&) = ascending)
{
size_t begin = 0, end = size, pivotI = 0;
while (true) {
pivotI = partition(arr, begin, end, compare);
if (k == pivotI) {
return arr[k];
}
if (k < pivotI) {
end = pivotI;
}
if (k > pivotI) {
begin = pivotI + 1;
}
}
};
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
template <class T>
void countKOS(T* arr, size_t size, T& percentile10, T& mediana, T& percentile90, bool (*compare)(const T&, const T&) = ascending)
{
percentile10 = kOrdinalStatistics(arr, size, size / 10, compare);
mediana = kOrdinalStatistics(arr, size, size / 2, compare);
percentile90 = kOrdinalStatistics(arr, size, size * 9 / 10, compare);
}
template <class T>
void printResult(T percentile10, T mediana, T percentile90)
{
cout <<
percentile10 << endl;
cout << mediana << endl;
cout << percentile90 << endl;
}
int main()
{
MyDArray<size_t> arr;
initArr(arr);
size_t percentile10, mediana, percentile90;
countKOS(&arr[0], arr.getSize(), percentile10, mediana, percentile90, ascending);
printResult(percentile10, mediana, percentile90);
}