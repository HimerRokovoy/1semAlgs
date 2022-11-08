#include <assert.h>
#include <iostream>

#define growCoefficient 2
#define initSize 1
#define success 0

using namespace std;

class Process {
public:
Process()
{
P = 0;
t = 0;
T = 0;
}
Process(int priority, int fullTime)
: P(priority)
, t(0)
, T(fullTime)
{
}
int GetPriority() const
{
return P;
}
int GetRemainingTime() const
{
return t;
}
int GetAllTime() const
{
return T;
}
void Execute()
{
t += P;
}
bool IsCompleted() const
{
if (t >= T) {
return true;
}
return false;
}
friend std::ostream& operator<<(ostream& os, Process process);
friend bool CompareProcess(const Process proc1, const Process proc2);
friend bool CompareProcessReverse(const Process proc1, const Process proc2);

private:
int P;
int t;
int T;
};
bool CompareProcess(const Process& proc1, const Process& proc2)
{
if ((proc1.GetPriority() * (proc1.GetRemainingTime() + 1)) > (proc2.GetPriority() * (proc2.GetRemainingTime() + 1))) {
return true;
}
return false;
}
bool CompareProcessReverse(const Process& proc1, const Process& proc2)
{
if ((proc1.GetPriority() * (proc1.GetRemainingTime() + 1)) < (proc2.GetPriority() * (proc2.GetRemainingTime() + 1))) {
return true;
}
return false;
}

std::ostream& operator<<(ostream& os, Process process)
{
os << "P = " << process.P << " t = " << process.t << " T = " << process.T << endl;
return os;
}

template <class T>
class Heap {
public:
Heap()
{
arr = nullptr;
arrSize = 0;
arrCapacity = 0;
}
Heap(T* array, int arraySize, bool (*Compare)(const T&, const T&))
{
this->Compare = Compare;
arrCapacity = arrSize = arraySize;
arr = new T[arrSize];
for (int i = 0; i < arrSize; ++i) {
arr[i] = array[i];
}
buildHeap();
}
~Heap()
{
if (arr != nullptr) {
delete[] arr;
}
}
void Insert(const T element)
{
if (arrSize == arrCapacity) {
grow();
}
arr[arrSize] = element;
siftUp(arrSize, Compare);
++arrSize;
}
T ExtractMax()
{
if (arrSize <= 0) {
assert(false && "In ExtractMax arrSize <= 0");
}
swap(arr[0], arr[arrSize - 1]);
PrintHeap();
--arrSize;
siftDown(0, Compare);
return arr[arrSize];
}
T PeekMax() const
{
if (arrSize > 0) {
assert(false && "In PeekMax arrSize <= 0");
}
return arr[0];
};
bool IsEmpty()
{
if (arrSize == 0) {
return true;
}
return false;
}
void buildHeap()
{
for (int i = arrSize / 2 - 1; i >= 0; --i) {
siftDown(i, Compare);
}
}
void PrintHeap()
{
for (int i = 0; i < arrSize; ++i) {
}
}

private:
T* arr;
int arrSize;
int arrCapacity;
bool (*Compare)(const T&, const T&);
void siftDown(int index, bool (*Compare)(const T&, const T&))
{
if (2 * index + 1 >= arrSize) {
return;
};
if (Compare(arr[index], arr[2 * index + 1])) {
swap(arr[index], arr[2 * index + 1]);
siftDown(2 * index + 1, Compare);
} else {
if (2 * index + 2 >= arrSize) {
return;
};
if (Compare(arr[index], arr[2 * index + 1])) {
swap(arr[index], arr[2 * index + 2]);
siftDown(2 * index + 2, Compare);
}
}
}
void siftUp(int index, bool (*Compare)(const T&, const T&))
{
while (index > 0) {
int parentInd = (index - 1) / 2;
if (!(Compare(arr[parentInd], arr[index]))) {
return;
};
swap(arr[index], arr[parentInd]);
index =
parentInd;
}
}
void grow()
{
T* newBuffer = new T[std::max(arrCapacity * growCoefficient, initSize)];
for (int i = 0; i < arrCapacity; ++i) {
newBuffer[i] = this->arr[i];
}
arrCapacity = std::max(arrCapacity * growCoefficient, initSize);
delete[] arr;
arr = newBuffer;
}
};

template <class T>
class PriorityQueue {
public:
PriorityQueue()
: heap()
{
}
PriorityQueue(T* array, int arraySize, bool (*Compare)(const T&, const T&))
: heap(array, arraySize, Compare)
{
}
PriorityQueue(T element)
: heap(element)
{
}
void PushBack(T element)
{
heap.Insert(element);
}
T PopFront()
{
return heap.ExtractMax();
}
T PeekMax()
{
return heap.PeekMax();
}
bool IsEmpty()
{
return heap.IsEmpty();
}
void PrintQueue()
{
heap.PrintHeap();
}

private:
Heap<T> heap;
};

int main()
{
int arrSize = 0;
cin >> arrSize;
Process* arrProcess = new Process[arrSize];
for (int i = 0; i < arrSize; ++i) {
int priority, fullTime;
cin >> priority;
cin >> fullTime;
arrProcess[i] = Process(priority, fullTime);
};
PriorityQueue<Process> pQueue(arrProcess, arrSize, CompareProcess);
int counter = 0;
pQueue.PrintQueue();
while (!pQueue.IsEmpty()) {
Process process = (pQueue.PopFront());
pQueue.PrintQueue();
process.Execute();
pQueue.PrintQueue();
if (!process.IsCompleted()) {
pQueue.PushBack(process);
};
++counter;
pQueue.PrintQueue();
}
cout << counter;
delete[] arrProcess;
return 0;
}