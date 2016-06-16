#include<bits/stdc++.h>
using namespace std;
#define mid(L,R) ((L+R)>>1)
vector < int > Adj[100001];
int vis[100001],level[100001],dp[20][100001],A[100001],root[100001],RM[100001],B[100001];
const int MAXLG = 20;
int gc = 0 , N;
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
int build(int L, int R)
{
    ++gc;
    if(L==R)
        return gc;
    int x  = gc;
    tree[x] = Node(build(L,mid(L,R)),build(mid(L,R)+1,R),0);
    return x;
}
void ini(int N)
{
    int i , j ;
    for(i=1;i<MAXLG;++i)
        for(j=1;j<=N;++j)
            dp[i][j] = dp[i-1][dp[i-1][j]];
    return ;
}
int LCA(int u , int v)
{
    if(level[u]>level[v])
        swap(u,v);

    int dif = level[v] - level[u] , i ;
    for(i=0;i<MAXLG;++i)
        if((dif>>i)&1)
            v = dp[i][v];
    if(u==v)return u;
    for(i=MAXLG-1;i>=0;--i)
        if(dp[i][v] && dp[i][v]!=dp[i][u])
            v=dp[i][v] , u=dp[i][u];
    return dp[0][u];
}
int update(int L , int R , int root , int idx)
{
    if(L>idx || R<idx)
        return root;
    ++gc;
    if(L==idx && R==idx)
    {
        tree[gc] = Node(-1,-1,tree[root].cnt+1);
        return gc;
    }
    int x = gc;
    tree[x] = Node(update(L,mid(L,R),tree[root].L,idx),update(mid(L,R)+1,R,tree[root].R,idx),tree[root].cnt+1);
    return x;
}

void dfs(int u)
{
    vis[u] = 1;

    root[u] = update(0,N-1,root[dp[0][u]],B[u]);
    for(vector < int > ::iterator it=Adj[u].begin();it!=Adj[u].end();++it)
    {
        int v = *it;
        if(!vis[v])
        {
            level[v] = level[u]  + 1;
            dp[0][v] = u;
            dfs(v);
        }
    }
}
int query(int L , int R , int root1 , int root2 , int root3 , int root4 , int K)
{
    for(;L!=R;)
    {
        if(tree[tree[root1].L].cnt+tree[tree[root2].L].cnt-tree[tree[root3].L].cnt-tree[tree[root4].L].cnt>=K)
        {
            R = mid(L,R);
            root1=tree[root1].L;
            root2=tree[root2].L;
            root3=tree[root3].L;
            root4=tree[root4].L;
        }
        else
        {
            L = mid(L,R)+1;
            K-=tree[tree[root1].L].cnt+tree[tree[root2].L].cnt-tree[tree[root3].L].cnt-tree[tree[root4].L].cnt;
            root1=tree[root1].R;
            root2=tree[root2].R;
            root3=tree[root3].R;
            root4=tree[root4].R;
        }
    }
    return L;
}
#define gc getchar_unlocked
int fastscan()
{
    register int n=0;
    char ch=gc();
    for(;(ch<48||ch>57);ch=gc())
        ;
    for(;(ch>47&&ch<58);ch=gc())
        n=(n<<3)+(n<<1)+ch-48;
    return n;
}


int main()
{
//    ios::sync_with_stdio(0);cin.tie(0);
    int  M , i , x , y , z;
    N  = fastscan();
    M  = fastscan();

    vector < int > V;
    for(i=1;i<=N;++i){A[i]=fastscan();V.push_back(A[i]);}
    sort(V.begin(),V.end());
    for(i=1;i<=N;++i){B[i]=lower_bound(V.begin(),V.end(),A[i])-V.begin();RM[B[i]]=A[i];}
    for(i=0;i<N-1;++i)
    {
        x = fastscan();
        y = fastscan();
        Adj[x].push_back(y);
        Adj[y].push_back(x);
    }
    root[0] = build(0,N-1);
    dfs(1);
    ini(N);
    for(;M;--M)
    {
        x = fastscan();
        y = fastscan();
        z = fastscan();
        printf("%d\n",RM[query(0,N-1,root[x],root[y],root[LCA(x,y)],root[dp[0][LCA(x,y)]],z)]);
    }
    return 0;
}
