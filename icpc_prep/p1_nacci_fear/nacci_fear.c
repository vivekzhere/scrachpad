#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned int uint32;

#define CACHE_LEN 40
uint32 nnaci_vals[CACHE_LEN];
#define INCR_INDEX(i) (((i) + 1) % CACHE_LEN)
#define DECR_INDEX(i) ((i) ? ((i) - 1) : (CACHE_LEN - 1) )

uint32 nnacci(uint32 n, uint32 l)
{
	uint32 i, head, val;

	if (l < n)
		return l;

	for (head = DECR_INDEX(CACHE_LEN), i = 0; i < n; i++, head = DECR_INDEX(head))
		nnaci_vals[head] = i;

	nnaci_vals[head] = (n * (n -1)) / 2;

	for (i = n + 1; i <= l; i++) {
		val = 2 * nnaci_vals[head] - nnaci_vals[(head + n) % CACHE_LEN];
		head = DECR_INDEX(head);
		nnaci_vals[head] = val;
	}
	
	return nnaci_vals[head];
}

int main()
{
	uint32 t, n, k, l, ans, i, val, mult;

	scanf("%u", &t);

	while (t > 0) {
		scanf("%u %u %u", &n, &k, &l);
		memset(&nnaci_vals[0], 0, sizeof (uint32) * CACHE_LEN);
		ans = nnacci(n, l);
		val = 0;
		mult = 1;
		for ( i = 0; i < k; i++) {
			val = val + (ans % 10) * mult;
			ans = ans / 10;
			mult = mult * 10;
		}
		printf ("%u\n", val);
		t--;
	}
	return 0;
}
