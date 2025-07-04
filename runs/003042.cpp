#include <iostream>
#include <string>
#include <vector>
#include <list>

//-------------------------------------------------------------------------------------------------
class my_pair
{
    public:
    int myfrequency;
    std::string myword;

    my_pair()
    {}

    my_pair(std::string In_word, int In_frequency) : myword (In_word), myfrequency (In_frequency)
    {}

    ~my_pair()
    {}
};
//-------------------------------------------------------------------------------------------------
class my_node
{
    public:
    std::vector< int > branch;
    std::list< my_pair > myList;



    my_node() : branch(1), myList()
    {}

    my_node(int branch_number) : branch(branch_number), myList()
    {
        for(int i=0; i<branch_number; ++i)
        {
            branch[i]=0;
        }
    }

    ~my_node()
    {
        branch.clear();
        myList.clear();
    }
};
//-------------------------------------------------------------------------------------------------
int push_button(int button, int CurNode, std::vector< my_node > &myTree)
{
    if( myTree[CurNode].branch[button-2] == 0)
    {
        myTree.push_back(my_node(8));
        myTree[CurNode].branch[button-2]=myTree.size()-1;
        return myTree.size()-1;
    }
    else
    {
        return myTree[CurNode].branch[button-2];
    }
}
//-------------------------------------------------------------------------------------------------
int main()
{
    int f;
    int i;
    int N;
    std::string MyStr;

    std::vector < my_node > myTree(1, my_node(8));

//    std::cout << "Enter N:";
    std::cin>>N;

    for(i=0; i<N; ++i)      // vocabulary
    {
        std::cin>>MyStr;
        std::cin>>f;

        int CurNode=0;

        for(int j=0; j<MyStr.length(); ++j)
        {
            switch( MyStr[j] )
            {
                case 'a':
                case 'b':
                case 'c':
                {
                    CurNode = push_button(2, CurNode, myTree);
                    break;
                }
                case 'd':
                case 'e':
                case 'f':
                {
                    CurNode = push_button(3, CurNode, myTree);
                    break;
                }
                case 'g':
                case 'h':
                case 'i':
                {
                    CurNode = push_button(4, CurNode, myTree);
                    break;
                }
                case 'j':
                case 'k':
                case 'l':
                {
                    CurNode = push_button(5, CurNode, myTree);
                    break;
                }
                case 'm':
                case 'n':
                case 'o':
                {
                    CurNode = push_button(6, CurNode, myTree);
                    break;
                }
                case 'p':
                case 'q':
                case 'r':
                case 's':
                {
                    CurNode = push_button(7, CurNode, myTree);
                    break;
                }
                case 't':
                case 'u':
                case 'v':
                {
                    CurNode = push_button(8, CurNode, myTree);
                    break;
                }
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                {
                    CurNode = push_button(9, CurNode, myTree);
                    break;
                }
            }
        }
        if( myTree[CurNode].myList.empty() )
        {
            myTree[CurNode].myList.push_back(my_pair(MyStr, f));
        }
        else
        {
            std::list< my_pair >::iterator it = myTree[CurNode].myList.begin();
            while( f <= it->myfrequency && it != myTree[CurNode].myList.end())
            {
                ++it;
            }
            myTree[CurNode].myList.insert(it, 1, my_pair(MyStr, f));
        }
    }

    char ch;
    int stage = 0; // 0 - default stage, 1 - word typing, 2 - punctuation, 3 - end of sms
    int step = 0;
    int step_punct = 0;
    int CurNode = 0;

    std::cin.get(ch);
    while (stage!=3 && (std::cin.get(ch)))
    {
        switch(ch)
        {
            case '1':
            {
                switch(stage)
                {
                    case 0:
                    {
                        stage = 2;
                        step_punct = 1;
                        break;
                    }
                    case 1:
                    {
                        std::list< my_pair >::iterator it = myTree[CurNode].myList.begin();

                        for(i=0; i<step; ++i) ++it;
                        std::cout<< (it->myword);

                        it->myfrequency++;

                        if(!step)
                        {
                            std::list< my_pair >::iterator it1 = it;
                            --it1;
                            while (it1->myfrequency <= it->myfrequency && it1 != myTree[CurNode].myList.begin())
                            {
                                --it1;
                            }
                            if( it1 != myTree[CurNode].myList.begin())
                            {
                                ++it1;
                                myTree[CurNode].myList.insert(it1, 1, my_pair(it->myword, it->myfrequency));
                            }
                            else
                            {
                                myTree[CurNode].myList.push_front(my_pair(it->myword, it->myfrequency));
                            }
                        }

                        CurNode = 0;
                        step = 0;
                        stage = 2;
                        step_punct = 1;
                        break;
                    }
                    case 2:
                    {
                        switch(step_punct)
                        {
                            case 1:
                            std::cout<<'.';
                            break;
                            case 2:
                            std::cout<<',';
                            break;
                            case 3:
                            std::cout<<'?';
                            break;
                        }
                        step_punct = 1;
                        break;
                    }
                }
                break;
            }
            case '2':
            {
                switch(stage)
                {
                    case 0:
                    {
                        CurNode = myTree[CurNode].branch[0];
                        stage = 1;
                        break;
                    }
                    case 1:
                    {
                        CurNode = myTree[CurNode].branch[0];
                        break;
                    }
                    case 2:
                    {
                        switch(step_punct)
                        {
                            case 1:
                            std::cout<<'.';
                            break;
                            case 2:
                            std::cout<<',';
                            break;
                            case 3:
                            std::cout<<'?';
                            break;
                        }
                        step_punct = 1;
                        CurNode = myTree[CurNode].branch[0];
                        stage = 1;
                        step = 0;
                        break;
                    }
                }
                break;
            }
            case '3':
            {
                switch(stage)
                {
                    case 0:
                    {
                        CurNode = myTree[CurNode].branch[1];
                        stage = 1;
                        break;
                    }
                    case 1:
                    {
                        CurNode = myTree[CurNode].branch[1];
                        break;
                    }
                    case 2:
                    {
                        switch(step_punct)
                        {
                            case 1:
                            std::cout<<'.';
                            break;
                            case 2:
                            std::cout<<',';
                            break;
                            case 3:
                            std::cout<<'?';
                            break;
                        }
                        step_punct = 1;
                        CurNode = myTree[CurNode].branch[1];
                        stage = 1;
                        step = 0;
                        break;
                    }
                }
                break;
            }
            case '4':
            {
                switch(stage)
                {
                    case 0:
                    {
                        CurNode = myTree[CurNode].branch[2];
                        stage = 1;
                        break;
                    }
                    case 1:
                    {
                        CurNode = myTree[CurNode].branch[2];
                        break;
                    }
                    case 2:
                    {
                        switch(step_punct)
                        {
                            case 1:
                            std::cout<<'.';
                            break;
                            case 2:
                            std::cout<<',';
                            break;
                            case 3:
                            std::cout<<'?';
                            break;
                        }
                        step_punct = 1;
                        CurNode = myTree[CurNode].branch[2];
                        stage = 1;
                        step = 0;
                        break;
                    }
                }
                break;
            }
            case '5':
            {
                switch(stage)
                {
                    case 0:
                    {
                        CurNode = myTree[CurNode].branch[3];
                        stage = 1;
                        break;
                    }
                    case 1:
                    {
                        CurNode = myTree[CurNode].branch[3];
                        break;
                    }
                    case 2:
                    {
                        switch(step_punct)
                        {
                            case 1:
                            std::cout<<'.';
                            break;
                            case 2:
                            std::cout<<',';
                            break;
                            case 3:
                            std::cout<<'?';
                            break;
                        }
                        step_punct = 1;
                        CurNode = myTree[CurNode].branch[3];
                        stage = 1;
                        step = 0;
                        break;
                    }
                }
                break;
            }
            case '6':
            {
                switch(stage)
                {
                    case 0:
                    {
                        CurNode = myTree[CurNode].branch[4];
                        stage = 1;
                        break;
                    }
                    case 1:
                    {
                        CurNode = myTree[CurNode].branch[4];
                        break;
                    }
                    case 2:
                    {
                        switch(step_punct)
                        {
                            case 1:
                            std::cout<<'.';
                            break;
                            case 2:
                            std::cout<<',';
                            break;
                            case 3:
                            std::cout<<'?';
                            break;
                        }
                        step_punct = 1;
                        CurNode = myTree[CurNode].branch[4];
                        stage = 1;
                        step = 0;
                        break;
                    }
                }
                break;
            }
            case '7':
            {
                switch(stage)
                {
                    case 0:
                    {
                        CurNode = myTree[CurNode].branch[5];
                        stage = 1;
                        break;
                    }
                    case 1:
                    {
                        CurNode = myTree[CurNode].branch[5];
                        break;
                    }
                    case 2:
                    {
                        switch(step_punct)
                        {
                            case 1:
                            std::cout<<'.';
                            break;
                            case 2:
                            std::cout<<',';
                            break;
                            case 3:
                            std::cout<<'?';
                            break;
                        }
                        step_punct = 1;
                        CurNode = myTree[CurNode].branch[5];
                        stage = 1;
                        step = 0;
                        break;
                    }
                }
                break;
            }
            case '8':
            {
                switch(stage)
                {
                    case 0:
                    {
                        CurNode = myTree[CurNode].branch[6];
                        stage = 1;
                        break;
                    }
                    case 1:
                    {
                        CurNode = myTree[CurNode].branch[6];
                        break;
                    }
                    case 2:
                    {
                        switch(step_punct)
                        {
                            case 1:
                            std::cout<<'.';
                            break;
                            case 2:
                            std::cout<<',';
                            break;
                            case 3:
                            std::cout<<'?';
                            break;
                        }
                        step_punct = 1;
                        CurNode = myTree[CurNode].branch[6];
                        stage = 1;
                        step = 0;
                        break;
                    }
                }
                break;
            }
            case '9':
            {
                switch(stage)
                {
                    case 0:
                    {
                        CurNode = myTree[CurNode].branch[7];
                        stage = 1;
                        break;
                    }
                    case 1:
                    {
                        CurNode = myTree[CurNode].branch[7];
                        break;
                    }
                    case 2:
                    {
                        switch(step_punct)
                        {
                            case 1:
                            std::cout<<'.';
                            break;
                            case 2:
                            std::cout<<',';
                            break;
                            case 3:
                            std::cout<<'?';
                            break;
                        }
                        step_punct = 1;
                        CurNode = myTree[CurNode].branch[7];
                        stage = 1;
                        step = 0;
                        break;
                    }
                }
                break;
            }
            case ' ':
            {
                switch(stage)
                {
                    case 0:
                    {
                        std::cout<< " ";
                        break;
                    }
                    case 1:
                    {
                        std::list< my_pair >::iterator it = myTree[CurNode].myList.begin();

                        for(i=0; i<step; ++i) ++it;
                        std::cout<< (it->myword) << " ";

                        std::string cur_word=it->myword;
                        int cur_frequency = it->myfrequency;
                        ++cur_frequency;

                        std::list< my_pair >::iterator it1 = it;
                        --it1;
                        myTree[CurNode].myList.erase(it);
                        while( cur_frequency >= it1->myfrequency && it1 != myTree[CurNode].myList.begin())
                        {
                            --it1;
                        }
                        if( it1 != myTree[CurNode].myList.begin()) ++it1;
                        myTree[CurNode].myList.insert(it1, 1, my_pair(cur_word, cur_frequency));

                        stage = 0;
                        CurNode = 0;
                        step = 0;
                        break;
                    }
                    case 2:
                    {
                        switch(step_punct)
                        {
                            case 1:
                            std::cout<<". " ;
                            break;
                            case 2:
                            std::cout<<", ";
                            break;
                            case 3:
                            std::cout<<"? ";
                            break;
                        }
                        step_punct = 1;
                        CurNode = 0;
                        stage = 0;
                        step = 0;
                        break;
                    }
                }
                break;
            }
            case '*':
            {
                switch(stage)
                {
                    case 0:
                    {
                        std::cout<< '*';
                        break;
                    }
                    case 1:
                    {
                        ++step;
                        break;
                    }
                    case 2:
                    {
                        ++step_punct;
                        break;
                    }
                }
                break;
            }
            case '\n':
            {
                switch(stage)
                {
                    case 1:
                    {
                        std::list< my_pair >::iterator it = myTree[CurNode].myList.begin();
                        for(i=0; i<step; ++i) ++it;
                        std::cout<< (it->myword);
                        stage = 3;
                        break;
                    }
                    case 2:
                    {
                        switch(step_punct)
                        {
                            case 1:
                            std::cout<<'.';
                            break;
                            case 2:
                            std::cout<<',';
                            break;
                            case 3:
                            std::cout<<'?';
                            break;
                        }
                        break;
                    }
                }
                stage = 3;
                break;
            }
        }
    }

    myTree.clear();
    return 0;
}
