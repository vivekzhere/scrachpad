#include <iostream>
#include <queue>
#include <vector>

#define max_n 100002
#define max(a, b) (((a) > (b))? (a) : (b))
#define abs(a) (((a) < 0) ? (-1 * (a)) : (a))

using namespace std;

int main ()
{
	int t, n, i, c_d, c_m;
	int ar[max_n];
	long long ans;
	priority_queue<int, vector<int>, greater<int> > dino;
	priority_queue<int, vector<int>, greater<int> > man;

	cin>>t;
	while (t-- > 0) {
		cin>>n;
		ans = 0;
		for ( i = 0; i < n; i++) {
			cin>>ar[i];

			if (ar[i] > 0)
				man.push(i);
			else if (ar[i] < 0)
				dino.push(i);

			while (!man.empty() && !dino.empty()) {
				c_m = man.top();
				c_d = dino.top();
				if (-1 * ar[c_d] >= ar[c_m]) {
					ans += ar[c_m] * abs(c_m - c_d);
					ar[c_d] += ar[c_m];
					if(ar[c_d] == 0)
						dino.pop();
					
					ar[c_m] = 0;
					man.pop();
				} else {
					ans += (-1 * ar[c_d]) * abs(c_m - c_d);
					ar[c_m] += ar[c_d];
					if(ar[c_m] == 0)
						man.pop();
					
					ar[c_d] = 0;
					dino.pop();
				}
			}
		}
		if (!man.empty() || !dino.empty())
			cout<<"Ohhh Noooooo!!!!"<<endl;
		cout<<ans<<endl;
	}
	return 0;
}

