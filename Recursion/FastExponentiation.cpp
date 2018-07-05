#include <iostream>
using namespace std;

int fast_exp_calls = 0;
int faster_exp_calls = 0;

double fastExp(int x, int p)
{
    fast_exp_calls++;

    if(p == 0)
        return 1;

    else if(p == 1)
        return x;

    else if(p % 2 == 0)
        return fastExp(x, p/2) * fastExp(x, p/2);

    else
        return x * fastExp(x, p/2)  * fastExp(x, p/2);
}

double fasterExp(int x, int p)
{
    faster_exp_calls++;

    if(p == 0)
        return 1;

    else if(p == 1)
        return x;

    else if(p % 2 == 0)
    {
        double result = fasterExp(x, p/2);
        return result * result;
    }

    else
    {
        double result = fasterExp(x, p/2);
        return x * result * result;
    }
}

int main()
{
    int x = 5;
    int p = 20;

    cout << x << "^" << p << " = " << fastExp(x, p) << "\n";
    cout << x << "^" << p << " = " << fasterExp(x, p) << "\n";

    cout << "Exp calls: " << fast_exp_calls << "\n";
    cout << "Fast Exp calls: " << faster_exp_calls << "\n";
    return 0;
}
