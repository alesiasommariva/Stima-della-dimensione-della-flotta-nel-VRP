#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#define N 101

struct cl{
  int id;
  int e;
  int l;
  int s;
  int x;
  int y;
  int d;
};

int max(int a, int b){ return a>b?a:b; }

int ord (const void * a, const void * b) {
   return ( *(float*)a - *(float*)b );
}

int calcoloLb1(int num_cl, int pesi[], float c){
  float tot_pesi=0.;

  for(int i = 0; i<num_cl; i++){
    tot_pesi+=pesi[i];
  }
  float numV = tot_pesi/c;

  return ceil(numV);
}

int calcololb2fast(int num_cl, int pesi[], float capac){
  qsort(pesi+1, num_cl, sizeof(float), ord);

  int jst;
  for(int i=1; i<=num_cl; i++){
    if(pesi[i]<=(capac/2)){
      jst=i;
      break;
    }
  }

  int cj12, jp, js, cj2;
  float l2;

  if(jst==1){
    l2 = calcoloLb1(num_cl, pesi+1, capac);
  }else{
    float sjst=0.;
    cj12 = jst-1;
    for(int i=jst; i<=num_cl; i++){
      sjst+=pesi[i];
    }

    jp=jst;
    for(int i=1; i<=num_cl; i++){
      if(i<jst && pesi[i]<=(capac-pesi[jst])){
        jp=i;
        break;
      }
    }
    cj2=jst-jp;

    float sj2=0.;
    if(jp<jst){
      for(int i=jp; i<=jst-1; i++){
        sj2+=pesi[i];
      }
    }

    js=jst;
    float sj3=pesi[js];
    pesi[num_cl+1]=0;

    while (pesi[js+1]==pesi[js]) {
      js++;
      sj3+=pesi[js];
    }

    l2=cj12;

    do {
      l2 = max(l2, cj12+ceil(((sj3+sj2)/capac)-cj2));
      js++;

      if(js<=num_cl){
        sj3+=pesi[js];
        while (pesi[js+1]==pesi[js]) {
          js++;
          sj3+=pesi[js];
        }

        while (jp>1 && pesi[jp-1]<=(capac-pesi[js])) {
          jp--;
          cj2++;
          sj2+=pesi[jp];
        }
      }
    } while(js<=num_cl && (cj12+ceil(((sjst+sj2)/capac)-cj2))>l2 );
  }
  return (int)l2;
}

int leggi_clique(char *f){
  FILE *fd;
  fd=fopen(f, "r");
  int m;

  if( fd==NULL ) {
    perror("Errore in apertura del file2");
    exit(1);
  }

  fscanf(fd, "%d", &m);

  return m;
}

int main(int argc, char *argv[]){

  FILE *fd;
  int num_veicoli, j, i=0;
  float capac;
  char c[100];

  fd=fopen(argv[1], "r");
  if( fd==NULL ) {
    perror("Errore in apertura del file1");
    exit(1);
  }

  for(int x=0; x<8; x++){
    if(x==4){
      fscanf(fd, "%d", &num_veicoli);
      fscanf(fd, "%f", &capac);
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
    fscanf(fd, "%d", &tempi[i].d);
    fscanf(fd, "%d", &tempi[i].e);
    fscanf(fd, "%d", &tempi[i].l);
    fscanf(fd, "%d", &tempi[i].s);
    i++;
    }

  fclose(fd);

  float distanze[N][N];

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      distanze[i][j]=sqrt((tempi[j].x-tempi[i].x)*(tempi[j].x-tempi[i].x)+(tempi[j].y-tempi[i].y)*(tempi[j].y-tempi[i].y));
    }
  }

  float dist_depo[N-1];
  for (int i = 1; i < N; i++) {
    dist_depo[i-1] = distanze[0][i];
  }
  qsort(dist_depo, N-1, sizeof(float), ord);

  int pesi[N+1];
  for(int i=1; i<N; i++){
    pesi[i] = tempi[i].d;
  }
  int lb1 = calcoloLb1(N-1, pesi+1, capac);
  int lb2 = calcololb2fast(N-1, pesi, capac);

  int clique = leggi_clique(argv[2]);

  int m = max(max(lb1,lb2), clique);
  printf("%d\n", m);

  int teta[N+m];

  int max1=0, min=0, temp;
  for(i=1; i<N; i++){
    if(distanze[i][0]+tempi[i].s>tempi[0].e-tempi[i].l){
      max1 = distanze[i][0]+tempi[i].s;
    }else{
      max1 = tempi[0].e-tempi[i].l;
    }
    min=max1;
    for(j=1; j<N; j++){
      if(i!=j){
        if(distanze[i][j]+tempi[i].s>tempi[j].e-tempi[i].l){
          max1 = distanze[i][j]+tempi[i].s;
        }else{
          max1 = tempi[j].e-tempi[i].l;
        }

        temp=max1;
        if(temp<min){
          min=temp;
        }
      }
    }
    teta[i] = min;
  }

  for (size_t i = N; i < N+m; i++) {
    teta[i] = dist_depo[i-N];//questi sono i w(pesi) per ogni cliente
  }

  int lb3 = calcololb2fast(N+m, teta, tempi[0].l);

  printf("%d\n",lb3);

  return 0;

}
