#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int MAX_VALUE = 9;

void print(int* data, int size)
{
    for(int i = 0; i < size; i++)
        cout << data[i] << " ";
    cout << "\n";
}

void countingSort(int in[], int out[], int size)
{
    int count[MAX_VALUE + 1];

    for(int i = 0; i < MAX_VALUE + 1; i++)
        count[i] = 0;

    for(int i = 0; i < size; i++)
        count[in[i]]++;

    print(count, MAX_VALUE+1);

    for(int i = 1; i < MAX_VALUE + 1; i++)
        count[i] = count[i] + count[i-1];

    print(count, MAX_VALUE+1);

    for(int i = size - 1; i >= 0; i--)
    {
        out[count[in[i]]-1] = in[i];
        count[in[i]]--;
    }
}

int main()
{
    srand(time(NULL));

    int size = 10;
    int unsorted[size];

    for(int i = 0; i < size; i++)
        unsorted[i] = rand() % (MAX_VALUE + 1);

    print(unsorted, size);
    int sorted[size];
    countingSort(unsorted, sorted, size);
    print(sorted, size);

    return 0;
}
