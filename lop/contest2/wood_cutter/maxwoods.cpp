#include <iostream>
#include <vector>
#define max_n 201
#define max(a, b) (((a) > (b))? (a) : (b))
#define min(a, b) (((a) < (b))? (a) : (b))


using namespace std;

typedef unsigned long long ull;
typedef long long ll;

int main ()
{
	int t, m, n, i, j, ans, incr;
	char item;
	short array[max_n][max_n];
	int st[max_n][max_n][2];
	
	cin>>t;
	while (t-- > 0) {
		cin>>m>>n;

		for(i = 0; i < m; i++)
			for(j = 0; j < n; j++) {
				cin>>item;
				if(item == '0')
					array[i][j] = 0;
				else if (item == 'T')
					array[i][j] = 1;
				else
					array[i][j] = -1;
				st[i][j][0] = st[i][j][1] = -1;
			}

		/* Third index 1 means facing right, 0 means left 
		 * Value at third index is max num trees cut to reach the config.
		 * value -1 means config invalid/ not yet calculated */
		if (array[0][0] == -1) {
			cout<<0<<endl;
			continue;
		}
		st[0][0][1] = array[0][0];
		ans = array[0][0];

		j = -1;
		for(i = 0; i < m; i++) {
			incr = (i&1)*-2 + 1;
			for (j+=incr; ((incr - 1) || j < n) && ((incr + 1) || j >= 0); j+=incr) {
				if(st[i][j][0] != -1) { /*left facing */
					if (j != 0 && array[i][j - 1] != -1) {
						st[i][j - 1][0] = max(st[i][j - 1][0], st[i][j][0] + array[i][j - 1]);
						ans = max(ans, st[i][j - 1][0]);
					}
					if (i != m - 1 && array[i + 1][j] != -1) {
						st[i + 1][j][1] = max(st[i + 1][j][1], st[i][j][0] + array[i + 1][j]);
						ans = max(ans, st[i + 1][j][1]);
					}
				}
				if(st[i][j][1] != -1) { /*rightfacing */
					if (j != n - 1 && array[i][j + 1] != -1) {
						st[i][j + 1][1] = max(st[i][j + 1][1], st[i][j][1] + array[i][j + 1]);
						ans = max(ans, st[i][j + 1][1]);
					}
					if (i != m - 1 && array[i + 1][j] != -1) {
						st[i + 1][j][0] = max(st[i + 1][j][0], st[i][j][1] + array[i + 1][j]);
						ans = max(ans, st[i + 1][j][0]);
					}
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}

