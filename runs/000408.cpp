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
		//char buf[40];
		string buf;
		//itoa(ikey,buf,10);
		buf=toString(ikey);
		voc[i].key=buf;
	}
}

int findpivot(int i, int j){
	int firstkey=voc[i].rate;
	for(int k=i+1;k<=j;k++){
		if(voc[k].rate<firstkey){
			return k;
		}
		else if(voc[k].rate>firstkey){
			return i;
		}
	}
	return 0;
}

int partition(int i, int j, int pivot){
	int l=i;
	int r=j;
	while(1==1){
		voc_type temp;
		temp.key=voc[l].key;
		temp.wrd=voc[l].wrd;
		temp.rate=voc[l].rate;
		voc[l].key=voc[r].key;
		voc[l].wrd=voc[r].wrd;
		voc[l].rate=voc[r].rate;
		voc[r].key=temp.key;
		voc[r].wrd=temp.wrd;
		voc[r].rate=temp.rate;
		while(voc[l].rate>pivot) l++;
		while(voc[r].rate<=pivot) r--;
		if(l>r) break;
	}
	return l;
}

void quicksort(int i, int j){
	int pivotindex=findpivot(i,j);
	if(pivotindex!=0){
		int pivot=voc[pivotindex].rate;
		int k=partition(i,j,pivot);
		quicksort(i,k-1);
		quicksort(k,j);
	}

}

void simplesort(){
	voc_type temp;
	for(int i=0;i<(num_of_words-1);i++){
		for(int j=i+1;j<num_of_words;j++){
			if(voc[i].rate<voc[j].rate){
				temp.key=voc[i].key;
				temp.wrd=voc[i].wrd;
				temp.rate=voc[i].rate;
				voc[i].key=voc[j].key;
				voc[i].wrd=voc[j].wrd;
				voc[i].rate=voc[j].rate;
				voc[j].key=temp.key;
				voc[j].wrd=temp.wrd;
				voc[j].rate=temp.rate;
			}
		}
	}
}

void printvoc(){
	for(int i=0;i<num_of_words;i++){
		cout<<"key="<< voc[i].key<<" word="<<voc[i].wrd<<" rate="<<voc[i].rate<<endl;
	}
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
		if(voc[i].key.find(code)==0){
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
			for(int j=i-1;j>-1;j--){
				if(voc[i].rate>=voc[j].rate){
					temp.key=voc[i].key;
					temp.wrd=voc[i].wrd;
					temp.rate=voc[i].rate;
					voc[i].key=voc[j].key;
					voc[i].wrd=voc[j].wrd;
					voc[i].rate=voc[j].rate;
					voc[j].key=temp.key;
					voc[j].wrd=temp.wrd;
					voc[j].rate=temp.rate;
				}
			}
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
				outstr+=temp;
				code="1";
				num_of_stars=0;
			}
		}
		else if(c==' '){
			if(code!=""){
                temp=decode(code,num_of_stars); 
				increm(temp);
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

int input(string fname){

	ifstream ifsin(fname.c_str(),ios::in);

	if(!ifsin){
		cerr<<"\nImpossible to open file "<<fname;
		return -1;
	}

	string buf;

	if(!getline(ifsin,buf)){
		return -1;
	}

	//num_of_words=atoi(buf.c_str());	
    num_of_words = fromString<int>(buf);

	voc= new voc_type[num_of_words];

	for(int j=0;j<num_of_words;j++){

		if(!getline(ifsin,buf)){
			return -1;
		}	

		int pos=buf.find(" ");
		voc[j].wrd=buf.substr(0,pos);
		buf=buf.substr(pos+1);
		//voc[j].rate=atoi(buf.c_str());
		voc[j].rate=fromString<int>(buf);

	} 

	if(!getline(ifsin,buf)){
		return -1;
	}
	instr=buf;

	ifsin.close();
	return 0;
}

int output(string fname,string str){
	ofstream ofsout(fname.c_str(),ios::out);
	if(!ofsout){
		cerr<<"\nImpossible to open file "<<fname;
		return -1;
	}
	ofsout<<str;


	ofsout.close();
	return 0;
}

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

	input(src_file);
	build_keys();
	//quicksort(0,num_of_words-1);
	simplesort();
	//printvoc();
	string outstr=scaning();
	output(total_file,outstr);
	cout<<"Operation completed"<<endl;
	return 0;
};