#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "/home/vivekana/Code/scrachpad/lib/types_x86_64.h"
#include "/home/vivekana/Code/scrachpad/lib/heap.h"

struct edge {
	uint32 i, j;
	struct edge *to_next;
	struct edge *from_next;
};
typedef struct edge edge_t;
typedef struct edge* edgeptr_t;

struct vertex {
	uint32 id;
	edgeptr_t edge_to;
	edgeptr_t edge_from;
	uint32 rev_cnt;
	uint8 flag;
};
typedef struct vertex vertex_t;
typedef struct vertex* vertexptr_t;

struct info {
	vertexptr_t vertex;
	edgeptr_t edge;
	void *heap;
	uint32 n, m;
};
typedef struct info info_t;
typedef struct info* infoptr_t;

infoptr_t graph_detach(infoptr_t info)
{
	if (!info)
		return NULL;

	if (info->heap)
		info->heap = heap_detach(info->heap);

	if (info->edge) {
		free (info->edge);
		info->edge = NULL;
	}

	if (info->vertex) {
		free (info->vertex);
		info->vertex = NULL;
	}

	free (info);
	return NULL;
}

/* Given N and M as input (N number of vetrices and M edges),
 * this function creates adjacency matrix by reading M (a, b) pairs
 * from stdin.
 */
infoptr_t graph_attach(uint32 n, uint32 m)
{
	infoptr_t info = NULL;
	uint32 a, b, i;
	
	info = malloc(sizeof(info_t));
	if (!info)
		return NULL;
	(void *)memset((void *)info, 0, sizeof (info_t));

	info->n = n;
	info->m = m;
	
	info->vertex = malloc (n * sizeof (vertex_t));
	if (!info->vertex)
		goto fail;
	(void *)memset((void *)info->vertex, 0, n * sizeof (vertex_t));
	for (i = 0; i < n; i++) {
		info->vertex[i].id = i;
	}

	info->edge = malloc (m * sizeof (edge_t));
	if (!info->edge)
		goto fail;
	(void *)memset((void *)info->edge, 0, m * sizeof (edge_t));

	info->heap = heap_attach(n, HEAP_TYPE_MIN);
	if (!info->heap)
		goto fail;

	for (i = 0; i < m; i++) {
		scanf("%u %u", &a, &b);
		if (a != b) {
			info->edge[i].i = a - 1;
			info->edge[i].j = b - 1;

			info->edge[i].from_next = info->vertex[a - 1].edge_from;
			info->vertex[a - 1].edge_from = &info->edge[i];
			
			info->edge[i].to_next = info->vertex[b - 1].edge_to;
			info->vertex[b - 1].edge_to = &info->edge[i];
		}
	}
	return info;
fail:
	return graph_detach (info);
}

uint32 chef_reversing(infoptr_t info)
{
	vertexptr_t vertex, vertex_next;
	edgeptr_t edge;
	
	if (!(info && info->vertex && info->edge && info->heap))
		return -1;

	vertex = info->vertex;
	vertex->flag = 1;

	while (vertex) {
		if (vertex->id == info->n - 1)
			return vertex->rev_cnt;

		edge = vertex->edge_from;
		while (edge) {
			vertex_next = &info->vertex[edge->j];
			
			if (vertex_next->flag && vertex_next->rev_cnt > vertex->rev_cnt) {
				
				vertex_next->rev_cnt = vertex->rev_cnt;
				heap_updateval(info->heap, vertex_next, vertex_next->rev_cnt);

			} else if (!vertex_next->flag) {
				vertex_next->flag = 1;
				vertex_next->rev_cnt = vertex->rev_cnt;

				if (heap_insert (info->heap, vertex_next, vertex_next->rev_cnt))
					return info->m + 1;
			}
			edge = edge->from_next;
		}
		
		edge = vertex->edge_to;
		while (edge) {
			vertex_next = &info->vertex[edge->i];
			
			if (vertex_next->flag && vertex_next->rev_cnt > vertex->rev_cnt + 1) {
				
				vertex_next->rev_cnt = vertex->rev_cnt + 1;
				heap_updateval(info->heap, vertex_next, vertex_next->rev_cnt);
			
			} else if (!vertex_next->flag) {
				vertex_next->flag = 1;
				vertex_next->rev_cnt = vertex->rev_cnt + 1;

				if (heap_insert (info->heap, vertex_next, vertex_next->rev_cnt))
					return info->m + 1;
			}	
			edge = edge->to_next;
		}

		vertex = (vertexptr_t)heap_delroot(info->heap);
	}
	
	return info->m + 1;
}

int main()
{
	uint32 n, m, retval;
	infoptr_t info = NULL;

	scanf("%u %u", &n, &m);
	
	info = graph_attach(n, m);
	if (info == NULL) {
		printf ("-1");
		goto fail;
	}
	
	retval = chef_reversing(info);
	if (retval > m)
		printf ("-1");
	else
		printf ("%u", retval);

fail:
	info = graph_detach(info);
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

