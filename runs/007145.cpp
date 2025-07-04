#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
  if (a>b) return a;
  return b;
}

int min(int a, int b)
{
  if (a>b) return b;
  return a;
}

int main(int argc, char* argv[])
{
  int M, N, i, j, k, l;
  int *dist;                          // расстояние
  int *res;                           // result
  FILE *in;
  in=stdin;
  fscanf(in, "%d", &N);
  dist=(int*)malloc(N*N*sizeof(int));
  for(k=0;k<N*N;k++)
    dist[k]=-1;                      // значение -1 означает, что расстояние еще не найдено

    //INPUT

  for(k=0;k<N-1;k++)
  {
    fscanf(in, "%d",&i);
    fscanf(in, "%d",&j);
    fscanf(in, "%d",&dist[(i-1)*N+j-1]);
  }
  for(i=0;i<N;i++)                                              //симметризация матрицы
    for(j=i+1;j<N;j++)
      if(dist[i*N+j]>=0 || dist[j*N+i]>=0 )
      {
        dist[i*N+j]=max(dist[j*N+i],dist[i*N+j]);
        dist[j*N+i]=max(dist[j*N+i],dist[i*N+j]);
      }


//MAIN PART
  for(i=0;i<N;i++)
    dist[i*N+i]=0;



  for(l=0; l<2; l++)
  {
    for(i=0; i<N; i++)
    {
      for(j=0; j<N; j++)
      {
        for(k=0; k<N; k++)
        {
          if(dist[i*N+j]>=0 && dist[j*N+k]>=0)
          {
            if (dist[i*N+k]==-1 && dist[k*N+i]==-1)
            {
              dist[i*N+k]=dist[i*N+j]+dist[j*N+k];
              dist[k*N+i]=dist[i*N+k];
            }
            else
            {
              dist[i*N+k]=min(dist[i*N+j]+dist[j*N+k],dist[i*N+k]);
              dist[k*N+i]=dist[i*N+k];
            }
          }
        }
      }
    }
  }


//OUTPUT
  fscanf(in, "%d", &M);
  res=(int*)malloc(M*sizeof(int));
  for(k=0;k<M;k++)
  {
    fscanf(in, "%d",&i);
    fscanf(in, "%d",&j);
    res[k]=dist[(i-1)*N+j-1];
  }
  for(k=0;k<M;k++)
    printf("%d\n", res[k]);
/*
 // OUTPUTALL
    for(i=0;i<N;i++)
    {
      for(j=0;j<N;j++)
        printf("(%d,%d)->%2d; ", i+1, j+1, dist[i*N+j]);
      printf("\n");
    }
*/
  free(res);
  free(dist);
  return 0;
}

