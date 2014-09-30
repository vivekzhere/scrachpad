#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned int uint32;
typedef signed int int32;
typedef unsigned long long uint64;
typedef signed long long int64;

int next_right(char H[], int i, int len)
{
	int j;

	for (j = i + 1; H[j] == 'c' && j < len; j++);
	return j;
}

int next_left(char H[], int i, int len)
{
	int j;

	for (j = i - 1; H[j] == 'c' && j >= 0; j--);
	return j;
}

int main()
{
	int t, i, j, len, count, ans, ni, nj;
	char H[100001];
	
	scanf("%d", &t);

	while(t-- > 0) {
		scanf("%s", H);

		for (i = 0; H[i] != '\0'; i++);
		len = i;
		count = 0;
		ans = 1;
		for (i = 0, j = len - 1; count < len;)
		{
	//	printf ("%s:%d:i %d: j %d: count %d: ans %d\n", H, len, i, j, count, ans);
			if (i > j) {
				ans++;
				i = 0;
				j = len - 1;
				continue;
			}
			if (H[i] == 'c') {
				i = next_right(H, i, len);
				continue;
			}
			if (H[j] == 'c') {
				j = next_left(H, j, len);
				continue;
			}

			if (H[i] == H[j]) {
				H[i] = 'c';
				H[j] = 'c';
				i = next_right(H, i, len);
				j = next_left(H, j, len);
				count++;
				if ( i != j)
					count++;

				continue;
			}
			
			ni = next_right(H, i, len);
			if (ni >= len) {
				i = ni;
				continue;
			}
			if (H[ni] == H[j]) {
				i = ni;
				continue;
			}

			nj = next_left(H, j, len);
			if (nj < 0) {
				j = nj;
				continue;
			}
			if (H[i] == H[nj]) {
				j = nj;
				continue;
			}
			i = ni;
			j = nj;
		}
		printf("%d\n", ans);
	}

	return 0;
}
