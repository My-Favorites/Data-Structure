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


/* wrong function. need to be updated. */
void
ShortestDist(MGraph Graph, int dist[], int count[], Vertex S)
{
    bool *vi = malloc(sizeof(*vi) * Graph->Nv);
    Vertex u, v;
    bool f;
    int p;
    for (v = 0; v < Graph->Nv; ++v) {
        dist[v] = -1;
        count[v] = 0;
        vi[v] = false;
    }
    dist[S] = 0;
    count[S] = 1;
    for (; ;) {
        f = false;
        for (u = 0; u < Graph->Nv; ++u)
            if (!vi[u] && dist[u] >= 0) {
                f = true;
                break;
            }
        if (!f)
            break;
        for (v = u + 1; v < Graph->Nv; ++v)
            if (!vi[v] && dist[v] >= 0 && dist[v] < dist[u])
                u = v;
        vi[u] = true;
        for (v = 0; v < Graph->Nv; ++v) {
            if (Graph->G[u][v] > 0) {
                p = Graph->G[u][v] + dist[u];
                if (dist[v] < 0 || p < dist[v]) {
                    dist[v] = p;
                    count[v] = count[u];
                } else if (dist[v] >= 0 && p == dist[v]) {
                    count[v] += count[u];
                }
            }
        }
    }
    free(vi);
}
