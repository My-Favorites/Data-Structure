#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

/**
 * The function for swapping two integers.
 *
 * @param a The pointer to a variable to be swapped.
 * @param b The pointer to the other variable to be swapped.
 */
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

/**
 * The structure of a list node.
 */
typedef struct _list {
  int value;
  struct _list *p_next;
} list;

/**
 * The structure of a vertex.
 *
 */
typedef struct _vertex {
  int in_degree, out_degree;
  list edges_out;
} vertex;

/**
 * The structure of a heap.
 */
typedef struct _heap {
  int data[MAX_SIZE]; /* The actual data. */
  int map[MAX_SIZE]; /* The map which maps some data to the values to be compared in the heap. */
  int size; /* The size of the heap. */
} heap;
vertex vertices[MAX_SIZE];

list *init_list(list *const p_list);
vertex *init_vertex(vertex *p_vertex);
list *insert_into_list(list *const p_list, int value);
heap *init_heap(heap *const p_heap);
int heap_top(const heap *const p_heap);
heap *heap_pop(heap *const p_heap);
heap *heap_insert(heap *const p_heap, int value);

/**
 * Initialize a linked list.
 *
 * @param p_list The pointer to the list.
 * @return The pointer to the original list.
 */
list *init_list(list *const p_list) {
  p_list->p_next = NULL;
  return p_list;
}

/**
 * Initialize a vertex.
 *
 * @param p_vertex The pointer to the vertex.
 * @return The pointer to the original vertex.
 */
vertex *init_vertex(vertex *p_vertex) {
  p_vertex->in_degree = 0;
  p_vertex->out_degree = 0;
  init_list(&p_vertex->edges_out);
  return p_vertex;
}

/**
 * Insert a value into a linked list.
 *
 * @param p_list The pointer to the list.
 * @param value The value to be inserted.
 * @return The pointer to the original list.
 */
list *insert_into_list(list *const p_list, int value) {
  list *new_list = (list *) malloc(sizeof(list));
  new_list->value = value;
  new_list->p_next = p_list->p_next;
  p_list->p_next = new_list;
  return new_list;
}

/**
 * Initialize a priority queue.
 *
 * @param p_heap The pointer to the heap.
 * @return The pointer to the original heap.
 */
heap *init_heap(heap *const p_heap) {
  p_heap->size = 0;
  return p_heap;
}

/**
 * Get the top element of the priority queue.
 *
 * @param p_heap The pointer to the heap.
 * @return The value of the top element.
 */
int heap_top(const heap *const p_heap) {
  return p_heap->data[0];
}

/**
 * Pop the top element from the priority queue.
 *
 * @param p_heap The pointer to the heap.
 * @return The pointer to the original heap.
 */
heap *heap_pop(heap *const p_heap) {
  p_heap->data[0] = p_heap->data[p_heap->size - 1];
  p_heap->size -= 1;
  int index = 0;
  int left_index = index * 2 + 1;
  int right_index = left_index + 1;
  while (left_index < p_heap->size) {
    if (right_index >= p_heap->size) {
      if (p_heap->map[p_heap->data[index]] > p_heap->map[p_heap->data[left_index]]) {
        swap(p_heap->data + index, p_heap->data + left_index);
      } else {
        break;
      }
      index = left_index;
    } else {
      if (p_heap->map[p_heap->data[right_index]] < p_heap->map[p_heap->data[left_index]]) {
        if (p_heap->map[p_heap->data[index]] > p_heap->map[p_heap->data[right_index]]) {
          swap(p_heap->data + index, p_heap->data + right_index);
          index = right_index;
        } else {
          break;
        }
      } else {
        if (p_heap->map[p_heap->data[index]] > p_heap->map[p_heap->data[left_index]]) {
          swap(p_heap->data + index, p_heap->data + left_index);
          index = left_index;
        } else {
          break;
        }
      }
    }
    left_index = index * 2 + 1;
    right_index = left_index + 1;
  }
  return p_heap;
}

/**
 * Insert an element into the priority queue.
 *
 * @param p_heap The pointer to the heap.
 * @param value The value to be inserted.
 * @return The pointer to the original heap.
 */
heap *heap_insert(heap *const p_heap, int value) {
  p_heap->data[p_heap->size++] = value;
  int index = p_heap->size - 1;
  while (index > 0 && p_heap->map[p_heap->data[index]] < p_heap->map[p_heap->data[(index - 1) >> 1]]) {
    swap(p_heap->data + index, p_heap->data + ((index - 1) >> 1));
    index = (index - 1) >> 1;
  }
  return p_heap;
}

int main(int argc, char *argv[]) {
  int N, i, j;
  heap pqueue;
  heap *p_pqueue = &pqueue;
  init_heap(p_pqueue); /* Initialize the priority queue. */
  scanf("%d", &N);
  /* Uses the standard Kahn algorithm. */
  int number;
  for (i = 0; i < N; ++i) {
    init_vertex(vertices + i);
    scanf("%d", pqueue.map + i);
  }
  for (i = 0; i < N; ++i) { /* Traverse through the input. */
    number = pqueue.map[i];
    /* Build the edges. */
    if (number != -1) { /* If the place is occupied, */
      int place = number % N; /* determine the place the number should be placed at. */
      if (place < i) { /* If the place is before the real one,  */
        for (j = place; j < i; ++j) { /* add an edge from each place between them to the real place. */
          vertices[j].out_degree += 1;
          vertices[i].in_degree += 1;
          insert_into_list(&(vertices[j].edges_out), i);
        }
      } else if (place > i) { /* If the place is after the real one, */
        for (j = place; j < N; ++j) { /* add edges until the end, */
          vertices[j].out_degree += 1;
          vertices[i].in_degree += 1;
          insert_into_list(&(vertices[j].edges_out), i);
        }
        for (j = 0; j < i; ++j) { /* and then from the start to the real one. */
          vertices[j].out_degree += 1;
          vertices[i].in_degree += 1;
          insert_into_list(&(vertices[j].edges_out), i);
        }
      } else { /* If the place is just the actual one, insert it directly into the priority queue of vertices with in degree 0. */
        heap_insert(p_pqueue, i);
      }
    }
  }
  int top;
  list *p_edge;
  int flag = 0; /* The flag which indicates if it is the first element to output or not. */
  /* Traverse through the edges connected to this vertex. */
  while (p_pqueue->size > 0) { /* While there are elements in the priority queue, */
    top = heap_top(p_pqueue); /* get the smallest one. */
    if (flag == 0) { /* If it is the first number printed, */
      printf("%d", p_pqueue->map[top]); /* print with no whitespace. */
      flag = 1;
    } else { /* otherwise place a whitespace before it and print. */
      printf(" %d", p_pqueue->map[top]);
    }
    heap_pop(p_pqueue); /* Pop that element. */
    p_edge = &vertices[top].edges_out;
    /* Traverse through the edges connected to this vertex. */
    for (i = 0; i < vertices[top].out_degree; ++i) {
      p_edge = p_edge->p_next;
      /* Check if the vertices are ready to go out (has in degree 0). */
      vertices[p_edge->value].in_degree -= 1;
      if (vertices[p_edge->value].in_degree == 0) {
        heap_insert(p_pqueue, p_edge->value); /* If so, push it into the priority queue. */
      }
    }
  }
  return 0;
}