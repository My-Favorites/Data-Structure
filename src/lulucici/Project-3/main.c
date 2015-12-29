#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

typedef struct _list {
  int value;
  struct _list *p_next;
} list;

typedef struct _vertex {
  int in_degree, out_degree;
  list edges_out;
} vertex;

typedef struct _heap {
  int data[MAX_SIZE];
  int map[MAX_SIZE];
  int size;
} heap;
vertex vertices[MAX_SIZE];
void print_heap(const heap *const p_heap);

list *init_list(list *const p_list) {
  p_list->p_next = NULL;
  return p_list;
}

vertex *init_vertex(vertex *p_vertex) {
  p_vertex->in_degree = 0;
  p_vertex->out_degree = 0;
  init_list(&p_vertex->edges_out);
  return p_vertex;
}

list *insert_into_list(list *const p_list, int value) {
  list *new_list = (list *) malloc(sizeof(list));
  new_list->value = value;
  new_list->p_next = p_list->p_next;
  p_list->p_next = new_list;
  return new_list;
}

heap *init_heap(heap *const p_heap) {
  p_heap->size = 0;

  return p_heap;
}

int heap_top(const heap *const p_heap) {
  return p_heap->data[0];
}

heap *heap_pop(heap *const p_heap) {
//  print_heap(p_heap);
//  printf("Top is %d, size is %d\n", p_heap->data[p_heap->size - 1], p_heap->size);
  p_heap->data[0] = p_heap->data[p_heap->size - 1];
  p_heap->size -= 1;
//  print_heap(p_heap);
  int index = 0;
  int left_index = index * 2 + 1;
  int right_index = left_index + 1;
  while (left_index < p_heap->size) {
    if (right_index >= p_heap->size) {
      if (p_heap->map[p_heap->data[index]] > p_heap->map[p_heap->data[left_index]]) {
//        printf("case 1, %d, %d\n", index, left_index);
        swap(p_heap->data + index, p_heap->data + left_index);
//        print_heap(p_heap);
      } else {
        break;
      }
      index = left_index;
    } else {
      if (p_heap->map[p_heap->data[right_index]] < p_heap->map[p_heap->data[left_index]]) {
        if (p_heap->map[p_heap->data[index]] > p_heap->map[p_heap->data[right_index]]) {
//          printf("case 2, %d, %d\n", index, right_index);
          swap(p_heap->data + index, p_heap->data + right_index);
//          print_heap(p_heap);
          index = right_index;
        } else {
          break;
        }
      } else {
        if (p_heap->map[p_heap->data[index]] > p_heap->map[p_heap->data[left_index]]) {
//          printf("case 3, %d, %d\n", index, left_index);
          swap(p_heap->data + index, p_heap->data + left_index);
//          print_heap(p_heap);
          index = left_index;
        } else {
          break;
        }
      }
    }
    left_index = index * 2 + 1;
    right_index = left_index + 1;
  }
//  print_heap(p_heap);
  return p_heap;
}

heap *heap_insert(heap *const p_heap, int value) {
  p_heap->data[p_heap->size++] = value;
  int index = p_heap->size - 1;
  while (index > 0 && p_heap->map[p_heap->data[index]] < p_heap->map[p_heap->data[(index - 1) >> 1]]) {
    swap(p_heap->data + index, p_heap->data + ((index - 1) >> 1));
    index = (index - 1) >> 1;
  }
  return p_heap;
}

void print_heap(const heap *const p_heap) {
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
  printf("\n");
}

int main(int argc, char *argv[]) {
  int N, i, j;

  heap pqueue;
  heap *p_pqueue = &pqueue;
  init_heap(p_pqueue);
  scanf("%d", &N);
  heap my_heap;
  heap *p_my_heap = &my_heap;
  init_heap(p_my_heap);
  /**
   * Uses the standard Kahn algorithm.
   */
  int number;
  for (i = 0; i < N; ++i) {
    init_vertex(vertices + i);
    scanf("%d", pqueue.map + i);
  }
  for (i = 0; i < N; ++i) {
    number = pqueue.map[i];
    /**
     * Build the edges.
     */
    if (number != -1) {
      int place = number % N;
      if (place < i) {
        for (j = place; j < i; ++j) {
          vertices[j].out_degree += 1;
          vertices[i].in_degree += 1;
          insert_into_list(&(vertices[j].edges_out), i);
        }
      } else if (place > i) {
        for (j = place; j < N; ++j) {
          vertices[j].out_degree += 1;
          vertices[i].in_degree += 1;
          insert_into_list(&(vertices[j].edges_out), i);
        }
        for (j = 0; j < i; ++j) {
          vertices[j].out_degree += 1;
          vertices[i].in_degree += 1;
          insert_into_list(&(vertices[j].edges_out), i);
        }
      } else {
        heap_insert(p_pqueue, i);
      }
    }
  }
  int top;
  list *p_edge;
  int flag = 0;
  while (p_pqueue->size > 0) {
    top = heap_top(p_pqueue);
    if (flag == 0) {
      printf("%d", p_pqueue->map[top]);
      flag = 1;
    } else {
      printf("%d ", p_pqueue->map[top]);
    }
    heap_pop(p_pqueue);
    p_edge = &vertices[top].edges_out;
    /**
     * Traverse through the edges connected to this vertex.
     */
    for (i = 0; i < vertices[top].out_degree; ++i) {
      p_edge = p_edge->p_next;
      /**
       * Check if the vertices are ready to go out.
       */
      vertices[p_edge->value].in_degree -= 1;
//      printf("Indegree of %d is %d\n", p_edge->value, vertices[p_edge->value].in_degree);
      if (vertices[p_edge->value].in_degree == 0) {
//        printf("insert %d\n", p_edge->value);
        heap_insert(p_pqueue, p_edge->value);
      }
    }
  }
  return 0;
}