#include <stdio.h>
#include <stdlib.h>

typedef unsigned short ushort ;

typedef struct Node
{
	ushort i;
	Node** links;
	Node* up;
	int linkN;
	int maxLinkN;
	int L;
	ushort Depth;
} Node;

ushort N; // kol-vo vershin
ushort LINKS=5;
Node** G;
ushort *Order, *First;
ushort index=1;
ushort *Seg; //massiv visot
ushort *SegTree; //derevo otrezkov

void NewNode(ushort l, ushort i,Node* N){
	N->linkN=0;
	N->maxLinkN=LINKS;
	N->links = (Node**)malloc(LINKS*sizeof(Node*));
	N->L=l;
	N->i=i;
}

void Scan()
{
	unsigned short int n1, n2, l, i;
	scanf("%hu", &N);
	G = (Node**)malloc(N*sizeof(Node*));
	for(i=1; i <= N; i++) G[i]=(Node*)malloc(sizeof(Node));
	if(N>0) NewNode(0,1,G[1]); else exit(0);
	for(i = 0; i < N-1; i++){
		scanf("%hu %hu %hu",&n1, &n2, &l);
		NewNode(l,n2,G[n2]);
		G[n1]->links[ G[n1]->linkN ] = G[n2];
		G[n1]->linkN++;
		if(G[n1]->linkN >= G[n1]->maxLinkN-1) 
		{
			G[n1]->maxLinkN*=2;
			G[n1]->links=(Node**)realloc(G[n1]->links,G[n1]->maxLinkN*sizeof(Node*));
		}
		G[n2]->up=G[n1];
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
		MakeOrder(g->links[i],D);
		Order[index]=g->i;
		index++;
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

void Preproc ()
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

void LCA()
{
	Preproc();
	ushort M, i, j, v1, v2;
	scanf("%hu", &M);
	for(i=0;i<M;i++)
	{
		scanf("%hu %hu",&v1, &v2);
		if(v1>v2){int tmp=v1; v1=v2; v2=tmp;}
		int Min = GetMin(1,0,index-1,First[v1]-1,First[v2]-1);
		Node *T1 = G[v1], *T2=G[v2];
		int Sum = 0;
		while(T1->Depth>Min) 
			{Sum+=T1->L; T1=T1->up;}
		while(T2->Depth>Min) 
			{Sum+=T2->L; T2=T2->up;}
		printf("%d\n",Sum);
	}
}

int main()
{
	Scan();
	LCA();
	return 0;
}
