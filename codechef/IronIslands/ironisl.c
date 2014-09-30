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

#define MAX_N 10000
struct info {
	uint32 nodes[MAX_N];
	uint32 que[MAX_N];
	int head, tail;
	uint32 edges[MAX_N][MAX_N];
	uint32 n;
	uint32 flag;
};
typedef struct info info_t;
typedef struct info* infoptr_t;

infoptr_t graph_detach(infoptr_t info)
{
	if (!info)
		return NULL;

	free (info);
	return NULL;
}

/* Given N and M as input (N number of vetrices and M edges),
 * this function creates adjacency matrix by reading M (a, b) pairs
 * from stdin.
 */
void graph_attach(infoptr_t info)
{
	int i,j;
	char string[MAX_N];
	
	scanf("%u", &info->n);
	
	for (i = 0; i < info->n; i++) {
		scanf("%s", string);
		for (j = 0; j < info->n; j++) {
			if (string[j] == '0')
				info->edges[i][j] = 0;
			else
				info->edges[i][j] = 1;
		}
	}
}

void enque(infoptr_t info, uint32 n)
{
	if ((info->head + 1) % MAX_N == info->tail)
		return;

	info->que[info->head] = n;
	info->head = (info->head + 1) % MAX_N;
}

uint32 deque(infoptr_t info)
{
	if (info->head == info->tail)
		return MAX_N;
	
	info->tail = (info->tail + 1) % MAX_N;
	return info->que[info->tail];
}

void process_phase(infoptr_t info)
{
	uint32 v, m, a, b;

	uint32 node, i;
	uint32 len[MAX_N], len_sum;

	scanf("%u %u", &v, &m);
	v--;

	while (m-- > 0) {
		scanf("%u %u", &a, &b);
		if (info->edges[a - 1][b - 1] == 0)
			info->edges[a - 1][b - 1] = 1;
		else
			info->edges[a - 1][b - 1] = 0;
	}

	info->head = info->tail = 0;
	node = v;
	len_sum = 0;

	len[node] = 0;
	info->nodes[node] = info->flag;
/*	for( i = 0 ; i < info->n; i++) {
		for( j = 0 ; j < info->n; j++)
			printf ("%u\t", info->edges[i][j]);
		printf("\n");
	}*/
	while (node != MAX_N) {

		for (i = 0; i < info->n; i++) {
			if (info->nodes[i] != info->flag && info->edges[node][i] == 1) {
				info->nodes[i] = info->flag;
				len[i] = len[node] + 1;
				len_sum += len[i];
				enque(info, i);
//				printf("i %u : len %u : sum %u\n", i, len[i], len_sum);
			}
		}
		node = deque(info);
	}
	printf("%u\n", len_sum);
}

int main()
{
	uint32 t, q, i;
	infoptr_t info = NULL;
	
	info = malloc(sizeof(info_t));
	if (!info)
		return 0;

	for ( i = 0; i < MAX_N; i++)
		info->nodes[i] = i;

	scanf("%u", &t);
	while (t-- > 0) {
		graph_attach(info);
		memset((void *)info->nodes, 0, info->n * sizeof (uint32));
		scanf ("%u", &q);
		while (q-- > 0) {
			info->flag = q + 1;
			process_phase(info);
		}
	}

	info = graph_detach(info);
	return 0;
}
