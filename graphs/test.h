
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct MinHeapNode
{
    int  v;
    int dist;
} MinHeapNode;
 
// Structure to represent a min heap
typedef struct MinHeap
{
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
     MinHeapNode **array;
} MinHeap;