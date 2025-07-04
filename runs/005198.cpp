#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <cstdlib>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class dict_part
{
public:
    dict_part* pointr;
    char* str;
    int n,l;
    bool last_used;

	dict_part(int l1,char* s1,int n1)
	{
		last_used=false;
		l=l1;
		n=n1;
		pointr=NULL;
		str=(char*)malloc(sizeof(char)*l);
		for (int i=0;i<l;i++)
			{*(str+i)=*(s1+i);};
	}
	~dict_part()
	{ 
		free(str); 
	}
protected:
private:
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class dict_hdr
{
public:
	char* str_n;
	int l;
	dict_hdr* next;
	dict_part* down;

	dict_hdr(int l1,char* s1)
	{
		next=NULL;
	    down=NULL;
		l=l1;
		str_n=(char*)malloc(sizeof(char)*l);
		for (int i=0;i<l;i++)
			{*(str_n+i)=*(s1+i);};
	}
	~dict_hdr()
	{
		free(str_n); 
	}
private:
protected:
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char *conv(int l1,char* sss)
{

char temp;
char* temp_str;

temp_str=(char*)malloc(sizeof(char)*l1);

for (int i1=0;i1<l1;i1++)
{   
	switch (*(sss+i1))
	{
	case 'a': temp='2'; break;
	case 'b': temp='2'; break;
	case 'c': temp='2'; break;
	case 'd': temp='3'; break;
	case 'e': temp='3'; break;
	case 'f': temp='3'; break;
	case 'g': temp='4'; break;
	case 'h': temp='4'; break;
	case 'i': temp='4'; break;
	case 'j': temp='5'; break;
	case 'k': temp='5'; break;
	case 'l': temp='5'; break;
	case 'm': temp='6'; break;
	case 'n': temp='6'; break;
	case 'o': temp='6'; break;
	case 'p': temp='7'; break;
	case 'q': temp='7'; break;
	case 'r': temp='7'; break;
	case 's': temp='7'; break;
    case 't': temp='8'; break;
	case 'u': temp='8'; break;
	case 'v': temp='8'; break;
	case 'w': temp='9'; break;
	case 'x': temp='9'; break;
	case 'y': temp='9'; break;
	case 'z': temp='9'; break;
	default:  temp='?'; break;
	};
	*(temp_str+i1)=temp;
};

return temp_str;

};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool str_equal(int l1,char *str1,int l2,char *str2)
{
bool flag;	
if (l1!=l2) return false;
flag=true;
int ii1=0;   
while ((flag==true)&&(ii1<l1))
{  
   if (*(str1+ii1)==*(str2+ii1)) ii1++;
   else flag=false;
};
return flag;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void sortirovka(dict_hdr * h)
{
dict_part* p_now_f,*p_now_s,*temp,*p,*prew,*temp1,*temp2;
bool flag1;

p=h->down;

if (p->pointr==NULL)
{
	return;	
}
else
{
flag1=true;
while (flag1==true)
{
	flag1=false;
	if ((h->down->n<h->down->pointr->n)||((h->down->n==h->down->pointr->n)&&(h->down->pointr->last_used==true)))
	{
		temp=h->down;
		temp1=h->down->pointr;
		temp2=h->down->pointr->pointr;
		h->down=temp1;
		h->down->pointr=temp;
		h->down->pointr->pointr=temp2;
		flag1=true;
	};
	
	prew=h->down;
	p_now_f=h->down->pointr;
	p_now_s=h->down->pointr->pointr;
	while (p_now_s!=NULL)
	{
		if ((p_now_s->n>p_now_f->n)||((p_now_s->n==p_now_f->n)&&(p_now_s->last_used==true)))
		{
			temp=p_now_s->pointr;
			prew->pointr=p_now_s;
			p_now_s->pointr=p_now_f;
			p_now_f->pointr=temp;

			prew=p_now_s;
			p_now_f=p_now_f;
			p_now_s=temp;
			flag1=true;
		}
        else
        {
		prew=prew->pointr;
		p_now_f=p_now_f->pointr;
		p_now_s=p_now_s->pointr;
		};
	};

};

};
return;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




int main()
{
 const int max_word_lenth=20;

 int N;
 
 char temp;
 char* str_temp,*conv_str;
 int nmb,freq;
 char temp_read;

 str_temp=(char*)malloc(sizeof(char)*max_word_lenth);
 conv_str=(char*)malloc(sizeof(char)*max_word_lenth);
 
 scanf("%d",&N);
 scanf("%c",&temp_read); 

 dict_part* d_p_now,*d_p_now_temp;
 dict_hdr* d_box_first,*d_b_now,*d_b_now_temp;
 bool flag_seek;
 
 //nachinaem schiivanie----------------------------------------------
 for (int j=0;j<N;j++)
 {
	 nmb=0;
	 scanf("%c",&temp);
	 while (!(temp==' '))
	 {
		 *(str_temp+nmb)=temp;
		 scanf("%c",&temp);
		 nmb++; 
	 };

        //for (int iii1=0;iii1<nmb;iii1++) {printf("%c",*(str_temp+iii1));}; printf("--l=%d--",nmb);

	 conv_str=conv(nmb,str_temp);
     
	 scanf("%d",&freq);
     scanf("%c",&temp_read); 

        //for (int iii=0;iii<nmb;iii++) {printf("%c",*(conv_str+iii));}; printf("\n");
	 
	 dict_part *one_part = new dict_part(nmb,str_temp,freq); 
	 
	 if (j==0) 
	 {
		 dict_hdr* d_box = new dict_hdr(nmb,conv_str);
		 d_box_first=d_box;
		 d_box->down=one_part;
	 }
	 else 
	 {	 
		 d_b_now=d_box_first; 
		 flag_seek=false;

		 while (((str_equal(d_b_now->l,d_b_now->str_n,nmb,conv_str)!=true)&&(!(d_b_now->next==NULL))||(!(d_b_now->next==0))))
		 {
			 d_b_now=d_b_now->next;
		 };

		 if ((str_equal(d_b_now->l,d_b_now->str_n,nmb,conv_str)==false) && (d_b_now->next==NULL)) //добавим в самый конец
         {
			 
			 dict_hdr* d_box = new dict_hdr(nmb,conv_str);
			 d_b_now->next=d_box;
			 d_box->down=one_part;
		 };
		 if ((str_equal(d_b_now->l,d_b_now->str_n,nmb,conv_str)==true))
		 {
			 if (d_b_now->down==NULL) d_b_now->down=one_part;
			 else
			 {
				 d_p_now=d_b_now->down;
				 while (d_p_now->pointr!=0)  {d_p_now=d_p_now->pointr;};
				 d_p_now->pointr=one_part;
			 };
		 };
     };
	 
 };
 
 //zakonchili schitivanie------------------------------------------------------
 
 d_b_now=d_box_first;
 while (d_b_now!=NULL)
 {
	sortirovka(d_b_now);
    d_b_now=d_b_now->next;
 };
 
/////////////////////////////////////////////////////////////////////////////////////
 char *sss;
 int sss_len=0,sss_pos;
	 sss=(char*)malloc(sizeof(char)*100000);
	 	
 int ch,ch1; 
 ch = getchar();  
 do 
 { 
     if (ch != 10)
	 {
	  *(sss+sss_len)=ch;
	  sss_len++; ch1=ch;
	 };
     ch = getchar();
 } while ((ch != 10)&&(ch1 != 13));


 int numb_elem=0;
 int numb_stars=0;
 char space_sign=32,star_sign=42; 
 

/////////////////////////////////////shag////////////////////////

sss_pos=0;
bool flag=false;
while (sss_pos<sss_len)
{
 numb_elem=0;
 numb_stars=0;
 if (flag==false) {temp=*(sss+sss_pos); sss_pos++;}
 if (temp==32) printf("%c",temp);
 else
 {
 while ( (temp!=space_sign) && (temp!=star_sign) && (temp!=49) && (sss_pos<=sss_len) )
 {
	 *(str_temp+numb_elem)=temp;
	 temp=*(sss+sss_pos); sss_pos++;
     numb_elem++;
 };

 if (temp==49)
 {
	 numb_stars=0;
	 temp=*(sss+sss_pos); sss_pos++;
	 while ((temp==star_sign)&&(sss_pos<=sss_len))
	 {
		 numb_stars++;
		 temp=*(sss+sss_pos); sss_pos++;
	 };

     d_b_now=d_box_first;
 
	 while ((str_equal(numb_elem,str_temp,d_b_now->l,d_b_now->str_n)==false)&&(d_b_now->next!=NULL))
	 {
		d_b_now=d_b_now->next;
	 };
 
	 if ((str_equal(numb_elem,str_temp,d_b_now->l,d_b_now->str_n)==true))
	 {
		 d_p_now=d_b_now->down;
		
	     for (int nn4=0;nn4<d_p_now->l;nn4++)
			{printf("%c",*(d_p_now->str+nn4));};
 		 d_p_now->n++;
	 }
	 else
	 {
		for (int nn5=0;nn5<numb_elem;nn5++)
			{printf("%c",*(str_temp+nn5));};
	 };

	 switch (numb_stars % 3)
	 {
         case 0: printf("."); break;
	     case 1: printf(","); break;
		 case 2: printf("?"); break;
	 };
	 if (temp==32) {printf("%c",temp); flag=false;} else flag=true;
 }
 
 else
 {
    numb_stars=0;
	while ( (temp==star_sign) && (sss_pos<=sss_len) )
	{
		numb_stars++;
		temp=*(sss+sss_pos); sss_pos++;
	};

	d_b_now=d_box_first;
 
	while ((str_equal(numb_elem,str_temp,d_b_now->l,d_b_now->str_n)==false)&&(d_b_now->next!=NULL))
	{
		d_b_now=d_b_now->next;
	};
 
	if ((str_equal(numb_elem,str_temp,d_b_now->l,d_b_now->str_n)==true))
	{
		d_p_now=d_b_now->down;
		for (int jjj=0;jjj<numb_stars;jjj++)
		{
			if (d_p_now->pointr==NULL) d_p_now=d_b_now->down;
			else d_p_now=d_p_now->pointr;
		};
	    for (int nn2=0;nn2<d_p_now->l;nn2++)
			{printf("%c",*(d_p_now->str+nn2));};
		d_p_now->n++;
		d_p_now->last_used=true;
		sortirovka(d_b_now);
		d_p_now->last_used=false;
		if (temp==32) {printf("%c",temp); flag=false;} else flag=true;
	
	}
	else
	{
		for (int nn3=0;nn3<numb_elem;nn3++)
			{printf("%c",*(str_temp+nn3));};
		if (temp==32) {printf("%c",temp); flag=false;} else flag=true;
	};
 };
 };
};




 //очистка списка
 d_b_now=d_box_first;
 d_p_now=d_box_first->down;
 
 while (((d_b_now!=0)))
 {
	 d_p_now=d_b_now->down;
	 while (d_p_now!=0)  
	 {
		 d_p_now_temp=d_p_now;
		 d_p_now=d_p_now->pointr;
		 delete d_p_now_temp;
	 };
	 d_b_now_temp=d_b_now;
	 d_b_now=d_b_now->next;
	 delete d_b_now_temp;
 }; 

 return 0;

};