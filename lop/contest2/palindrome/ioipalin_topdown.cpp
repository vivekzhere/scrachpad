#include <iostream>
#include <vector>
#include <string>

#define max_n 5001
#define max(a, b) (((a) > (b))? (a) : (b))
#define min(a, b) (((a) < (b))? (a) : (b))

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

//vector<vector<short> > st(max_n, vector<short> (max_n, -1));
short st[max_n][max_n];
string txt;

void palin(int start, int end) {
	if(txt[start] == txt[end]) {
		if (st[start + 1][end - 1] == -1)
			palin(start + 1, end - 1);
		st[start][end] = st[start + 1][end - 1];
	} else {
		if (st[start + 1][end] == -1)
			palin(start + 1, end);
		if (st[start][end - 1] == -1)
			palin(start, end - 1);

		st[start][end] = min(st[start + 1][end], st[start][end - 1]) + 1;
	}
}
int main ()
{
	int n;
	int i, j;

	cin>>n;
	cin>>txt;

	for (i = 0; i < n; i++) {
		st[i][i] = 0;
		for(j = i + 1; j < n; j++) {
			st[i][j] = -1;
		}
	}
	palin(0, n - 1);

	cout<<st[0][n - 1]<<endl;
	return 0;
}

