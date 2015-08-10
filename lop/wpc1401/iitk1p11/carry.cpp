#include <iostream>
using namespace std;

int main ()
{
	int t, n;

	cin>>t;

	while(t-- > 0) {
		cin>>n;
		
		if ( n == 1 || n == 10 || n == 100 || n == 1000 || n == 10000 || n == 100000)
			cout<<"NO\n";
		else
			cout<<"YES\n";
	}

	return 0;
}
