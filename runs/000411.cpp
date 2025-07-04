#include <iostream>
#include <fstream>
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

	int read_from_file(string fname){

		int i,j,k;
		
		ifstream ifsin(fname.c_str(),ios::in);
		
		if(!ifsin){
			cerr<<"\nImpossible to open file "<<fname;
			return -1;
		}
		
		string buf;
		
		
		if(!getline(ifsin,buf)){
			return -1;
		}
        
		//num_of_nodes=atoi(buf.c_str());	
		num_of_nodes=fromString<int>(buf);
		
		//weights=(int**)malloc(num_of_nodes*sizeof(int*));
		weights=new int*[num_of_nodes];
		
		for(i=0;i<num_of_nodes;i++){
            //weights[i]=(int*)malloc(num_of_nodes*sizeof(int));
			weights[i]=new int[num_of_nodes];
			for(k=0;k<num_of_nodes;k++){
                if(i==k){
				  weights[i][k]=0;
				}
				else weights[i][k]=40001;
			}
		}

		for(j=0;j<num_of_nodes-1;j++){
		   
		   if(!getline(ifsin,buf)){
			return -1;
		   }	
		   
		   int pos=buf.find(" ");
		   string buf2=buf.substr(0,pos);
		   //int from_node=atoi(buf2.c_str())-1;
		   int from_node=fromString<int>(buf2)-1;
		   buf=buf.substr(pos+1);
		   pos=buf.find_first_not_of(" ");
		   buf=buf.substr(pos);
		   pos=buf.find(" ");
		   buf2=buf.substr(0,pos);
           //int to_node=atoi(buf2.c_str())-1;
		   int to_node=fromString<int>(buf2)-1;
           buf=buf.substr(pos+1);
		   pos=buf.find_first_not_of(" ");
		   buf=buf.substr(pos);
		   pos=buf.find(" ");
		   buf2=buf.substr(0,pos);
           //weights[from_node][to_node]=atoi(buf2.c_str()); 
           weights[from_node][to_node]=fromString<int>(buf2);   
           //weights[to_node][from_node]=atoi(buf2.c_str());
           weights[to_node][from_node]=fromString<int>(buf2); 
		}

        if(!getline(ifsin,buf)){
			return -1;
		}
        
		//num_of_results=atoi(buf.c_str());
		num_of_results=fromString<int>(buf);
		
        //result_nodes=(int**)malloc(num_of_results*sizeof(int*));
		result_nodes=new int*[num_of_results];
        
		for(i=0;i<num_of_results;i++){
            //result_nodes[i]=(int*)malloc(2*sizeof(int));
			result_nodes[i]=new int[2];
            if(!getline(ifsin,buf)){
			    return -1;
			}
           int pos=buf.find(" ");
		   string buf2=buf.substr(0,pos);
		   //result_nodes[i][0]=atoi(buf2.c_str())-1;
		   result_nodes[i][0]=fromString<int>(buf2)-1;
		   buf=buf.substr(pos+1);
		   pos=buf.find_first_not_of(" ");
		   buf=buf.substr(pos);
		   pos=buf.find(" ");
		   buf2=buf.substr(0,pos);
           //result_nodes[i][1]=atoi(buf2.c_str())-1;
           result_nodes[i][1]=fromString<int>(buf2)-1;
        }

		ifsin.close();
		return 0;
	}


	void floyd(){
	    //distances=(int**)malloc(num_of_nodes*sizeof(int*));
		distances=new int*[num_of_nodes];
		for(int i=0;i<num_of_nodes;i++){
            //distances[i]=(int*)malloc(num_of_nodes*sizeof(int));
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
	
	int write_pathes(string fname){
		ofstream ofsout(fname.c_str(),ios::out);
        if(!ofsout){
			cerr<<"\nImpossible to open file "<<fname;
			return -1;
		}
		for(int i=0; i<num_of_results;i++){
		    ofsout<<(distances[result_nodes[i][0]][result_nodes[i][1]])<<endl;
		  
		}

        ofsout.close();
		return 0;
	}
	
};



int main(int argc, char *argv[]){
	string src_file, total_file;
	
	if(argc>2){
		src_file=argv[1];
		total_file=argv[2];
	}
	else{
		cout<<"Input source file: ";
		cin>> src_file;
		cout<<"Input total file: ";
		cin>>total_file;
	}
	
	tree t;
	if(t.read_from_file(src_file)==-1){
		cout<<"Error on reading file "<<src_file<<endl;
		return -1;
	}
	else{
		t.floyd();
		
		if(t.write_pathes(total_file)==-1){
            cout<<"Error on recording to file "<<total_file<<endl;
		    return -1;
		}
		else{
			cout<<"Operation was completed successfully"<<endl;
		}
	}
	return 0;
};
