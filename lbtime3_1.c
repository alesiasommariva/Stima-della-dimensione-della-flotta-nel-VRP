#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "graph.h"
#define N 101

struct cl{
  int id;
  int e;
  int l;
  int s;
  int x;
  int y;
  int q;
};

int main(int argc, char *argv[]){

  FILE *fd;
  int num_veicoli, e, l, s, j, i=0, capac;
  char c[100];

  fd=fopen(argv[1], "r");
  if( fd==NULL ) {
    printf("%s\n",argv[1]);
    perror("Errore in apertura del file");
    exit(1);
  }

  for(int x=0; x<8; x++){
    if(x==4){
      fscanf(fd, "%d", &num_veicoli);
      fscanf(fd, "%d", &capac);
    }else{
      fscanf(fd, "%s", c);
    }
  }
  fgets(c, 100, fd);

  struct cl tempi[N];

  while(!feof(fd)){
    fscanf(fd, "%d", &tempi[i].id);
    fscanf(fd, "%d", &tempi[i].x);
    fscanf(fd, "%d", &tempi[i].y);
    fscanf(fd, "%d", &tempi[i].q);
    fscanf(fd, "%d", &tempi[i].e);
    fscanf(fd, "%d", &tempi[i].l);
    fscanf(fd, "%d", &tempi[i].s);
    i++;
    }

  fclose(fd);

  int distanze[N][N];

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      distanze[i][j]=sqrt(pow(tempi[j].x-tempi[i].x, 2)+ pow(tempi[j].y-tempi[i].y, 2));
    }
  }

  int inc[N][N];
  Grafo g = crea_grafo(N);

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      if(i!=j){
        if(tempi[i].e+tempi[i].s+distanze[i][j]>tempi[j].l && tempi[j].e+tempi[j].s+distanze[j][i]>tempi[i].l){
          inc[i][j]=1;
          aggiungi_arco(g, tempi[i].id, tempi[j].id);
        }else if(distanze[0][i]+distanze[i][j]+distanze[j][0]>tempi[0].l && distanze[0][j]+distanze[j][i]+distanze[i][0]>tempi[0].l){
          inc[i][j]=1;
          aggiungi_arco(g, tempi[i].id, tempi[j].id);
        }else if(tempi[i].q+tempi[j].q>capac){
          inc[i][j]=1;
          aggiungi_arco(g, tempi[i].id, tempi[j].id);
        }else{
          inc[i][j]=0;
        }
      }else{
        inc[i][j]=0;
      }
    }
  }

  if(conta_archi(g)!=0){
    printf("p edge %d\n", conta_vertici(g));

    for(i=1; i<conta_vertici(g); i++){
      for(j=0; j<num_successori_vertice(g, i); j++){
        printf("e %d %d\n", i, vertice_succ(g, i, j));
      }
    }
  }else{
    printf("niente");
  }

  return 0;
}
