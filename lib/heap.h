/* Generic Heap implementation as array
 */

/* Change this typedef to type of value based on
 * which, the heap is build
 */
typedef uint32 heapval_t;

#define HEAP_TYPE_MIN 0
#define HEAP_TYPE_MAX 1

/* API's exported by heap module

/* Attach a heap by using heap_attach API.
 * Takes maximum size of heap and type as argument.
 * For Min Heap : Type = HEAP_TYPE_MIN
 * For Max Heap : Type = HEAP_TYPE_MAX
 * Returns the handle for the heap on sucess.
 * Returns NULL on failure.
 * Multiple heap instances could be created
 */
extern void* heap_attach(uint32 max_len, uint8 type);

/* Detach a heap by using heap_detach API
 * after you are done with heap.
 * Takes heap handle as argument.
 * Returns NULL.
 */
extern void* heap_detach(void* handle);

/* Insert an element into the heap.
 * Takes heap handle, pointer to a payload and a
 * value of type heapval_t as arguments.
 * Heap is build based on heapval_t value.
 * Returns 0 on sucess, 1 on failure.
 */
extern int heap_insert(void* handle, void* data, heapval_t val);

/* Delete the root of the heap.
 * Root will be the min of all elements for Min heap and 
 * max of all elements for Max heap.
 * Returns the pointer to payload of the root.
 * Retuns NULL on underflow.
 */
extern void* heap_delroot(void* handle);

/* Returns the root of the heap.
 * The root is not removed from the heap.
 * Returns NULL on underflow.
 */
extern void* heap_getroot(void* handle);

/* Upadte the value of particular node.
 * Takes heap handle, pointer to payload and new value.
 * Returns 0 on sucesss full upadtion. Otherwise returns 1.
 * The caller must take care to update the new value inside
 * payload (if value is stored inside payload). This routine
 * will not update value inside payload
 */
extern int heap_updateval(void* handle, void* data, heapval_t newval);
