#include <stdlib.h>
#include <assert.h>

#include "graph.h"

 /*grafo implementato con liste di adiacenza*/

struct grafo {
    int n;              /* numero vertici */
    int m;              /* numero archi */
    struct successori {
        int d;          /* numero successori */
        int len;        /* numero celle in array */
        int list[1];    /* lista corrente di successori */
    } *info[1];
};

Grafo crea_grafo(int n){
    Grafo g;
    int i;

    g = malloc(sizeof(struct grafo) + sizeof(struct successori *) * (n-1));
    assert(g);

    g->n = n;
    g->m = 0;

    for(i = 0; i < n; i++) {
        g->info[i] = malloc(sizeof(struct successori));
        assert(g->info[i]);

        g->info[i]->d = 0;
        g->info[i]->len = 1;
    }

    return g;
}

void elimina_grafo(Grafo g){
    int i;

    for(i = 0; i < g->n; i++) free(g->info[i]);
    free(g);
}

void aggiungi_arco(Grafo g, int u, int v){
    assert(u >= 0);
    assert(u < g->n);
    assert(v >= 0);
    assert(v < g->n);

    while(g->info[u]->d >= g->info[u]->len) {
        g->info[u]->len *= 2;
        g->info[u] =
            realloc(g->info[u],
                sizeof(struct successori) + sizeof(int) * (g->info[u]->len - 1));
    }

    //aggiunto nuovo arco
    g->info[u]->list[g->info[u]->d++] = v;
    g->m++;
}

int conta_vertici(Grafo g){
    return g->n;
}

int conta_archi(Grafo g){
    return g->m;
}

int vertice_succ(Grafo g, int i, int j){ //successore j del vertice i
  return g->info[i]->list[j];
}

int num_successori_vertice(Grafo g, int u){
    assert(u >= 0);
    assert(u < g->n);

    return g->info[u]->d;
}
