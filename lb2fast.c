#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 101

int ord (const void * a, const void * b) {
   return ( *(float*)b - *(float*)a );
}

float l1(float wcl[], float cap_veicolo, float ncl){

  float tot_pesi=0., l1;

  for(int i=0; i<ncl; i++){
    tot_pesi+=wcl[i];
  }
  l1 = tot_pesi/cap_veicolo;

  return ceil(l1);
}

float max(float a, float b){ return a>b?a:b; }

int main(int argc, char *argv[]) {

  FILE *fd;
  int i=1, tmp;
  float capac, l2;
  char c[100];

  fd=fopen(argv[1], "r");
  if( fd==NULL ) {
    perror("Errore in apertura del file");
    exit(1);
  }

  for(int x=0; x<8; x++){
    if(x==4){
      fscanf(fd, "%d", &tmp);
      fscanf(fd, "%f", &capac);
    }else{
      fscanf(fd, "%s", c);
    }
  }
  fgets(c, 100, fd);

  float pesi[N+2];

  while(i<=N){
    for(int j=0; j<7; j++){
      if(j==3){
        fscanf(fd, "%f", &pesi[i]);
      }else{
        fscanf(fd, "%d", &tmp);
      }
    }
    i++;
  }


  fclose(fd);

  qsort(pesi+1, N, sizeof(float), ord);

  int jst;
  for(i=1; i<=N; i++){
    if(pesi[i]<=(capac/2)){
      jst=i;
      break;
    }
  }

  int cj12, jp, js, cj2;

  if(jst==1){
    l2 = l1(pesi+1, capac, N);
  }else{
    float sjst=0.;
    cj12 = jst-1; //|j1|+|j2|
    for(i=jst; i<=N-1; i++){
      sjst+=pesi[i];
    }

    jp=jst;
    for(i=1; i<=N; i++){
      if(i<jst && pesi[i]<=(capac-pesi[jst])){
        jp=i;
        break;
      }
    }
    cj2=jst-jp;//|j2|

    float sj2=0.;
    if(jp<jst){
      for(i=jp; i<=jst-1; i++){
        sj2+=pesi[i];
      }
    }

    js=jst;
    float sj3=pesi[js];
    pesi[N+1]=0;

    while (pesi[js+1]==pesi[js]) {
      js++;
      sj3+=pesi[js];
    }

    l2=cj12;

    do {
      l2 = max(l2, cj12+ceil(((sj3+sj2)/capac)-cj2));
      js++;

      if(js<=N){
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
    } while(js<=N && (cj12+ceil(((sjst+sj2)/capac)-cj2))>l2 );
  }
  printf("%s --> %d\n", argv[1], (int)l2);
  return 0;
}
