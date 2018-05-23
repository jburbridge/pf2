#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void linearSearch(int numbers[], int SIZE, int target, int& index, int& numAttempts)
{
    numAttempts = 0;

    for (int i = 0; i < SIZE; i++)
    {
        //Count the number of times this loop iterates
        numAttempts++;

        //If we find the target, save the index and leave the function
        if (numbers[i] == target)
        {
            index = i;
            return;
        }
    }

    index = -1;
}

void binarySearch(int numbers[], int SIZE, int target, int& index, int& numAttempts)
{
    //Make sure numAttemps is 0
    numAttempts = 0;

    //Set inital values for indices
    int left = 0;
    int right = SIZE - 1;
    int middle;

    //While left and right haven't crossed
    while(left <= right)
    {
        //Count the number of times this loop iterates
        numAttempts++;

        //Compute the midpoint
        middle = (left + right) / 2;

        //If target is at the midpoint, we've found it
        if (numbers[middle] == target)
        {
            index = middle;
            return;
        }

        //Check if target is in bottom half of array
        else if (numbers[middle] > target)
            right = middle - 1;

        //Else, target must be in top half
        else
            left = middle + 1;
    }

    index = -1;
}

void print(int numbers[], int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        cout << setw(5) << numbers[i];
        if (i % 10 == 9)
            cout << endl;
    }
}

int main()
{
    srand(time(0));

    int SIZE = 10000;
    int * numbers = new int[SIZE];

    for (int i = 0; i < SIZE; i++)
        numbers[i] = rand() % SIZE;

    sort(numbers, numbers + SIZE);
    print(numbers, SIZE);

    int entry;
    cout << "What number would you like to search for?\n";
    cin >> entry;

    int index, numAttempts;

    cout << "Iterative Binary search: ";
    binarySearch(numbers, SIZE, entry, index, numAttempts);
    if (index == -1)
        cout << entry << " was not found. ";
    else
        cout << entry << " was found at location " << index << ". ";
    cout << "Total numbers checked: " << numAttempts << "\n";

    cout << "Linear search: ";
    linearSearch(numbers, SIZE, entry, index, numAttempts);
    if (index == -1)
        cout << entry << " was not found. ";
    else
        cout << entry << " was found at location " << index << ". ";
    cout << "Total numbers checked: " << numAttempts << "\n";

    delete [] numbers;
    numbers = nullptr;

    return 0;
}
