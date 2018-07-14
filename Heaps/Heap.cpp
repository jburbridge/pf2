#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class Heap
{
public:
    Heap(const int size);
    ~Heap();

    bool isFull();
    bool search(const int val);
    bool insert(const int val);
    bool removeTop();
    int peekTop();

    void print();

private:
    int MAX_HEAP_SIZE;
    int heap_size;
    int* data;

    //Internal helper functions
    int left(const int i);
    int right(const int i);
    int parent(const int i);

    void swap(int& a, int& b);
    void percolateUp(const int i);
    void percolateDown(const int i);
};

Heap::Heap(const int size)
{
    MAX_HEAP_SIZE = size;
    heap_size = 0;
    data = new int[MAX_HEAP_SIZE];
}

Heap::~Heap()
{
    delete [] data;
}

bool Heap::isFull()
{
    if(heap_size == MAX_HEAP_SIZE)
        return true;
    else
        return false;
}

//Heap is not strictly ordered, so we have to search everything
//Possible optimization: if data[i] < val, val will not be in that subheap, so skip ahead
bool Heap::search(const int val)
{
    for(int i = 0; i < heap_size; i++)
        if(data[i] == val)
            return true;
    return false;
}

bool Heap::insert(const int val)
{
    if(!isFull())
    {
        data[heap_size] = val;
        heap_size++;
        percolateUp(heap_size-1);
        return true;
    }
    else
        return false;
}

bool Heap::removeTop()
{
    heap_size--;
    data[0] = data[heap_size];
    percolateDown(0);
}

int Heap::peekTop()
{
    return data[0];
}

void Heap::print()
{
    for(int i = 0; i < heap_size; i++)
        cout << data[i] << " ";
    cout << "\n";
}

int Heap::left(const int i)
{
    return 2*i + 1;
}

int Heap::right(const int i)
{
    return 2*i + 2;
}

int Heap::parent(const int i)
{
    return ceil(i/2) - 1;
}

void Heap::swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void Heap::percolateUp(const int i)
{
    if(i <= 0 || i >= heap_size)
        return;

    int p = parent(i);
    if(data[i] > data[p])
    {
        swap(data[i], data[p]);
        percolateUp(p);
    }
}

void Heap::percolateDown(const int i)
{
    int lc = left(i);
    int rc = right(i);
    int largest;

    if(lc <= heap_size && data[lc] > data[i])
        largest = lc;
    else
        largest = i;

    if(rc <= heap_size && data[rc] > data[largest])
        largest = rc;

    if(largest != i)
    {
        swap(data[i], data[largest]);
        percolateDown(largest);
    }
}

int main()
{
    srand(time(NULL));

    int size = 10;
    Heap h(size);

    for(int i = 0; i < size; i++)
    {
        h.insert(rand() % 100);
        h.print();
    }

    h.removeTop();
    h.print();

    return 0;
}
