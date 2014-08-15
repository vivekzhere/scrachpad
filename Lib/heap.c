/* Generic Heap implementation as array.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "types_x86_64.h"
#include "heap.h"

struct heapnode {
	void* data;
	heapval_t val;
};
typedef struct heapnode node_t;
typedef struct heapnode* nodeptr_t;

struct heapinfo {
	nodeptr_t heap;
	uint32 maxsize;
	uint32 size;
	uint8 type; // 0 - min heap, 1 - max heap
};
typedef struct heapinfo info_t;
typedef struct heapinfo* infoptr_t;

#define LEFT(i) (((i) << 1) + 1)
#define RIGHT(i) (((i) + 1) << 1)
#define PARENT(i) (((i) - 1) >> 1)

#define COND(info, a, b)( \
		((info)->type == HEAP_TYPE_MAX) ? \
		((info)->heap[(a)].val > (info)->heap[(b)].val): \
		((info)->heap[(a)].val < (info)->heap[(b)].val) \
		)

/* Attach a heap by using heap_attach API.
 * Takes maximum size of heap and type as argument.
 * For Min Heap : Type = HEAP_TYPE_MIN
 * For Max Heap : Type = HEAP_TYPE_MAX
 * Returns the handle for the heap on sucess.
 * Returns NULL on failure.
 * Multiple heap instances could be created
 */
void* heap_attach(uint32 max_len, uint8 type)
{
	infoptr_t info = NULL;
	
	info = malloc(sizeof (info_t));
	if (!info) {
		return NULL;
	}
	(void *)memset((void *)info, 0, sizeof (info_t));

	info->heap = malloc(max_len * sizeof (node_t));
	if (!info->heap) {
		info = (infoptr_t)heap_detach(info);
		return NULL;
	}
	(void *)memset((void *)info->heap, 0, max_len * sizeof (node_t));

	info->maxsize = max_len;
	info->size = 0;
	info->type = type;

	return info;
}

/* Detach a heap by using heap_detach API
 * after you are done with heap.
 * Takes heap handle as argument.
 * Returns NULL.
 */
void* heap_detach(void* handle)
{
	infoptr_t info = (infoptr_t) handle;

	if (!info)
		return NULL;

	if (info->heap) {
		free(info->heap);
		info->heap = NULL;
	}

	free(info);
	return NULL;
}

/* HEAPIFY is an important subroutine for manipulating heaps.
 * Its inputs are Heap_info for the heap and an index i into the array.
 * When HEAPIFY is called, it is assumed that the binary trees rooted at
 * LEFT(i) and RIGHT(i) are heaps, but that the element at ith postion
 * may violate the heap condition with respect to its children.
 * The function of HEAPIFY is to let the value at ith postition "float down"
 * in the heap so that the subtree rooted at index i becomes a heap.
 */
void heapify(infoptr_t info, uint32 i)
{
	uint32 left, right, newi = i;
	node_t temp;

	if (i >= info->size)
		return;

	left = LEFT(i);
	right = RIGHT(i);

	if (left < info->size && COND(info, left, i))
		newi = left;
	if (right < info->size && COND(info, right, i))
		newi = right;

	if (i != newi) {
		temp = info->heap[i];
		info->heap[i] = info->heap[newi];
		info->heap[newi] = temp;
		heapify(info, newi);
	}
}

/* Insert an element into the heap.
 * Takes heap handle, pointer to a payload and a
 * value of type heapval_t as arguments.
 * Heap is build based on heapval_t value.
 * Returns 0 on sucess, 1 on failure.
 */
int heap_insert(void* handle, void* data, heapval_t val)
{
	infoptr_t info = (infoptr_t) handle;
	uint32 i, parent;
	node_t temp;

	if (!info)
		return 1;
	
	if (info->size >= info->maxsize)
		return 1;

	i = info->size;
	info->size++;
	info->heap[i].data = data;
	info->heap[i].val = val;

	parent = PARENT(i);
	while (i > 0 && COND(info, i, parent)) {
		temp = info->heap[i];
		info->heap[i] = info->heap[parent];
		info->heap[parent] = temp;

		i = parent;
		parent = PARENT(i);
	}
	return 0;
}

/* Delete the root of the heap.
 * Root will be the min of all elements for Min heap and 
 * max of all elements for Max heap.
 * Returns the pointer to payload of the root.
 * Retuns NULL on underflow.
 */
void* heap_delroot(void* handle)
{
	infoptr_t info = (infoptr_t) handle;
	void* base;

	if (!info)
		return NULL;
	
	if (info->size < 1)
		return NULL;

	base = info->heap[0].data;
	info->size--;
	info->heap[0] = info->heap[info->size];
	heapify(info, 0);
	return base;
}

/* Returns the root of the heap.
 * The root is not removed from the heap.
 * Returns NULL on underflow.
 */
void* heap_getroot(void* handle)
{
	infoptr_t info = (infoptr_t) handle;
	void* base;

	if (!info)
		return NULL;
	
	if (info->size < 1)
		return NULL;

	return info->heap[0].data;
}

