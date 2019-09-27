#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<search.h>

struct cl{
  int e;
  int l;
  int s;
};

int ord (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int max(int a, int b){ return a>b?a:b; }

int wleft(int i, int t1, int t2, struct cl c[]){
  int time = t2-t1;
  int max1 = max(0, (c[i].e+c[i].s-t1));
  int x[3] = {time, max1, c[i].s};
  qsort(x, 3, sizeof(int), ord);
  return x[0];

}

int wright(int i, int t1, int t2, struct cl c[]){
  int time = t2-t1;
  int max1 = max(0, (t2-c[i].l));
  int x[3] = {time, max1, c[i].s};
  qsort(x, 3, sizeof(int), ord);
  return x[0];
}

int w(int i, int t1, int t2, struct cl c[]){
  if(wleft(i, t1, t2, c)>wright(i, t1, t2, c)){
    return wright(i, t1, t2, c);
  }else{
    return wleft(i, t1, t2, c);
  }
}

int w1(int t1, int t2, struct cl c[], int ncl){
  int sum = 0;
  for(int j = 1; j<ncl; j++){
    sum+=w(j, t1, t2, c);
  }
  return sum;
}

int en(int t1, int t2, int m){
  return m*(t2-t1);
}

int test(struct cl t[], int n, int m){
  //n=N

  int *t1, *t2, *tmp, size=2, temp[(n-1)*3], i;
  size_t count=0;
  t1 = (int *)malloc(size*sizeof(int));

  for(int k = 1; k<n; k++){
    temp[count++] = t[k].e;
    temp[count++] = t[k].l;
    temp[count++] = t[k].e+t[k].s;
  }

  qsort(temp, count, sizeof(int), ord);

  t1[0] = temp[0];
  count=1;
  for(i=1; i<(n-1)*3; i++){
    if(count>=size){
      size*=2;
      tmp=(int *)realloc(t1,size*sizeof(int));
      if(tmp!=NULL){
        t1=tmp;
      }else{
        printf("realloc failure\n");
        exit(EXIT_FAILURE);
      }
    }
    if(t1[count-1]!=temp[i]){
      t1[count++]=temp[i];
    }
  }

  size=2;
  t2 = (int *)malloc(size*sizeof(int));
  size_t count1=0;

  for(int k = 1; k<n; k++){
    temp[count1++] = t[k].l+t[k].s;
    temp[count1++] = t[k].e+t[k].s;
    temp[count1++] = t[k].l;
  }
  qsort(temp, count1, sizeof(int), ord);

  t2[0] = temp[0];
  count1=1;
  for(i=1; i<(n-1)*3; i++){
    if(count1>=size){
      size*=2;
      tmp=(int *)realloc(t2,size*sizeof(int));
      if(tmp!=NULL){
        t2=tmp;
      }else{
        printf("realloc failure\n");
        exit(EXIT_FAILURE);
      }
    }
    if(t2[count1-1]!=temp[i]){
      t2[count1++]=temp[i];
    }
  }


  int w;
  for(int i = 0; i<count; i++){
    for(int j = 0; j<count1; j++){
      if(t1[i]<t2[j]){
        w=0;
        w=w1(t1[i], t2[j], t, n);
        if(w>en(t1[i], t2[j], m)){
          m++;
        }
      }
    }
  }
  return m;
}

int main(int argc, char *argv[]){

  FILE *fd;
  int num_veicoli, i=1, capac, numcl, m;
  char c;

  fd=fopen(argv[1], "r");
  if( fd==NULL ) {
    perror("Errore in apertura del file");
    exit(1);
  }

  fscanf(fd, "%d", &numcl);
  fscanf(fd, "%d", &m);
  struct cl tempi[(numcl-1)];
  struct cl tempi1[numcl-1];
  int j=1;

  while(!feof(fd)){
    if(i>=numcl){
      fscanf(fd, "%d", &tempi1[j].e);
      fscanf(fd, "%d", &tempi1[j].l);
      fscanf(fd, "%d", &tempi1[j].s);
      j++;
    }else{
      fscanf(fd, "%d", &tempi[i].e);
      fscanf(fd, "%d", &tempi[i].l);
      fscanf(fd, "%d", &tempi[i].s);
      i++;
    }
  }

  fclose(fd);

  int sol1 = test(tempi, numcl, m);
  int sol2 = test(tempi1, numcl, m);

  int sol = max(sol1, sol2);
  printf("%d\n", sol);

  return 0;
}
