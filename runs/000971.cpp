#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned short int **create_arc(unsigned short int N)
{
    unsigned short int **arc;
    unsigned short int i,j;
    arc = (unsigned short int**)malloc(sizeof(unsigned short int*)*0);
    for (i = 0; i<N; i++)
    {
        arc = (unsigned short int**)realloc(arc, (i+1)*sizeof(unsigned short int*));
        arc[i] = (unsigned short int*)malloc(sizeof(unsigned short int)*N);
    }

    for (i =0; i<N; i++)
        for (j = 0; j<N; j++)
            arc[i][j] = 40001;
    return arc;
}

bool **create_path(unsigned short int N )
{
    bool **path;
    unsigned short int i,j;
    path = (bool **)malloc(sizeof(bool*)*0);
    for (i = 0; i<N; i++)
    {
        path = (bool**)realloc(path, (i+1)*sizeof(bool*));
        path[i] = (bool*)malloc(sizeof(bool)*N);
    }

    for (i =0; i<N; i++)
        for (j = 0; j<N; j++)
            path[i][j] = 0;
    return path;
}


void height_test(unsigned short int N, unsigned short int cur, unsigned short int **arc, bool **path, unsigned short int *height)
{
    unsigned short int i;
    for (i = 2; i<N; i++)
    {
        if (arc[cur][i]!=40001 && path[cur][i] == 0 && i!=cur)
        {
            height[i] = height[cur]+1 ;
            path[i][cur] = 1; path[cur][i] = 1;
            height_test(N, i, arc, path, height);
        }
    }
}




unsigned short int direct_parent(unsigned short int N, unsigned short int cur, unsigned short int **arc,unsigned short int *height)
{
    unsigned short int i=1;
    if (cur == 1) {return 1;}
    for (i = 1; i<N; i++)
    {
        if(arc[cur][i]!=40001 && height[i]<height[cur])
        {
            return i;
        }
    }
     return 0;
}

unsigned short int parent(unsigned short int N, unsigned short int cur, unsigned short int par, unsigned short int **arc, unsigned short int *height, unsigned short int len)
{
    unsigned short int i, hc = 0, hp = 0;
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

unsigned short int *str_read(char *str, unsigned short int count)
{
    unsigned short int i=1;
    char *arr;
    unsigned short int *num;
    num = (unsigned short int*)malloc(sizeof(unsigned short int)*count);
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
    unsigned short int N, M, i, j, str_count=0, len=0;
    unsigned short int **arc;
    bool **path;
    char *str;
    unsigned short int *num;
    unsigned short int *height;

    num = (unsigned short int*)malloc(sizeof(unsigned short int)*10);
    arc = (unsigned short int**)malloc(sizeof(unsigned short int*)*0);
    str = (char*)malloc(255*sizeof(char));


   // stdin = fopen("./tree_text","r");
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
                path = create_path(N+1);
                height = (unsigned short int*)malloc(sizeof(unsigned short int)*(N+1));
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
                printf("%d\n", parent(N+1,i, j, arc, height, len));

            }
        }
    }
        return 0;}