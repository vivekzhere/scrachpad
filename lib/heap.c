/* Generic Heap implementation as array.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "types_x86_64.h"
#include "heap.h"

struct heap_node {
	void* data;
	heapval_t val;
};
typedef struct heap_node heap_node_t;
typedef struct heap_node* heap_nodeptr_t;

struct heap_info {
	heap_nodeptr_t heap;
	uint32 maxsize;
	uint32 size;
	uint8 type; // 0 - min heap, 1 - max heap
};
typedef struct heap_info heap_info_t;
typedef struct heap_info* heap_infoptr_t;

#define LEFT(i) (((i) << 1) + 1)
#define RIGHT(i) (((i) + 1) << 1)
#define PARENT(i) (((i) - 1) >> 1)

#define COND(info, a, b)( \
		((info)->type == HEAP_TYPE_MAX) ? \
		((info)->heap[(a)].val > (info)->heap[(b)].val): \
		((info)->heap[(a)].val < (info)->heap[(b)].val) \
		)

/* Detach a heap by using heap_detach API
 * after you are done with heap.
 * Takes heap handle as argument.
 * Returns NULL.
 */
void* heap_detach(void* handle)
{
	heap_infoptr_t info = (heap_infoptr_t) handle;

	if (!info)
		return NULL;

	if (info->heap) {
		free(info->heap);
		info->heap = NULL;
	}

	free(info);
	return NULL;
}

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
	heap_infoptr_t info = NULL;
	
	info = malloc(sizeof (heap_info_t));
	if (!info) {
		return NULL;
	}
	(void *)memset((void *)info, 0, sizeof (heap_info_t));

	info->heap = malloc(max_len * sizeof (heap_node_t));
	if (!info->heap) {
		info = (heap_infoptr_t)heap_detach(info);
		return NULL;
	}
	(void *)memset((void *)info->heap, 0, max_len * sizeof (heap_node_t));

	info->maxsize = max_len;
	info->size = 0;
	info->type = type;

	return info;
}

/* Reset the heap as empty.
 * Will not free the memory allocated.
 * Heap can be re used after reset
 * Returns 0 on sucess, 1 on failure.
 */
int heap_reset(void* handle)
{
	heap_infoptr_t info = (heap_infoptr_t) handle;

	if (!info)
		return 1;
	
	info->size = 0;
	return 0;
}

/* HEAPIFY is an important subroutine for manipulating heaps.
 * Its inputs are Heap_info for the heap and an index i into the array.
 * When HEAPIFY is called, it is assumed that the binary trees rooted at
 * LEFT(i) and RIGHT(i) are heaps, but that the element at ith postion
 * may violate the heap condition with respect to its children.
 * The function of HEAPIFY is to let the value at ith postition "float down"
 * in the heap so that the subtree rooted at index i becomes a heap.
 */
void heapify(heap_infoptr_t info, uint32 i)
{
	uint32 left, right, newi = i;
	heap_node_t temp;

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
	heap_infoptr_t info = (heap_infoptr_t) handle;
	uint32 i, parent;
	heap_node_t temp;

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
	heap_infoptr_t info = (heap_infoptr_t) handle;
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
	heap_infoptr_t info = (heap_infoptr_t) handle;
	void* base;

	if (!info)
		return NULL;
	
	if (info->size < 1)
		return NULL;

	return info->heap[0].data;
}

/* Upadte the value of particular node.
 * Takes heap handle, pointer to payload and new value.
 * Returns 0 on sucesss full upadtion. Otherwise returns 1.
 * The caller must take care to update the new value inside
 * payload (if value is stored inside payload). This routine
 * will not update value inside payload
 */
int heap_updateval(void* handle, void* data, heapval_t newval)
{
	uint32 i, parent;
	heap_infoptr_t info = (heap_infoptr_t) handle;
	heap_node_t temp;

	if (!info)
		return 1;

	for (i = 0; i < info->size; i++) {
		if (data == info->heap[i].data)
			break;
	}

	if (i == info->size)
		return 1;

	if (info->heap[i].val == newval)
		return 0;

	if ((info->heap[i].val > newval && info->type == HEAP_TYPE_MIN) ||
			(info->heap[i].val < newval && info->type == HEAP_TYPE_MAX)) {
		info->heap[i].val = newval;
		
		parent = PARENT(i);
		while (i > 0 && COND(info, i, parent)) {
			temp = info->heap[i];
			info->heap[i] = info->heap[parent];
			info->heap[parent] = temp;

			i = parent;
			parent = PARENT(i);
		}
	} else {
		info->heap[i].val = newval;
		heapify(info, i);
	}

	return 0;
}
