#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void print(const int* arr, const int size)
{
    for(int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

int* createArrayHeap(const int size)
{
    int* arr = new int[size];

    for(int i = 0; i < size; i++)
        arr[i] = rand() % 100;

    cout << "Inside createArrayHeap\n";
    print(arr, size);
    cout << "Address = " << arr << "\n";
    return arr;
}

int* createArrayStack(const int size)
{
    int arr[size];

    for(int i = 0; i < size; i++)
        arr[i] = rand() % 100;

    cout << "Inside createArrayStack\n";
    print(arr, size);
    return arr;
}

int main()
{
    srand(time(NULL));

    int size = 10;

    int* numbers1 = createArrayHeap(size);
    cout << "In main:\n";
    print(numbers1, size);
    cout << "Address = " << numbers1 << "\n";

    int* numbers2 = createArrayStack(size);
    cout << "In main:\n";
    print(numbers2, size);

    return 0;
}
