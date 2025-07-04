#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
//-----------------------------------------------
class my_pair
{
    public:
    int key;
    int distance;

    my_pair()
    {
        this->key=0;
        this->distance=0;
    }

    my_pair(int inKey, int inDistance)
    {
        this->key=inKey;
        this->distance=inDistance;
    }

    ~my_pair()
    {}
};
//-----------------------------------------------
void my_dfs(int cur, int prev, std::vector< std::vector< my_pair > > &g, std::vector< int > &myHeight,  std::vector< my_pair > &myAncestor)
{
    if(!prev)
    {
        myHeight[cur-1]=1;
    }
    else
    {
        myHeight[cur-1]=myHeight[prev-1]+1;
    }
    for(unsigned int i=0; i<g[cur-1].size(); ++i)
    {
        if(!myHeight[g[cur-1][i].key-1])
        {
            myAncestor[g[cur-1][i].key-1]=my_pair(cur, g[cur-1][i].distance);
            my_dfs(g[cur-1][i].key, cur, g, myHeight, myAncestor);
        }
    }
}
//-----------------------------------------------
int my_way(int v1, int v2, std::vector< std::vector< my_pair > > &g, std::vector< my_pair > &myAncestor, std::vector< int > &myHeight)
{
    if (v1 == v2)
    {
        return 0;
    }
    else
    {
        int distance_v1_v2;

        distance_v1_v2 = 0;

        if(myHeight[v1-1]>=myHeight[v2-1])
        {
            while(myHeight[v1-1] != myHeight[v2-1])
            {
                distance_v1_v2 = distance_v1_v2 + myAncestor[v1-1].distance;
                v1=myAncestor[v1-1].key;
            }
        }
        else
        {
            while(myHeight[v2-1] != myHeight[v1-1])
            {
                distance_v1_v2 = distance_v1_v2 + myAncestor[v2-1].distance;
                v2=myAncestor[v2-1].key;
            }
        }

        while (v1 != v2)
        {
            distance_v1_v2 = distance_v1_v2 + myAncestor[v2-1].distance;
            v2=myAncestor[v2-1].key;
            distance_v1_v2 = distance_v1_v2 + myAncestor[v1-1].distance;
            v1=myAncestor[v1-1].key;
        }
        return distance_v1_v2;
    }
}
//-----------------------------------------------
int main()
{
    std::string myFilename;
    std::cout<< "Enter name of Inputfile:";
    std::cin>>myFilename;

    std::ifstream InputFile(&myFilename[0], std::ios::in);

    if( !InputFile )
    {
        std::cerr<< "File could not be opened" << std::endl;
        exit(1);
    }

    std::ofstream OutputFile("answer.txt", std::ios::out);

    if( !OutputFile )
    {
        std::cerr << "File could not be opened" << std::endl;
        exit(1);
    }

    int r_begin;
    int r_end;
    int r_length;
    int N, M;
    int i;

    InputFile >> N;

    std::vector< std::vector< my_pair > > g(N);
    std::vector< my_pair > myAncestor(N);
    std::vector< int > myHeight(N);

    for(i=0; i<N-1; ++i)
    {
        InputFile >> r_begin;
        InputFile >> r_end;
        InputFile >> r_length;

        g[r_begin-1].push_back(my_pair(r_end, r_length));
        g[r_end-1].push_back(my_pair(r_begin, r_length));
    }

    my_dfs(1, 0, g, myHeight, myAncestor);
    InputFile>> M;

    for(i=0; i<M; ++i)
    {
        InputFile >> r_begin;
        InputFile >> r_end;
        OutputFile << my_way(r_begin, r_end, g, myAncestor, myHeight) << std::endl;
    }

    myHeight.clear();
    myAncestor.clear();
    g.clear();
    return 0;
}
