#include <iostream>
using namespace std;

int f(int n)
{
    cout << "Calling f(" << n << ")\n";
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return f(n-1) + f(n-2);
}

int main()
{
    int n = 0;
    int fnMinus2 = 0;
    int fnMinus1 = 1;
    int fn = 0;

    cout << "Enter a value for N:\n";
    cin >> n;

    for (int counter = 2; counter <= n; counter++)
    {
        fn = fnMinus1 + fnMinus2;
        fnMinus2 = fnMinus1;
        fnMinus1 = fn;
    }

    cout << "Iterative solution: " << fn << endl;
    cout << "Recursive solution: " << f(n) << endl;

    return 0;
}

