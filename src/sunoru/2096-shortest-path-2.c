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

void ShortestDist( MGraph Graph, int dist[], Vertex S );

int main()
{
    int dist[MaxVertexNum];
    Vertex S, V;
    MGraph G = ReadG();

    scanf("%d", &S);
    ShortestDist( G, dist, S );

    for ( V=0; V<G->Nv; V++ )
        printf("%d ", dist[V]);

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
ShortestDist(MGraph Graph, int dist[], Vertex S)
{
    Vertex *queue = malloc(sizeof(*queue) * Graph->Nv);
    bool *vi = malloc(sizeof(*vi) * Graph->Nv);
    int head = 0, tail = 1;
    Vertex u, v;
    int p;
    for (v = 0; v < Graph->Nv; ++v)
        dist[v] = INFINITY;
    dist[S] = 0;
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
    for (v = 0; v < Graph->Nv; ++v)
        if (dist[v] == INFINITY)
            dist[v] = -1;
}

