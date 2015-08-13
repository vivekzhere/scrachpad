#include <stdio.h>
 
#define max_n 1000000009
 
#define max(a, b) (((a) > (b))? (a) : (b))
#define abs(a) (((a) < 0) ? (-1 * (a)) : (a))
 
#define mod(a, b) ((a) % (b))
#define mod_mul(a, b, c) (mod((a) * (b), c))
#define mod_add(a, b, c) (mod((a) + (b), c))
 
using namespace std;
 
int paint[100001] = {0};
 
int main ()
{
	int t, n, m, i, j, index, col;
	char coll;
	long long ans;
	 
	scanf("%d", &t);
	while (t-- > 0) {
		scanf("%d%d",&n,&m);
		ans = 1;
		 
		for (i = 0; i < m; i++) {
			scanf(" %c%d", &coll, &index);
			paint[index] = (int) coll;
		}
		 
		i = 1;
		if (paint[1] == 0)
			while(paint[++i] == 0);
		index = i;
		col = paint[i];
		j = 0;
		while(j < m ) {
			if (paint[i] == col) {
				index = i;
				paint[i] = 0;
				j++;
				if ( j >= m)
					break;
				while(paint[++i] == 0);
				continue;
			}
			ans = mod_mul(ans, i - index, max_n);
			index = i;
			col = paint[i];
			paint[i] = 0;
			j++;
			if ( j >= m)
				break;
			while(paint[++i] == 0);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
