#include <iostream>
using namespace std;

void exchangeChars(string& word, int i, int j)
{
    char temp = word[i];
    word[i] = word[j];
    word[j] = temp;
}

void permute(string word, int k)
{
    if(k == word.length())
        cout << word << "\n";
    else
    {
        for(int j = k; j < word.length(); j++)
        {
            exchangeChars(word, k, j);
            permute(word, k+1);
            exchangeChars(word, j, k);
        }
    }
}

int main()
{
    string word = "programming";
    permute(word, 0);

    return 0;
}
