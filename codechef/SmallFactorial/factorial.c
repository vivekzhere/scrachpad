#include<stdio.h>
#include<stdlib.h>

void print_int(int result[], int m)
{
	for (m--; m>=0; m--)
		printf("%d", result[m]);
}

int multiply(int result[], int n, int m)
{
	int temp = 0, i;

	for (i = 0; i < m; i++) {
		temp += result[i] * n;
		result[i] = temp % 10;
		temp = temp / 10;
	}
	
	while ( temp > 0) {
		result[m] = temp % 10;
		m++;
		temp = temp / 10;
	}
	return m;
}

int main()
{
	int result[200], m, i, n, t;

	scanf("%d", &t);
	while (t>0) {
		t--;
		scanf("%d", &n);
		m = 1;
		result[0] = 1;
		for (i = 2; i <= n; i++)
			m = multiply(result, i, m);
		print_int(result, m);
		printf("\n");
	}
	return 0;
}
