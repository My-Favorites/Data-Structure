#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define INFINITY 1000000
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */
typedef int WeightType;

typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph ReadG(); /* details omitted */

void ShortestDist( MGraph Graph, int dist[], int count[], Vertex S );

int main()
{
    int dist[MaxVertexNum], count[MaxVertexNum];
    Vertex S, V;
    MGraph G = ReadG();

    scanf("%d", &S);
    ShortestDist( G, dist, count, S );

    for ( V=0; V<G->Nv; V++ )
        printf("%d ", dist[V]);
    printf("\n");
    for ( V=0; V<G->Nv; V++ )
        printf("%d ", count[V]);
    printf("\n");

    return 0;
}

/* Your function will be put here */
MGraph
ReadG()
{
    MGraph mg = malloc(sizeof(*mg));
    int i, x, y;
    scanf("%d%d", &mg->Nv, &mg->Ne);
    for (i = 0; i < mg->Ne; i++) {
        scanf("%d%d", &x, &y);
        scanf("%d", &mg->G[x][y]);
    }
    return mg;
} /* details omitted */


void
ShortestDist(MGraph Graph, int dist[], int count[], Vertex S)
{
    Vertex *queue = malloc(sizeof(*queue) * Graph->Nv);
    bool *vi = malloc(sizeof(*vi) * Graph->Nv);
    int head = 0, tail = 1;
    Vertex u, v;
    int p;
    for (v = 0; v < Graph->Nv; ++v) {
        dist[v] = INFINITY;
        count[v] = 0;
    }
    dist[S] = 0;
    count[S] = 1;
    queue[0] = S;
    vi[S] = true;
    while (head != tail) {
        u = queue[(head++) % Graph->Nv];
        vi[u] = false;
        for (v = 0; v < Graph->Nv; ++v) {
            if (Graph->G[u][v] > 0) {
                p = Graph->G[u][v] + dist[u];
                if (p < dist[v]) {
                    dist[v] = p;
                    if (!vi[v]) {
                        queue[(tail++) % Graph->Nv] = v;
                        vi[v] = true;
                    }
                }
            }
        }
    }
    head = 0; tail = 1; queue[0] = S; dist[S] = 0;
    while (head != tail) {
        u = queue[(head++) % Graph->Nv];
        for (v = 0; v < Graph->Nv; ++v) {
            if (Graph->G[u][v] > 0) {
                if (Graph->G[u][v] + dist[u] == dist[v]) {
                    queue[(tail++) % Graph->Nv] = v;
                    count[v]++;
                }
            }
        }
    }
    for (v = 0; v < Graph->Nv; ++v)
        if (dist[v] == INFINITY) {
            dist[v] = -1;
            count[v] = 0;
        }
}

