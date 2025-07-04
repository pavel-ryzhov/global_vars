#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct spisok
{
	int sym;
	char str[22];
	int rel;
	int par_or_not;
	struct spisok *next;
	struct spisok *child;
	struct spisok *sp;
	struct spisok *go_to_par;
	struct spisok *next_first;
	struct spisok *last_first;
	struct spisok *last;
};

struct spisok* add_in_list(char[] ,int, struct spisok *);
void free_list (struct spisok*);
int getnum(char);

int main(void)
{
    char buf[100002];
    char *buf2;
    char c,c2;
    int i,j,k,n,n2,x,kol,kp,kolv;
    struct spisok *head=NULL;
    struct spisok *cur=NULL;
	struct spisok *cur2;
	struct spisok *cur3=NULL;
	struct spisok *cur4=NULL;
	struct spisok *sled;
	struct spisok *sled2;
	struct spisok *sled3;
	struct spisok *tmp=NULL;
	struct spisok *prev;
    //FILE *fi,*fo;
    //fi=fopen("input.txt","r");
    //fo=fopen("output.txt","w");
    scanf("%d",&n);
    for (i=0;i<n;i++)
    {
        scanf("%s",buf);
        scanf("%d",&k);
        head=add_in_list(buf,k,head);
    }
    
    gets(buf);
    gets(buf);
    n=strlen(buf)-1;
    i=0;
    while ((buf[i]!='\0')&&(buf[i]!='\n'))
    {
        k=0;
        cur2=head;
        while ((buf[i]>='2')&&(buf[i]<='9'))
        {
            cur=cur2;
            x=buf[i]-'0';
            while (cur->sym!=x)
                if (i==0) cur=cur->next_first;
                else
                    if ((buf[i-1]<'2')||(buf[i-1]>'9'))
                        cur=cur->next_first;
                    else cur=cur->next;
                
            if (cur->par_or_not==-1)
                if (cur->go_to_par!=NULL) 
                    cur2=cur->go_to_par->child;
                else
                    cur2=cur;
            else cur2=cur->child;
            i++;
        }
        cur2=cur->sp;
        kol=0;
        while (buf[i]=='*')
        {
            kol++;
            i++;
        }
        j=0;
        while (j<kol)
        {
            j++;
            cur2=cur2->next;
        }
        cur2->rel++;
        n2=cur2->rel;
        prev=cur->sp;
        tmp=(struct spisok*)malloc(sizeof(struct spisok));
        tmp->child=NULL;
        tmp->sp=NULL;
        tmp->next=NULL;
        strcpy(tmp->str,cur2->str);
        printf("%s",cur2->str);
        tmp->rel=cur2->rel;
        if (cur->sp!=cur2)
        {
            cur3=cur->sp;
            while (cur3->next!=cur2)
                cur3=cur3->next;
            cur3->next=cur2->next;
            free(cur2);
            if (prev->rel<=n2)
            {
                tmp->next=prev;
                cur->sp=tmp;
            }
            else
            {
                cur3=prev;
                if ((cur3->rel>n2)&&(cur3->next!=NULL))
                    cur3=cur3->next;
                while ((cur3->rel>n2)&&(cur3->next!=NULL))
                {    
                    prev=prev->next;
                    cur3=cur3->next;
                }
                if (cur3->next==NULL)
                    if (cur3->rel>n2)
                    {
                        cur3->next=tmp;
                        tmp->next=NULL;
                    }
                    else
                    {
                        tmp->next=cur3;
                        prev->next=tmp;
                    }
                else
                {
                    tmp->next=cur3;
                    prev->next=tmp;
                }
            }
        }
        else free(tmp);
        while (((buf[i]<'2')||(buf[i]>'9'))&&(buf[i]!='\0')&&(buf[i]!='\n'))
        {
            kp=0;
            while (buf[i]==' ') {kp++;i++;}
            for (j=0;j<kp;j++) printf("%c",' ');
            while (buf[i]=='1') 
            {
                if (buf[i+1]=='1') printf("%c",'.');
                i++;
            }
            if (buf[i-1]=='1')
            {
                kol=0;
                while (buf[i]=='*')
                {
                    kol++;
                    i++;
                }
                if (kol==0) printf("%c",'.');
                if (kol==1) printf("%c",',');
                if (kol==2) printf("%c",'?');
            }
        }
    }
    /*cur=head;
	while(cur!=NULL)
	{
		cur2=cur->child;
		fprintf(fo,"\n---------------\nsym=%d\n",cur->sym);
		while (cur2!=NULL)
		{
            sled2=cur2->next;
            cur3=cur2->sp;
            fprintf(fo,"  child: sym=%d\n",cur2->sym);
            while (cur3!=NULL)
            {
                fprintf(fo,"    word: '%s'\n",cur3->str);
                sled3=cur3->next;
                free(cur3);
                cur3=sled3;
            }
            free(cur2);
            cur2=sled2;
        }
        sled=cur->next;
		free(cur);
		cur=sled;
	}
    */
    free_list(head);
    //scanf("%d",&x);
    //close(fi); 
    //close(fo);
}

struct spisok* add_in_list(char mas[],int n, struct spisok* head)
{
    struct spisok* nov=NULL;
    struct spisok* cur=NULL;
    struct spisok* cur2=NULL;
    struct spisok* nov2=NULL;
    struct spisok* nov3=NULL;
    struct spisok* prev=NULL;
    int len,i,num;
    len=strlen(mas);
	for (i=0;i<len;i++)
    {
        nov=(struct spisok*)malloc(sizeof(struct spisok));
        nov->next=NULL;
        nov->child=NULL;
        nov->sp=NULL;
        nov->go_to_par=NULL;
        nov->next_first=NULL;
        nov->last_first=NULL;
        nov->last=NULL;
        num=getnum(mas[i]);
        nov->sym=num;
        if (head==NULL)
        {
            head=nov;
            nov->next=NULL;
            head->last=nov;
            if (i==0) head->last_first=nov;
            cur2=nov;
        }
        else
        {
            cur=head;
            if (cur2==NULL)
            {
                nov->par_or_not=1;
                while ((cur->next_first!=NULL)&&(cur->sym!=num))
                    cur=cur->next_first;
                if (cur->sym==num) cur2=cur;
                else
                {
                    cur->next=nov;
		            nov->next=NULL;
		            cur2=nov;
                }
                if (cur2!=head->last_first)
                    head->last_first->next_first=cur2;
                head->last=cur2;
                if (i==0) head->last_first=cur2;
            }
            else
            {
                cur=head;
                nov->par_or_not=-1;
                if (cur2->par_or_not==-1)
                    if (cur2->go_to_par==NULL)
                    {
                        cur=head->last;
                        //while (cur->next!=NULL) 
                        //    cur=cur->next;
                        nov2=(struct spisok*)malloc(sizeof(struct spisok));
                        nov2->sym=cur2->sym;
                        nov2->sp=NULL;
                        nov2->next=NULL;
                        nov2->child=NULL;
                        nov2->go_to_par=NULL;
                        nov2->par_or_not=1;
                        nov2->next_first=NULL;
                        nov2->last_first=NULL;
                        nov2->last=NULL;
                        
                        head->last_first->next_first=nov2;
                        head->last=nov2;
                        if (i==0) head->last_first=nov2;
                        
                        cur->next=nov2;
                        cur2->go_to_par=nov2;
                        cur2=nov2;
                        cur=cur2;
                    }
                    else {cur2=cur2->go_to_par; cur=cur2;}
                else
                    while (cur!=cur2) cur=cur->next_first;
                
                if (cur->child!=NULL)
                {
                    cur=cur->child;
                    while ((cur->next!=NULL)&&(cur->sym!=num))
                        cur=cur->next;
                    if (cur->sym==num) cur2=cur;
                    else
                    {
                        cur->next=nov;
		                nov->next=NULL;
		                cur2=nov;
                    }
                }
                else
                {
                    cur->child=nov;
                    nov->next=NULL;
                    nov->child=NULL;
                    nov->sp=NULL;
                    nov->go_to_par=NULL;
                    cur2=nov;
                }
            }
        }
    }
    nov3=(struct spisok*)malloc(sizeof(struct spisok));
    nov3->child=NULL;
    nov3->sp=NULL;
    nov3->next=NULL;
    nov3->go_to_par=NULL;
    nov3->rel=n;
    strcpy(nov3->str,mas);
    if (cur2->sp==NULL)
    {
        nov3->next=NULL;
        cur2->sp=nov3;
    }
    else
    {
        prev=cur2->sp;
        if (prev->next==NULL)
        {
            if (prev->rel>=n) prev->next=nov3;
            else
            {
                nov3->next=prev;
                cur2->sp=nov3;
            }
        }
        else
        if (prev->rel<n)
        {
            nov3->next=prev;
            cur2->sp=nov3;
        }
        else
        {
            cur=prev->next;
            while ((cur->rel>=n)&&(cur->next!=NULL))
            {    
                prev=prev->next;
                cur=cur->next;
            }
            if (cur->next==NULL)
                if (cur->rel>=n)
                {
                    cur->next=nov3;
                    nov3->next=NULL;
                }
                else
                {
                    nov3->next=cur;
                    prev->next=nov3;
                }
            else
            {
                nov3->next=cur;
                prev->next=nov3;
            }
        }
    }
	return (head);
}

int getnum(char c)
{
    int n;
    if ((c>='a')&&(c<='c')) n=2;
    if ((c>='d')&&(c<='f')) n=3;
    if ((c>='g')&&(c<='i')) n=4;
    if ((c>='j')&&(c<='l')) n=5;
    if ((c>='m')&&(c<='o')) n=6;
    if ((c>='p')&&(c<='s')) n=7;
    if ((c>='t')&&(c<='v')) n=8;
    if ((c>='w')&&(c<='z')) n=9;
    return n;
}

void free_list(struct spisok* head)
{
	struct spisok *cur;
	struct spisok *cur2;
	struct spisok *cur3;
	struct spisok *sled;
	struct spisok *sled2;
	struct spisok *sled3;
	cur=head;
	while(cur!=NULL)
	{
		cur2=cur->child;
		while (cur2!=NULL)
		{
            sled2=cur2->next;
            cur3=cur2->sp;
            while (cur3!=NULL)
            {
                sled3=cur3->next;
                free(cur3);
                cur3=sled3;
            }
            free(cur2);
            cur2=sled2;
        }
        sled=cur->next;
		free(cur);
		cur=sled;
	}
}
