#include<stdio.h>
#include<stdlib.h>

int main()
{
	unsigned int n, t, c10;

	scanf("%u", &t);
	while (t>0) {
		t--;
		scanf("%u", &n);

		c10 = 0;
		
		n = n / 5;
		while (n > 0) {
			c10 += n;
			n = n / 5;
		}
		printf("%u\n", c10);
	}
	return 0;
}
