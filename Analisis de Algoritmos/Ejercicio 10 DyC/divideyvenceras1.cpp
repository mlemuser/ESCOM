#include <iostream>
using namespace std;

int main(void)
{
    ios::sync_with_stdio(false);
    long long int n, auxI, maxMax = -1e9, maxAhora = 0;
    cin >> n;
    for(int i = 0 ; i < n ; i++)
    {
        cin >> auxI;
        maxAhora = maxAhora + auxI;
        if(maxMax < maxAhora)
            maxMax = maxAhora;
        if(maxAhora < 0)
            maxAhora = 0;
    }
    cout << maxMax << "\n";
    return 0;
}
