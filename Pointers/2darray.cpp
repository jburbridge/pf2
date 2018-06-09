#include <array>
#include <iostream>
using namespace std;

void print(int** arr, const int rows, const int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            cout << arr[i][j] << " ";
        cout << "\n";
    }
}

int main()
{
    const int rows = 10, cols = 10;

    //Create and allocate memory for 2D array
    int** arr = new int*[rows];
    for(int i = 0; i < rows; i++)
        arr[i] = new int[cols];

    //Initialize the array
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            arr[i][j] = i + j;

    //Print the address where each row is stored
    for(int i = 0; i < rows; i++)
        cout << arr[i] << " ";
    cout << "\n";

    //Pass the array to the print function
    print(arr, rows, cols);

    //Test the array class in C++
    array<float, 10> arr2;
    for(int i = 0; i < 10; i++)
    {
        arr2[i] = 1.1 * i;
        cout << arr2[i] << " ";
        //cout << arr2.at(i) << " ";
    }
    cout << "\n";

    return 0;
}
