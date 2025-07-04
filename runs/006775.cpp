//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

typedef unsigned short ushort ;

typedef struct Link Link;

typedef struct Node
{
	ushort i;
	Link** links;
	Link* up;
	int linkN;
	int maxLinkN;
	ushort Depth;
} Node;

struct Link
{
	Node* l1;
	Node* l2;
	int L;
};

ushort N; // kol-vo vershin
ushort LINKS=10;
Node** G;
ushort *Order, *First;
ushort index=1;
ushort *Seg; //massiv visot
ushort *SegTree; //derevo otrezkov

void NewNode(ushort i,Node* N){
	N->linkN=0;
	N->maxLinkN=LINKS;
	N->links = (Link**)malloc(LINKS*sizeof(Link*));
	N->i=i;
}

void Resize(int i)
{
	G[i]->maxLinkN*=2;
	G[i]->links=(Link**)realloc(G[i]->links,G[i]->maxLinkN*sizeof(Link*));
}

Node* GoLink(Node* N,Link *L)//perehod po ssilke 'i' ot uzla 'N'
{
	if(L==NULL) return NULL;
	if(L->l1!=N) return L->l1; 
	else return L->l2;
}

void Scan() // chtenie dannih, sozdanie reber
{
	unsigned short int n1, n2, l, i;
	scanf("%hu", &N);
	G = (Node**)malloc(N*sizeof(Node*)); // tut hranitsa derevo. G[i] - vershina 'i'
	Link *L;
	for(i=1; i <= N; i++) 
		{
			G[i]=(Node*)malloc(sizeof(Node));
			NewNode(i,G[i]);
			G[i]->up=NULL;
		}
	for(i = 0; i < N-1; i++){
		scanf("%hu %hu %hu",&n1, &n2, &l);
		L=(Link*)malloc(sizeof(Link));
		L->L=l;
		L->l1=G[n1];
		L->l2=G[n2];
		G[n1]->links[ G[n1]->linkN ] = L;
		G[n2]->links[ G[n2]->linkN ] = L;
		G[n1]->linkN++;
		G[n2]->linkN++;
		if(G[n1]->linkN >= G[n1]->maxLinkN-1) Resize(n1);
		if(G[n2]->linkN >= G[n2]->maxLinkN-1) Resize(n2);
	}
}

ushort min(ushort a, ushort b)
{
	if (a<b) return a;
	return b;
}

ushort max(ushort a, ushort b)
{
	if (a>b) return a;
	return b;
}

void MakeOrder(Node* g, ushort D)
{
	Order[index]=g->i;
	if(First[g->i]==0) First[g->i]=index;
	g->Depth=D;
	index++;
	D++;
	for(int i=0; i< g->linkN; i++)
	{
		Node *L= GoLink(g,g->links[i]);
		if (g->up!=g->links[i]) {
			MakeOrder(L,D);
			Order[index]=g->i;
			index++;
		}
	}
}

void build (int v, int l, int r) //derevo otrezkov
{
	if (l == r)
		SegTree[v] = Seg[l];
	else {
		int m = (l + r) / 2;
		build (v*2, l, m);
		build (v*2+1, m+1, r);
		SegTree[v] = min(SegTree[v*2], SegTree[v*2+1]);
	}
}

ushort GetMin(int v, int L, int R, int l, int r) {
	if (l == L && r == R)
		return SegTree[v];
	int M = (L + R) / 2;
	if(r<=M) return GetMin (v*2, L, M, l, r);
	if(l>M) return GetMin (v*2+1, M+1, R, l, r);
	ushort an1 = GetMin (v*2, L, M, l, M);
	ushort an2 = GetMin (v*2+1, M+1, R, M+1, r);
	return min(an1,an2);
}

void MakeTree(Node *N) // rekursivno prohodim po derevu, pomechaem kto chei predok
{
	int i;
	Node* Up = GoLink(N,N->up);
	for(i=0; i<N->linkN; i++)
	{
		Node* l= GoLink(N,N->links[i]);
		if (l!=Up){ 
			l->up=N->links[i];
			MakeTree(l);
		}
	}
}

void Preproc () // preprocessing dlya zadachi LCA
{
	Order = (ushort*)malloc(sizeof(ushort)*N*3); 
	First = (ushort*)malloc(sizeof(ushort)*N*3); 
	int i; 
	for( i=0; i< 3*N; i++ ) First[i]=0;
	MakeOrder(G[1],0);
	Seg = (ushort*)malloc(sizeof(ushort)*index);
	SegTree = (ushort*)malloc(sizeof(ushort)*index*4);
	int j=0;
		while(j<index-1){
			Seg[j]=G[Order[j+1]]->Depth;
			j++;
		}
	build(1,0,index-1);
}

void LCA() // nahojdenie minimuma na otrezke
{
	Preproc();
	ushort M, i, j, v1, v2;
	scanf("%hu", &M);
	for(i=0;i<M;i++)
	{
		scanf("%hu %hu",&v1, &v2);
		if(First[v1]>First[v2]){ushort tmp=v1; v1=v2; v2=tmp;}
		int Min = GetMin(1,0,index-1,First[v1]-1,First[v2]-1);
		Node *T1 = G[v1], *T2=G[v2];
		int Sum = 0;
		while(T1->Depth>Min)  // podnimaemsya vverh do ukazannoj visoti, i summiruyem rebra
			{Sum+=T1->up->L; T1=GoLink(T1,T1->up);}
		while(T2->Depth>Min) 
			{Sum+=T2->up->L; T2=GoLink(T2,T2->up);}
		printf("%d\n",Sum);
	}
}

int main()
{
	Scan();
	MakeTree(G[1]);
	LCA();
	return 0;
}
