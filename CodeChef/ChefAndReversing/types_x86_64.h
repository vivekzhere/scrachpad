typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned int uint32;
typedef signed int int32;
typedef unsigned long long uint64;
typedef signed long long int64;

static inline void print_types()
{
	int i;
	i = sizeof(uint8);
	printf ("Size of uint8 : %d\n", i);

	i = sizeof(int8);
	printf ("Size of int8 : %d\n", i);

	i = sizeof(uint16);
	printf ("Size of uint16 : %d\n", i);

	i = sizeof(int16);
	printf ("Size of int16 : %d\n", i);

	i = sizeof(uint32);
	printf ("Size of uint32 : %d\n", i);

	i = sizeof(int32);
	printf ("Size of int32 : %d\n", i);

	i = sizeof(uint64);
	printf ("Size of uint64 : %d\n", i);

	i = sizeof(int64);
	printf ("Size of int64 : %d\n", i);
}
