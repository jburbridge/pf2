#include <iostream>
using namespace std;

char* findEnd(char word[])
{
    //Create pointer to beginning of char array
    char* out = word;

    //While we haven't found the null terminator, increment pointer
    while (*out != '\0')
        out++;

    //Return pointer
    return out;
}

int main()
{
    //Length is 23 characters
    char word[] = "Pointers are super fun.";

    //Find the end of the string and create a pointer to it
    char* endMarker = findEnd(word);

    //Print starting address of array
    cout << &word << endl;

    //Print ending address of array.
    //When a char pointer appears in a cout statement, C++ tries to treat it like a string.
    //Thus, to print the actual address stored by the char pointer, we have to cast it to a
    //void pointer. In other words, a pointer with no type.
    cout << (void*) endMarker << endl;

    //Subtract the starting address from the ending address to get the length of the string.
    //EndMarker has to be cast to void pointer again, and word must be cast to int.
    //Without these casts, C++ would think we're trying to subtract a string from another string.
    cout << "The length of the string is " << (void*) endMarker - (int) word << endl;

    return 0;
}
