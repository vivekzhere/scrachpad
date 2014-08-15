#include<stdio.h>
#include<stdlib.h>

#include "types_x86_64.h"
#include "heap.h"

int main()
{
	void *heap =NULL;
	void *heap2 =NULL;
	uint32 array[] = {3, 7, 5, 4, 1, 8, 0, 6, 2, 9};
	int i;
	
	printf("\nMAX HEAP\n");
	heap = heap_attach(10, HEAP_TYPE_MAX);
	if (!heap) {
		printf("Heap attach failed\n");
		return 0;
	}
	
	for (i = 0; i< 10; i++) {
		if (heap_insert(heap, &array[i], array[i])) {
			printf("Insert %d th element failed\n", i);
			break;
		}
		printf("Inserted : %d \tCurrent MAX : %d\n\n", array[i], *(uint32*)heap_getroot(heap));
		
		if (i == 2) {
			printf("Deleted : %d \tCurrent MAX : ", *(uint32*)heap_delroot(heap));
			printf("%d\n\n", *(uint32*)heap_getroot(heap));
	
		}
	}

	printf("\nMIN HEAP\n");
	heap2 = heap_attach(10, HEAP_TYPE_MIN);
	if (!heap2) {
		printf("Heap attach failed\n");
		return 0;
	}
	
	for (i = 0; i< 10; i++) {
		if (heap_insert(heap2, &array[i], array[i])) {
			printf("Insert %d th element failed\n", i);
			break;
		}
		printf("Inserted : %d \tCurrent min : %d\n\n", array[i], *(uint32*)heap_getroot(heap2));
		
		if (i == 2) {
			printf("Deleted : %d \tCurrent min : ", *(uint32*)heap_delroot(heap2));
			printf("%d\n\n", *(uint32*)heap_getroot(heap2));
	
		}
	}
	
	heap = heap_detach(heap);
	heap2 = heap_detach(heap2);
	return 0;
}
