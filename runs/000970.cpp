 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **create_arc(int N)
{
    int **arc;
    int i,j;
    arc = (int**)malloc(sizeof(int*)*0);
    for (i = 0; i<N; i++)
    {
        arc = (int**)realloc(arc, (i+1)*sizeof(int*));
        arc[i] = (int*)malloc(sizeof(int)*N);
    }

    for (i =0; i<N; i++)
        for (j = 0; j<N; j++)
            arc[i][j] = -10;
    return arc;
}

void height_test(int N, int cur, int **arc, int **path, int *height)
{
    int i;
    for (i = 2; i<N; i++)
    {
        if (arc[cur][i]>=0 && path[cur][i] == -10 && i!=cur)
        {
            height[i] = height[cur]+1 ;
            path[i][cur] = 1; path[cur][i] = 1;
            height_test(N, i, arc, path, height);
        }
    }
}




int direct_parent(int N, int cur, int **arc,int *height)
{
    int i=1;
    if (cur == 1) {return 1;}
    for (i = 1; i<N; i++)
    {
        if(arc[cur][i]>=0 && height[i]<height[cur])
        {
            return i;
        }
    }
     return 0;
}

int parent(int N, int cur, int par, int **arc, int *height, int len)
{
    int i, hc = 0, hp = 0;
    hc = height[cur];
    hp = height[par];
    while (hp!=hc)
    {
        if (hc>hp) { i=direct_parent(N, cur, arc,height); hc--;
            len+=arc[cur][i]; cur=i;                    }
        else { i=direct_parent(N, par, arc,height); hp--;
            len+=arc[par][i]; par=i;}
               }

    while (cur!=par)
    {
        i = direct_parent(N, cur, arc,height); len+=arc[cur][i]; cur=i;
        i=direct_parent(N, par, arc,height); len+=arc[par][i]; par=i;
    }
    return len;
}

int *str_read(char *str, int count)
{
    int i=1;
    char *arr;
    int *num;
    num = (int*)malloc(sizeof(int)*count);
    arr = strtok(str, " ");
    num[0] = atoi(arr);
    while  (arr!=NULL && i<count) {
        arr = strtok(NULL, " ");
        num[i] = atoi(arr);
        i++;

    }

    return num;
}





int main()
{
    int N, M, i, j, str_count=0, len=0;
    int **arc, **path;
    char *str;
    int *num;
    int *height;

    num = (int*)malloc(sizeof(int)*10);
    arc = (int**)malloc(sizeof(int*)*0);
    str = (char*)malloc(255*sizeof(char));



    //stdin = fopen("./tree_text","r");
    while(!feof(stdin))
    {
        str = fgets(str,255,stdin);
        if (str != NULL)
        {
            str_count++;
            if (str_count == 1)
            {
                N = atoi(str);
                arc = create_arc(N+1);
                path = create_arc(N+1);
                height = (int*)malloc(sizeof(int)*(N+1));
            }
            if (str_count>1 && str_count<=N)
            {
                num = str_read(str, 3);
                i = num[0]; j = num[1];
                    arc[i][j] = num[2];
                    arc[j][i] = num[2];
            }
            if (str_count == N+1)
            {
                M = atoi(str);
                height_test(N+1, 1, arc, path, height);

            }
            if (str_count>=N+2 && str_count<=N+M+1)
            {
                num = str_read(str, 2); i = num[0]; j = num[1];
                printf("%d \n",parent(N+1,i, j, arc, height, len));
             }
        }
    }

    return 0;
}