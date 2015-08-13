#include <iostream>
using namespace std;

int main ()
{
	int t, n, m, a, max, sum, i;
	cin>>t;
	while (t-- > 0) {
		cin>>n>>m;

		max = 0;
		sum = m;

		for(i = 0; i < n; i++) {
			cin>>a;
			if (a > max)
				max = a;
			sum += a;
		}
		if (sum % n == 0 && sum/n >= max)
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
	return 0;
}

