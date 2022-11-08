#include<iostream>

struct Proces
{
    int priority
};

template <class T>
class Heap
{
 public:
    Heap();
    
    Heap(const Heap&);
    Heap& operator= (const Heap&);

    Heap(Heap&&) = delete;
    Heap& operator= (Heap&&) = delete;

    ~Heap();

    const T& top() const;
    void pop();
    void push(const &T value);
    size_t size() const;
    bool empty() const;

    private:
    void sift_up(size_t idx);
    void sift_down(size_t idx);

};
int main()
{
   
 
}