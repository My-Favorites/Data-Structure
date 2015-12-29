#include <stdio.h>

#define MAX_SIZE 1000

typedef struct _heap {
  int data[MAX_SIZE];
  int size;
} heap;

heap* init_heap(heap* const p_heap) {
  p_heap->size = 0;

  return p_heap;
}

int heap_top(const heap* const p_heap) {
  return p_heap->data[0];
}

heap* heap_pop(heap* const p_heap) {
  return p_heap;
}

heap* heap_insert(heap* const p_heap, int value) {
  p_heap->data[p_heap->size++] = value;
  int index = p_heap->size - 1;
  int temp;
  while (p_heap->data[index] > p_heap->data[index >> 1]) {
    temp = p_heap->data[index];
    p_heap->data[index] = p_heap->data[index >> 1];
    p_heap->data[index >> 1] = temp;

    index = index >> 1;
  }

  return p_heap;
}

void print_heap(const heap* const p_heap) {
  int limit = 1;
  int count = 0;
  for (int i = 0; i < p_heap->size; ++i) {
    printf("%d,", p_heap->data[i]);
    count++;
    if (count == limit) {
      limit *= 2;
      count = 0;
      printf("\n");
    }
  }
}

int main(int argc, char *argv[]) {

  int N, i;
  int table[1000];

  int pqueue[1000];

  scanf("%d", &N);

  heap my_heap;
  heap* p_my_heap = &my_heap;
  init_heap(p_my_heap);


  for (i = 0; i < N; ++i) {
    scanf("%d", table + i);
    heap_insert(p_my_heap, table[i]);
  }

  printf("The top of the heap is %d.\n", heap_top(p_my_heap));
  print_heap(p_my_heap);

  /**
   * Uses the standard Kahn algorithm.
   */


//  printf("%d");

  return 0;
}