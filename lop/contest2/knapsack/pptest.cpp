#include <iostream>
#include <vector>
#define max_n 103
#define max(a, b) (((a) > (b))? (a) : (b))
#define min(a, b) (((a) < (b))? (a) : (b))

#define val(i, j) ( ((j) > 0)?st[(i)][(j) & 1] : 0)

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

int main ()
{
	short t, n, w, i, j, c, p;
	short C[max_n], T[max_n], st[max_n][2];
	
	cin>>t;
	st[0][0] = st[0][1] = 0;
	while (t-- > 0) {
		cin>>n>>w;
		for (i = 1; i <= n; i++) {
			cin>>c>>p>>T[i];
			C[i] = c * p;
		}

		for (j = 1; j <= n; j++) {
			for (i = 1; i <= w; i++) {
				if (i - T[j] < 0)
					st[i][j & 1] = val(i, j - 1);
				else
					st[i][j & 1] = max(val(i - T[j], j - 1) + C[j], val(i, j - 1));
			}
		}
		cout<<st[w][n & 1]<<endl;
	}
	return 0;
}

