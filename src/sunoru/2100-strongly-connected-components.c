#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

/* Your function will be put here */
Graph ReadG()
{
    int i, x, y;
    PtrToVNode p;
    Graph g = malloc(sizeof(*g));
    scanf("%d%d", &g->NumOfVertices, &g->NumOfEdges);
    g->Array = malloc(sizeof(*g->Array)*g->NumOfVertices);
    for (i = 0; i < g->NumOfVertices; ++i) {
        g->Array[i] = NULL;
    }
    for (i = 0; i < g->NumOfEdges; ++i) {
        scanf("%d%d", &x, &y);
        p = malloc(sizeof(*p));
        p->Vert = y;
        p->Next = g->Array[x];
        g->Array[x] = p;
    }
    return g;
} /* details omitted */

int vi[MaxVertices];
int s[MaxVertices];
int instack[MaxVertices];
int top = 0;
int indexes[MaxVertices];
int ind = 0;

void dfs(Graph g, Vertex u, void (*visit)(Vertex V))
{
    int v;
    indexes[u] = vi[u] = ind++;
    s[top++] = u;
    instack[u] = 1;
    PtrToVNode p = g->Array[u];
    while (p) {
        v = p->Vert;
        if (indexes[v] == -1) {
            dfs(g, v, visit);
            if (vi[v] < vi[u])
                vi[u] = vi[v];
        } else if (instack[v] && indexes[v] < vi[u]) {
            vi[u] = indexes[v];
        }
        p = p->Next;
    }
    if (vi[u] == indexes[u]) {
        do {
            visit(s[--top]);
            instack[s[top]] = 0;
        } while (s[top] != u);
        printf("\n");
    }
}

void
StronglyConnectedComponents(Graph G, void (*visit)(Vertex V))
{
    int i;
    for (i = 0; i < G->NumOfVertices; ++i) {
        indexes[i] = -1;
    }
    for (i = 0; i < G->NumOfVertices; ++i) {
        if (indexes[i] == -1) {
            dfs(G, i, visit);
        }
    }
}
