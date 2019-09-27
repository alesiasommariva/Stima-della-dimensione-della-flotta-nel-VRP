#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<limits.h>
#define N 101

typedef struct{
  int id;
  int e;
  int l;
  int s;
  int x;
  int y;
  int d;
}cl;

int ord (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int max(int a, int b){ return a>b?a:b; }

int leggi_lbtime3_3(char *f){
  FILE *fd;
  fd=fopen(f, "r");
  int m;


  if( fd==NULL ) {
    perror("Errore in apertura del file");
    exit(1);
  }

  fscanf(fd, "%d", &m);
  fclose(fd);
  return m;
}

cl * evaluation(int distanze[N][N], cl tempi[], int m, int n){

  int i,j;

  int dist[n][n];

  for(i=1; i<N; i++){
    for(j=1; j<N; j++){
      dist[i][j] = distanze[i][j];
    }
  }

  for(i=N; i<N+m; i++){
    for(j=1; j<N; j++){
      dist[i][j] = distanze[0][j];
    }
  }

  for(i=1; i<N; i++){
    for(j=N+m; j<n; j++){
      dist[i][j] = distanze[i][0];
    }
  }

  for(i=1; i<n; i++){
    for(j=N; j<N+m; j++){
      dist[i][j] = -1;
    }
  }

  for(i=N+m; i<n; i++){
    for(j=1; j<n; j++){
      dist[i][j] = -1;
    }
  }

  for(i=N; i<N+m; i++){
    for(j=N+m; j<n; j++){
      dist[i][j] = -1;
    }
  }


  cl * client;
  client = malloc(n * sizeof(cl));
  for(i=N; i<N+m; i++){
    client[i].e = 0;
    client[i].l = 0;
  }
  for(i=N+m; i<n; i++){
    client[i].e = 0;
    client[i].l = tempi[0].l;
  }
  for(i=1; i<N; i++){
    client[i].e = tempi[i].e;
    client[i].l = tempi[i].l;
  }


  int dist_depo[m], tmp[N-1];
  for(i=0; i<N-1; i++){
    tmp[i] = distanze[0][i+1];
  }
  qsort(tmp, N-1, sizeof(int), ord);
  int count=0;
  for(i=0; i<N-1 && count < m; i++){
    if(tmp[i]<0) continue;
    dist_depo[count++] = tmp[i];
  }


  int min[N-1];

  for(i=1; i<N; i++){
    min[i] = INT_MAX;
    for(j=1; j<n; j++){
      if(dist[i][j]<0) continue;
      if(dist[i][j]<min[i]){
        min[i] = dist[i][j];
      }
    }
  }


  for(i=N; i<N+m; i++){
    client[i].s = dist_depo[i-N];
  }
  for(i=N+m; i<n; i++){
    client[i].s = 0;
  }
  for(i=1; i<N; i++){
    client[i].s = tempi[i].s+min[i];
  }


  //reducing rows
  for(i=1; i<N; i++){
    for(j=1; j<n; j++){
      if(dist[i][j]!= -1)
        dist[i][j] -= min[i];
    }
  }

  for(i=N; i<N+m; i++){
    for(j=1; j<n; j++){
      if(dist[i][j]!= -1)
        dist[i][j] = max(0, dist[i][j]-dist_depo[i-N]);
    }
  }


  //reducing columns
  int min1[n];
  for(j=1; j<n; j++){
    min1[j] = INT_MAX;
    for(i=1; i<n; i++){
      if(dist[i][j]<0) continue;
      if(dist[i][j]<min1[j]){
        min1[j] = dist[i][j];
      }
    }
    if(min1[j]==INT_MAX){
      min1[j]=0;
    }
  }


  for(j=1; j<N; j++){
    for(i=1; i<n; i++){
      if(dist[i][j]!= -1)
        dist[i][j] -= min1[j];
    }
  }


  int dist_depo1[m];
  for(i=0; i<N-1; i++){
    tmp[i] = distanze[i+1][0];
  }
  qsort(tmp, N-1, sizeof(int), ord);
  count=0;
  for(i=0; i<N-1 && count < m; i++){
    if(tmp[i]<0) continue;
    dist_depo1[count++] = tmp[i];
  }

  for(j=N+m; j<n; j++){
    for(i=1; i<n; i++){
      if(dist[i][j]!= -1)
        dist[i][j] = max(0, dist[i][j]-dist_depo1[j-(N)]);
    }
  }

  //aggiornamento finestre temporali e tempi servizio
  for(i=1; i<n; i++){
    client[i].e = max(0, client[i].e-min1[i]);
    client[i].l = max(0, client[i].l-min1[i]);
    client[i].s += min1[i];
  }

  return client;
}

int main(int argc, char *argv[]){

  FILE *fd;
  int num_veicoli, j, i=0, capac;
  char c[100];

  fd=fopen(argv[1], "r");
  if( fd==NULL ) {
    perror("Errore in apertura del file");
    exit(1);
  }

  cl tempi[N];
  int distanze[N][N];

  for(int x=0; x<8; x++){
    if(x==4){
      fscanf(fd, "%d", &num_veicoli);
      fscanf(fd, "%d", &capac);
    }else{
      fscanf(fd, "%s", c);
    }
  }
  fgets(c, 100, fd);

  while(!feof(fd)){
    fscanf(fd, "%d", &tempi[i].id);
    fscanf(fd, "%d", &tempi[i].x);
    fscanf(fd, "%d", &tempi[i].y);
    fscanf(fd, "%d", &tempi[i].d);
    fscanf(fd, "%d", &tempi[i].e);
    fscanf(fd, "%d", &tempi[i].l);
    fscanf(fd, "%d", &tempi[i].s);
    i++;
  }
  fclose(fd);

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      distanze[i][j]=sqrt(pow(tempi[j].x-tempi[i].x, 2)+ pow(tempi[j].y-tempi[i].y, 2));
    }
  }

  for(i = 1; i<N; i++){
    for(j = 0; j<N; j++){
      distanze[i][j] = max(distanze[i][j], tempi[j].e-(tempi[i].l+tempi[i].s));
    }
  }

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      if(tempi[i].e+tempi[i].s+distanze[i][j]>tempi[j].l && i!=j){
        distanze[i][j] = -1;
      }else if (i==j) {
        distanze[i][j] = -1;
      }
    }
  }

  int trasposta[N][N];
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      trasposta[i][j] = distanze[j][i];
    }
  }

  int m = leggi_lbtime3_3(argv[2]);
  int n = N+2*m;

  cl *client1 = evaluation(distanze, tempi, m, n);
  cl *client2 = evaluation(trasposta, tempi, m, n);



  printf("%d\n", n);
  printf("%d\n", m);

  for(i=1; i<n; i++){
    printf("%d\t%d\t%d\n", client1[i].e, client1[i].l, client1[i].s);
  }

  printf("\n");
  for (size_t i = 1; i < n; i++) {
    printf("%d\t%d\t%d\n", client2[i].e, client2[i].l, client2[i].s);
  }

  return 0;
}
