#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "types_x86_64.h"

/* Given N and M as input (N number of vetrices and M edges),
 * this function creates adjacency matrix by reading M (a, b) pairs
 * from stdin.
 */
uint8* create_adj_matrix(uint32 n, uint32 m)
{
	uint8 *ptr = NULL;
	uint32 i, a, b;

	ptr = malloc (n * n * sizeof (uint8));
	if (!ptr) {
		return NULL;
	}

	(void *)memset((void *)ptr, 0, n * n * sizeof (uint8));

	for (i = 0; i < m; i++) {
		scanf("%u %u", &a, &b);
		if (a != b)
			ptr[(a-1) * n + b - 1] = 1;
	}
	return ptr;
}
void delete_adj_matrix(uint32 n, uint32 m, uint8** adj)
{
	if(adj && *adj) {
		free(*adj);
		*adj = NULL;
	}
}

uint32 chef_reversing(uint8* adjm, uint32* cache, uint32 n, uint32 m, uint32 min, uint32 rev_cnt, uint32 path_len, uint32 node)
{
	uint32 i, retval, flag = 0;
	
	if (path_len >= n)
		return m + 1;

	if (cache[node] <= m)
		return rev_cnt + cache[node];
	else if (cache[node] == m + 1)
		return m + 1;
	else if (rev_cnt > min)
		return m + 2;

	path_len++;

	for (i = 0; i < n; i++) {
		if (adjm[node * n + i] || adjm[i * n + node]) {
			if (adjm[node * n + i])
				retval = chef_reversing(adjm, cache, n, m, min, rev_cnt, path_len, i);
			else
				retval = chef_reversing(adjm, cache, n, m, min, rev_cnt + 1, path_len, i);
			if (retval > m) {
				if (retval == m + 2)
					flag = 1;
				continue;
			}

			if (retval < min)
				min = retval;
			if ((retval - rev_cnt) < cache[node])
				cache[node] = retval - rev_cnt;
		}

		if (min == 0)
			return 0;
	}
	
	if (cache[node] == m + 2 && !flag)
		cache[node]--;

	return min;
}

int main()
{
	uint32 n, m, retval;
	uint8* adjm = NULL;
	uint32* cache = NULL;

	scanf("%u%u", &n, &m);
	
	adjm = create_adj_matrix(n, m);
	if (adjm == NULL) {
		printf ("-1");
		return 0;
	}
	
	cache = malloc(n * sizeof(uint32));
	if (cache == NULL) {
		printf("-1");
		return 0;
	}
	(void *)memset((void *)cache, m + 2, n * sizeof (uint32));
	cache[n-1] = 0;
	
	retval = chef_reversing(adjm, cache, n, m, m + 1, 0, 0, 0);
	if (retval != m + 1)
		printf ("%u", retval);
	else
		printf ("-1");

	delete_adj_matrix(n, m, &adjm);
	free(cache);
	cache = NULL;

	return 0;
}
/*
Input:
7 7
1 2 
3 2
3 4
7 4
6 2
5 6
7 5

Output:
2
*/

