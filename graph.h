
typedef struct grafo *Grafo;

//grafo di n vertici
Grafo crea_grafo(int n);

//libera lo spazio occupato dal grafo
void elimina_grafo(Grafo);

//aggiunge un arco di estremi (i;j) al grafo
void aggiungi_arco(Grafo, int i, int j);

int conta_vertici(Grafo);
int conta_archi(Grafo);

//successore j del vertice i
int vertice_succ(Grafo, int i, int j);

//numero successori del vertice u nel grafo
int num_successori_vertice(Grafo, int u);
