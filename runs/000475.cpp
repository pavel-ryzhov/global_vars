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

typedef struct{
	string key;
	string wrd;
	int rate;
}voc_type;

voc_type *voc;

int num_of_words;

string keyboard[9]={".,?","abc","def","ghi","jkl",
"mno","pqrs","tuv","wxyz"};
string instr;

void build_keys(){
	for(int i=0;i<num_of_words;i++){
		int ikey=0;
		for(unsigned int j=0;j<voc[i].wrd.length();j++){
			for(int k=1;k<9;k++){
				int pos=keyboard[k].find(voc[i].wrd.at(j));
				if(pos>=0){
					ikey=10*ikey+k+1;
					break;
				}
			}
		}
		string buf;
		buf=toString(ikey);
		voc[i].key=buf;
	}
}



void simplesort(){
	voc_type temp;
	int max;
	for(int i=0;i<(num_of_words-1);i++){
		max=i;
		for(int j=i+1;j<num_of_words;j++){
			if(voc[max].rate<voc[j].rate){
				max=j;
				
			}
		}
		
		if(max>i){
			
			temp.key=voc[max].key;
			temp.wrd=voc[max].wrd;
			temp.rate=voc[max].rate;
			
			for(int j=max;j>=(i+1);j--){
				voc[j].key=voc[j-1].key;
				voc[j].wrd=voc[j-1].wrd;
				voc[j].rate=voc[j-1].rate;
				
			}
			
			voc[i].key=temp.key;
			voc[i].wrd=temp.wrd;
			voc[i].rate=temp.rate;  
			
        } 
		
	}
}

   


void printvoc(){
	for(int i=0;i<num_of_words;i++){
		cout<<"key="<< voc[i].key<<" word="<<voc[i].wrd<<" rate="<<voc[i].rate<<endl;

	}
	cout<<endl;
}

string decode(string code, int num_of_stars){
	string res="";
	int count=0;
	if(code=="1"){
		if(num_of_stars==0) return ".";
        if(num_of_stars==1) return ",";
        if(num_of_stars==2) return "?";
		return "";
	}
	for(int i=0;i<num_of_words;i++){
		if(voc[i].key==code){
			if (count==num_of_stars){
				return(voc[i].wrd);
			}
			else {
				count++;
			}
		}
	}
	return res;

}

void increm(string str){
	voc_type temp;
	for(int i=0;i<num_of_words;i++){
		if(voc[i].wrd==str){
			voc[i].rate++;
			int j;
			bool found=false;
			for(j=i-1;j>-1;j--){
                if(voc[i].rate<voc[j].rate) 
				{
					found=true;
					break;
				}
			}
			
			if(!found) j=-1;
			temp.key=voc[i].key;
			temp.wrd=voc[i].wrd;
			temp.rate=voc[i].rate;
			
			
			for(int k=i;k>=(j+2);k--){
				voc[k].key=voc[k-1].key;
				voc[k].rate=voc[k-1].rate;
				voc[k].wrd=voc[k-1].wrd;
			}
            voc[j+1].key=temp.key;
			voc[j+1].wrd=temp.wrd;
			voc[j+1].rate=temp.rate;

			break;
		}
	}
}

string scaning(){
	string outstr="";
	int num_of_stars=0;
	string code="";
	string temp;
	char c;
	for(unsigned int i=0;i<instr.length();i++){
		c=instr.at(i);
		if((c>='2')&&(c<='9')){
			code+=c;
			num_of_stars=0;
		}
		else if(c=='*'){
			num_of_stars++;
		}
		else if(c=='1'){
            if(code!=""){
				temp=decode(code,num_of_stars);
				increm(temp);
				//cout<<temp<<endl<<endl;
				//printvoc();
				outstr+=temp;
				code="1";
				num_of_stars=0;
			}
		}
		else if(c==' '){
			if(code!=""){
                temp=decode(code,num_of_stars); 
				increm(temp);
				//cout<<temp<<endl<<endl;
                //printvoc();
				outstr+=temp;
				outstr+=" ";
				code="";
				num_of_stars=0;
			}
		}
	}
	if(code!=""){
		outstr+=decode(code,num_of_stars);
        
	}
	return(outstr);

}

int input(){

  

	string buf;

	getline(cin,buf);

    num_of_words = fromString<int>(buf);

	voc= new voc_type[num_of_words];

	for(int j=0;j<num_of_words;j++){

		getline(cin,buf);
		

		int pos=buf.find(" ");
		voc[j].wrd=buf.substr(0,pos);
		buf=buf.substr(pos+1);
		voc[j].rate=fromString<int>(buf);

	} 

	getline(cin,buf);
	instr=buf;

	return 0;
}

int output(string str){
	cout<<str;


	return 0;
}

int main(int argc, char *argv[]){


	input();
	build_keys();
	simplesort();
	//printvoc();
	string outstr=scaning();
	output(outstr);
	return 0;
};