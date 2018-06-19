#include <iostream>
using namespace std;

int fastExp(int x, int p)
{
    if(p == 0)
        return 1;

    else if(p == 1)
        return x;

    else if(p % 2 == 0)
        return fastExp(x, p/2) * fastExp(x, p/2);

    else
        return x * fastExp(x, p/2)  * fastExp(x, p/2);
}

int main()
{
    int x = 5;
    int p = 9;

    cout << x << "^" << p << " = " << fastExp(x, p) << "\n";
    return 0;
}
