#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void print(const int* numbers, const int SIZE)
{
    for (int i = 0; i < SIZE; i++)
        cout << numbers[i] << " ";
    cout << endl;
}

void myCopy(const int* src, int* dest, const int SIZE)
{
    for(int i = 0; i < SIZE; i++)
        dest[i] = src[i];
}

void bubbleSort(int* numbers, const int SIZE)
{
    int temp;
    int count = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE - 1; j++)
        {
            if (numbers[j] > numbers[j+1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }

            count++;
        }
    }

    cout << "Bubble Sort completed after " << count << " checks\n";
}

void selectionSort(int* numbers, const int SIZE)
{
    int temp, smallest;
    int count = 0;

    for(int i = 0; i < SIZE - 1; i++)
    {
        //Location smallest number from i onward
        smallest = i;
        for(int j = i + 1; j < SIZE; j++)
        {
            count++;
            if(numbers[j] < numbers[smallest])
                smallest = j;
        }

        //Swap smallest with i
        temp = numbers[smallest];
        numbers[smallest] = numbers[i];
        numbers[i] = temp;
    }

    cout << "Selection Sort completed after " << count << " checks\n";
}

void insertionSort(int* numbers, const int SIZE)
{
    int j;
    int count = 0;

    for(int i = 0; i < SIZE; i++)
    {
        j = i;
        while(j > 0 && numbers[j] < numbers[j-1])
        {
            count++;
            int temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
           // print(numbers, SIZE);
            j--;
        }
    }

     cout << "Insertion Sort completed after " << count << " checks\n";
}

int main()
{
    srand(time(NULL));
    const int SIZE = 30;

    int* original = new int[SIZE];
    int* sortThis = new int[SIZE];

    for(int i = 0; i < SIZE; i++)
    {
        original[i] = rand() % 100;
        sortThis[i] = original[i];
    }

    cout << "Bubble Sort:\n";
    bubbleSort(sortThis, SIZE);
    print(sortThis, SIZE);
    myCopy(original, sortThis, SIZE);

    cout << "\nSelection Sort:\n";
    selectionSort(sortThis, SIZE);
    print(sortThis, SIZE);
    myCopy(original, sortThis, SIZE);


    cout << "\nInsertion Sort:\n";
    insertionSort(sortThis, SIZE);
    print(sortThis, SIZE);
    myCopy(original, sortThis, SIZE);

    return 0;
}
