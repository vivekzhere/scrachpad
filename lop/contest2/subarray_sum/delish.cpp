#include <iostream>
#include <vector>
#define max_n 10001
#define max(a, b) (((a) > (b))? (a) : (b))
#define min(a, b) (((a) < (b))? (a) : (b))

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

int main ()
{
	int t, n, i;
	ll item, ans;
	ll array[max_n], till_i[max_n][2], from_i[max_n][2];
	
	cin>>t;
	while (t-- > 0) {
		cin>>n;

		cin>>item;
		array[0] = item;
		till_i[0][0] = till_i[0][1] = item;
		
		for (i = 1; i < n; i++) {
			cin>>item;
			array[i] = item;

			till_i[i][0] = max(item, till_i[i - 1][0] + item);
			till_i[i][1] = min(item, till_i[i - 1][1] + item);
		}

		from_i[n - 1][0] = from_i[n - 1][1] = array[n - 1];
		for(i = n - 2; i >= 0; i--) {
			from_i[i][0] = max(array[i], from_i[i + 1][0] + array[i]);
			from_i[i][1] = min(array[i], from_i[i + 1][1] + array[i]);
		}

		ans = 0;
		for(i = 0; i < n - 1; i++) {
			ans = max(ans, till_i[i][0] - from_i[i + 1][1]);
			ans = max(ans, from_i[i + 1][0] - till_i[i][1]);
		}
		cout<<ans<<endl;
	}
	return 0;
}

