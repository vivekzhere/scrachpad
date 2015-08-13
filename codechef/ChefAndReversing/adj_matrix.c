#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "types_x86_64.h"

struct node {
	uint32 i, j;
	struct node *right;
	struct node *down;
};
typedef struct node node_t;
typedef struct node* nodeptr_t;

struct root {
	nodeptr_t* left_base;
	nodeptr_t* top_base;
	nodeptr_t chunk;
};
typedef struct root root_t;
typedef struct root* rootptr_t;

void delete_adj_matrix(uint32 n, uint32 m, rootptr_t* rootptr)
{
	if(!(rootptr && *rootptr))
		return;

	if((*rootptr)->chunk) {
		free((*rootptr)->chunk);
		(*rootptr)->chunk = NULL;
	}

	if((*rootptr)->left_base) {
		free((*rootptr)->left_base);
		(*rootptr)->left_base = NULL;
	}

	if((*rootptr)->top_base) {
		free((*rootptr)->top_base);
		(*rootptr)->top_base = NULL;
	}

	free(*rootptr);
	*rootptr = NULL;

}

/* Given N and M as input (N number of vetrices and M edges),
 * this function creates adjacency matrix by reading M (a, b) pairs
 * from stdin.
 */
rootptr_t create_adj_matrix(uint32 n, uint32 m)
{
	rootptr_t root = NULL;
	uint32 i, a, b;
	nodeptr_t temp = NULL;

	root = malloc(sizeof(root_t));
	if (!root) {
		return NULL;
	}
	(void *)memset((void *)root, 0, sizeof (root_t));

	root->top_base = malloc (n * sizeof (nodeptr_t));
	if (!root->top_base) {
		delete_adj_matrix(n, m, &root);
		return NULL;
	}
	(void *)memset((void *)root->top_base, 0, n * sizeof (nodeptr_t));

	root->left_base = malloc (n * sizeof (nodeptr_t));
	if (!root->left_base) {
		delete_adj_matrix(n, m, &root);
		return NULL;
	}
	(void *)memset((void *)root->left_base, 0, n * sizeof (nodeptr_t));

	root->chunk = malloc (m * sizeof (node_t));
	if (!root->chunk) {
		delete_adj_matrix(n, m, &root);
		return NULL;
	}
	(void *)memset((void *)root->chunk, 0, m * sizeof (node_t));

	for (i = 0; i < m; i++) {
		scanf("%u %u", &a, &b);
		if (a != b) {
			root->chunk[i].i = a - 1;
			root->chunk[i].j = b - 1;
			root->chunk[i].right = root->left_base[a - 1];
			root->left_base[a - 1] = &root->chunk[i];	
			root->chunk[i].down = root->top_base[b - 1];
			root->top_base[b - 1] = &root->chunk[i];	
		}
	}
	return root;
}

uint32 chef_reversing(rootptr_t root, uint32* cache, uint32 n, uint32 m, uint32 min, uint32 rev_cnt, uint32 path_len, uint32 node)
{
	uint32 retval, flag = 0;
	nodeptr_t i;
	
	if (path_len >= n)
		return m + 1;

	if (cache[node] <= m)
		return rev_cnt + cache[node];
	else if (cache[node] == m + 1)
		return m + 1;
	else if (rev_cnt > min)
		return m + 2;

	path_len++;

	i = root->left_base[node];
	while (i) {
		retval = chef_reversing(root, cache, n, m, min, rev_cnt, path_len, i->j);
		if (retval > m) {
			if (retval == m + 2)
				flag = 1;
			i = i->right;
			continue;
		}

		if (retval < min)
			min = retval;
		if ((retval - rev_cnt) < cache[node])
			cache[node] = retval - rev_cnt;
		
		if (min == 0)
			return 0;
		
		i = i->right;
	}
	
	i = root->top_base[node];
	while (i) {
		retval = chef_reversing(root, cache, n, m, min, rev_cnt + 1, path_len, i->i);
		if (retval > m) {
			if (retval == m + 2)
				flag = 1;
			i = i->down;
			continue;
		}

		if (retval < min)
			min = retval;
		if ((retval - rev_cnt) < cache[node])
			cache[node] = retval - rev_cnt;
		
		if (min == 0)
			return 0;
		
		i = i->down;
	}
	
	if (cache[node] == m + 2 && !flag)
		cache[node]--;

	return min;
}

int main()
{
	uint32 n, m, retval;
	rootptr_t root = NULL;
	uint32* cache = NULL;

	scanf("%u %u", &n, &m);
	
	root = create_adj_matrix(n, m);
	if (root == NULL) {
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
	
	retval = chef_reversing(root, cache, n, m, m + 1, 0, 0, 0);
	if (retval != m + 1)
		printf ("%u", retval);
	else
		printf ("-1");

	delete_adj_matrix(n, m, &root);
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

