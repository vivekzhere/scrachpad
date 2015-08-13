#include <iostream>
#define long long ll
using namespace std;

int main ()
{
	int t;
	long long x, n, m;

	cin>>t;

	while(t-- > 0) {

}

ll modular_pow(ll base, ll exponent, int modulus)
{

    ll result = 1;

    while (exponent > 0)

    {

        if (exponent % 2 == 1)

            result = (result * base) % modulus;

        exponent = exponent >> 1;

        base = (base * base) % modulus;

    }

    return result;

}
