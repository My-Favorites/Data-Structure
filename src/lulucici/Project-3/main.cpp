#include <cstdio>
#include <queue>
#include <list>
#define MAX_SIZE 2000
using namespace std;
int map[MAX_SIZE];

int N, i, j;
class Compare {
 public:
  bool operator() (int a, int b) {
    return map[a] > map[b];
  }
};
typedef struct _vertex {
  int in_degree, out_degree;
  vector<int> edges_out;
} vertex;
vertex vertices[MAX_SIZE];
vertex *init_vertex(vertex *p_vertex) {
  p_vertex->in_degree = 0;
  p_vertex->out_degree = 0;
  return p_vertex;
}
int main(int argc, char *argv[]) {
  scanf("%d", &N);
  int number;
  for (i = 0; i < N; ++i) {
    init_vertex(vertices + i);
    scanf("%d", map + i);
  }
  priority_queue<int, vector<int>, Compare> pqueue;
  int count = 0;
  for (i = 0; i < N; ++i) {
    number = map[i];
    if (number != -1) {
      count++;
      int place = number % N;
      if (place < i) {
        for (j = place; j < i; ++j) {
          vertices[j].out_degree += 1;
          vertices[i].in_degree += 1;
          vertices[j].edges_out.push_back(i);
        }
      } else if (place > i) {
        for (j = place; j < N; ++j) {
          vertices[j].out_degree += 1;
          vertices[i].in_degree += 1;
          vertices[j].edges_out.push_back(i);
        }
        for (j = 0; j < i; ++j) {
          vertices[j].out_degree += 1;
          vertices[i].in_degree += 1;
          vertices[j].edges_out.push_back(i);
        }
      } else {
        pqueue.push(i);
      }
    }
  }
  int top;
  int flag = 1;
  while (pqueue.size() > 0) {
//    count -= 1;
    top = pqueue.top();
    if (flag == 1) {
      printf("%d", map[top]);
//      break;
      flag = 0;
    } else {
      printf(" %d", map[top]);
    }
    pqueue.pop();
    for (vector<int>::iterator it = vertices[top].edges_out.begin(); it != vertices[top].edges_out.end(); ++it) {
      vertices[*it].in_degree -= 1;
      if (vertices[*it].in_degree == 0) {
        pqueue.push(*it);
      }
    }
  }
  return 0;
}