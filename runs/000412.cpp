#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
string toString(T val)
{
    ostringstream oss;
    oss<< val;
    return oss.str();
}

template<typename T> 
T fromString(const string& s) 
{
  istringstream iss(s);
  T res;
  iss >> res;
  return res;
}

class tree {
    int** weights;
	int** distances;
    int num_of_nodes;
	int num_of_results;
	int** result_nodes;

	
public:

	int read_from_file(){

		int i,j,k;
		
		
		string buf;
				
		getline(cin,buf);
		num_of_nodes=fromString<int>(buf);
		
		weights=new int*[num_of_nodes];
		
		for(i=0;i<num_of_nodes;i++){
			weights[i]=new int[num_of_nodes];
			for(k=0;k<num_of_nodes;k++){
                if(i==k){
				  weights[i][k]=0;
				}
				else weights[i][k]=40001;
			}
		}

		for(j=0;j<num_of_nodes-1;j++){
		   

		   getline(cin,buf);
		   
		   int pos=buf.find(" ");
		   string buf2=buf.substr(0,pos);
		   int from_node=fromString<int>(buf2)-1;
		   buf=buf.substr(pos+1);
		   pos=buf.find_first_not_of(" ");
		   buf=buf.substr(pos);
		   pos=buf.find(" ");
		   buf2=buf.substr(0,pos);
		   int to_node=fromString<int>(buf2)-1;
           buf=buf.substr(pos+1);
		   pos=buf.find_first_not_of(" ");
		   buf=buf.substr(pos);
		   pos=buf.find(" ");
		   buf2=buf.substr(0,pos);
           weights[from_node][to_node]=fromString<int>(buf2);   
           weights[to_node][from_node]=fromString<int>(buf2); 
		}


        getline(cin,buf);

		num_of_results=fromString<int>(buf);
		
		result_nodes=new int*[num_of_results];
        
		for(i=0;i<num_of_results;i++){
			result_nodes[i]=new int[2];

		   getline(cin,buf);

           int pos=buf.find(" ");
		   string buf2=buf.substr(0,pos);
		   result_nodes[i][0]=fromString<int>(buf2)-1;
		   buf=buf.substr(pos+1);
		   pos=buf.find_first_not_of(" ");
		   buf=buf.substr(pos);
		   pos=buf.find(" ");
		   buf2=buf.substr(0,pos);
           result_nodes[i][1]=fromString<int>(buf2)-1;
        }

		return 0;
	}


	void floyd(){
		distances=new int*[num_of_nodes];
		for(int i=0;i<num_of_nodes;i++){
			distances[i]=new int[num_of_nodes];
			for(int k=0;k<num_of_nodes;k++){
			  distances[i][k]=weights[i][k];
			}
		}

		for(int k=0;k<num_of_nodes;k++){
		   for(int i=0;i<num_of_nodes;i++){
			  if (distances[i][k]>40000) continue;
              for(int j=0;j<num_of_nodes;j++){
				  if (distances[k][j]>40000) continue;
				  if((distances[i][k]+distances[k][j])<distances[i][j])
					  distances[i][j]=distances[i][k]+distances[k][j];
			  }
		   }
		}

	}
	
	int write_pathes(){
		
		for(int i=0; i<num_of_results;i++){
		    cout<<(distances[result_nodes[i][0]][result_nodes[i][1]])<<endl;
		  
		}

		return 0;
	}
	
};



int main(){
	
	
	
	tree t;
	t.read_from_file();
	t.floyd();
	t.write_pathes();
   
	return 0;
};
