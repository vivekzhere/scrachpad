#include <stdio.h>
 
#define max_n 1000000009
 
#define max(a, b) (((a) > (b))? (a) : (b))
#define min(a, b) (((a) < (b))? (a) : (b))
#define abs(a) (((a) < 0) ? (-1 * (a)) : (a))
 
#define mod(a, b) ((a) % (b))
#define mod_mul(a, b, c) (mod((a) * (b), c))
#define mod_add(a, b, c) (mod((a) + (b), c))

#define max_i(x) ((x[0] >= x[1] && x[0] >= x[2])? 0: ((x[1] >= x[2])?1:2))
 
using namespace std;
 
 
int main ()
{
	int t, m, r, g, b, item, max[3], i;
	 
	scanf("%d", &t);
	while (t-- > 0) {
		scanf("%d %d %d %d", &r, &g, &b, &m);
		max[0] = max[1] = max[2] = 0;
		 
		for (i = 0; i < r; i++) {
			scanf("%d", &item);
			max[0] = max(item, max[0]);
		}
		for (i = 0; i < g; i++) {
			scanf("%d", &item);
			max[1] = max(item, max[1]);
		}
		for (i = 0; i < b; i++) {
			scanf("%d", &item);
			max[2] = max(item, max[2]);
		}

		for ( i = 0; i < m; i++) {
			item = max_i(max);
			if (max[item] == 0)
				break;
			max[item] = max[item] >> 1;
		}

		printf("%d\n",max[max_i(max)]);
	}
	return 0;
}
