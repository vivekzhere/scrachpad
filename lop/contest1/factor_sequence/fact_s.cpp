#include <iostream>
#include <vector>
#define max_n 1000001

using namespace std;

typedef unsigned long long ull;

int main ()
{
	ull t, n, i, j;

	cin>>t;
	vector<ull> array(max_n, 1);
	vector<ull> sum(max_n, 0);

	sum[0] = sum[1] = 0;
	for (i = 2; i < (max_n/2) + 1; i++) {
		for (j = 2*i; j < max_n; j+=i)
			array[j]+=i;
	}
	for (i = 2; i < max_n; i++) {
		sum[i] = sum[i-1] + array[i];
	}
	while (t-- > 0) {
		cin>>n;
		
		if (n < 2) {
			cout<<0<<endl;
			continue;
		}
		cout<<sum[n]<<endl;
	}
	return 0;
}
