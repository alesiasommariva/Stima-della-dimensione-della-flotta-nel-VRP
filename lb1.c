#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define N 101
//testato
float l1(float wcl[], float cap_veicolo, int ncl){

  float tot_pesi=0., l1;

  for(int i = 0; i<ncl; i++){
    tot_pesi+=wcl[i];
  }
  l1 = tot_pesi/cap_veicolo;
  return ceil(l1);
}

int main(int argc, char *argv[]) {

  FILE *fd;
  float num_veicoli, capac;
  char c[100];
  int i=0, tmp;

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

  float pesi[N];

  while(i<=100){
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
float numV = l1(pesi+1, capac, N-1);
printf("%s --> %d\n",argv[1], (int)numV);

return 0;
}
