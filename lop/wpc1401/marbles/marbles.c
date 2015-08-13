#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned int uint32;

int main()
{
	uint32 t, n, sum;

	scanf("%u", &t);

	while (t > 0) {
		scanf("%u", &n);
		sum = (n * (n + 1)) / 2;
		printf("%u\n", sum);
		t--;
	}
	return 0;
}
