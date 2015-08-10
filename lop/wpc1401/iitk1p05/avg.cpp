#include <iostream>
using namespace std;

int main ()
{
	int t, max, n, item;

	cin>>t;

	while(t-- > 0) {
		cin>>n;
		max = 0;
		while(n-- > 0) {
			cin>>item;
			if(item > max)
				max = item;
		}
		cout<<max<<endl;
	}

  return 0;
}
