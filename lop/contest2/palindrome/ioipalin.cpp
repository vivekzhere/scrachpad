#include <iostream>
#include <vector>
#include <string>

#define max_n 5001
#define max(a, b) (((a) > (b))? (a) : (b))
#define min(a, b) (((a) < (b))? (a) : (b))

#define val(i, j) (((i) < (j)) ? (st[(i)&1][(j)]) : 0 )

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

//vector<vector<short> > st(max_n, vector<short> (max_n, -1));
short st[2][max_n];
string txt;

int main ()
{
	int n;
	int i, j;

	cin>>n;
	cin>>txt;

	for (i = n - 1; i >= 0; i--) {
		for(j = i + 1; j < n; j++) {
			if (txt[i] == txt[j])
				st[i&1][j] = val(i + 1, j - 1);
			else
				st[i&1][j] = min(val(i + 1, j), val(i, j - 1)) + 1;
		}
	}
	cout<<st[0][n - 1]<<endl;
	return 0;
}

