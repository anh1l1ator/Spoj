#include<bits/stdc++.h>
using namespace std;
#define mid(L,R) ((L+R)/2)
struct Node{ int cnt , L , R;
    Node()
    {
        cnt=0;
        L = R = -1;
    }
    Node(int x,int y,int z)
    {
        L = x;
        R = y;
        cnt = z;
    }
}tree[8160001];


int fastscan()
{
    register int n=0;
    char ch=getchar_unlocked();
    for(;(ch<48||ch>57);ch=getchar_unlocked())
        ;
    for(;(ch>47&&ch<58);ch=getchar_unlocked())
        n=(n<<3)+(n<<1)+ch-48;
    return n;
}
int G[1000001];
int A[100001],root[100001],RM[100001],B[100001],V[100001];
int gc = 0 , N;

int build(int L , int R)
{
    ++gc;
    if(L==R)
        return gc;
    int x = gc;
    tree[x] = Node(build(L,mid(L,R)),build(mid(L,R)+1,R),0);
    return x;
}


int update(int L , int R , int root , int idx , int val)
{
    if(L>idx || R<idx)
        return root;
    ++gc;
    if(L==idx&&R==idx)
    {
        tree[gc] = Node(-1,-1,tree[root].cnt+val);
        return gc;
    }
    int x = gc;
    tree[x]=Node(update(L,mid(L,R),tree[root].L,idx,val),update(mid(L,R)+1,R,tree[root].R,idx,val),tree[root].cnt+val);
    return x;
}

int query(int L , int R , int root , int qe , int qr)
{
    if(qr<L || qe>R)return 0;
    if(qe<=L && R<=qr)
        return tree[root].cnt;
    return query(L,mid(L,R),tree[root].L,qe,qr)+
            query(mid(L,R)+1,R,tree[root].R,qe,qr);
}

int main()
{
    int  M , i , x , y , z;
    N  = fastscan();
    memset(G,-1,sizeof(G));
    for(i=1;i<=N;++i){A[i]=fastscan();}
    root[0] = build(1,N);
    for(i=1;i<=N;++i)
    {
        int p = root[i-1];
        if(G[A[i]]!=-1)
            p = update(1,N,p,G[A[i]],-1);
        root[i] = update(1,N,p,i,1);
        G[A[i]]=i;
    }
    M  = fastscan();

    for(;M;--M)
    {
        x = fastscan();
        y = fastscan();
        printf("%d\n",query(1,N,root[y],x,y));
    }

    return 0;
}
