#include<bits/stdc++.h>
using namespace std;
#define mid(L,R) ((L+R)/2)
#define lc(idx)  (2*idx+1)
#define rc(idx)  (2*idx+2)

/* This is simple usage of Persistent segment tree. Other approaches include merge sort tree, Fractional Cascading*/
int RM[100001];
struct Node{
    int cnt;
    int l , r;
    Node (int x , int y , int z)
    {
        cnt = x ;
        l = y ;
        r = z;
    }
    Node ()
    {
        cnt=   0 ;
        l  =  -1 ;
        r  =  -1;
    }
}tree[8600001];
int idx=0;
int build(int L , int R)
{
    ++idx;
    int x = idx;
    if(L==R)
        return x;
    tree[x].l = build(L,mid(L,R));
    tree[x].r = build(mid(L,R)+1,R);
    return x;
}

int update(int L , int R , int root , int qidx )
{
    if( R<qidx || L>qidx)
        return root;
    ++idx;
    int x = idx;
    if( R==qidx && L==qidx)
    {
        tree[x] = Node(tree[root].cnt+1,-1,-1);
        return x;
    }
    tree[x] = Node(tree[root].cnt+1,update(L,mid(L,R),tree[root].l,qidx),update(mid(L,R)+1,R,tree[root].r,qidx));
    return x;
}

int query(int L , int R , int root1 , int root2 , int K  )
{
    int x = L , y = R;
    for(;L!=R;)
    {
        if(tree[tree[root2].l].cnt-tree[tree[root1].l].cnt>=K)
        {
            R = mid(L,R);
            root1 = tree[root1].l;
            root2 = tree[root2].l;
        }
        else
        {
            L = mid(L,R)+1;
            K-=tree[tree[root2].l].cnt-tree[tree[root1].l].cnt;
            root1 = tree[root1].r;
            root2 = tree[root2].r;
        }
    }
    assert(x<=L && L<=y);
    return L;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N , M , i  ,x,y,z;
    cin>>N>>M;
    vector < int > A(N+1),V;
    vector < int > B(N+1);
    vector < int > root(N+1);
    A[0]=0;
    for(i=1;i<=N;++i){
        cin>>A[i];
        V.push_back(A[i]);
    }

    sort(V.begin(),V.end());
    for(i=1;i<=N;++i)
    {
        B[i] = lower_bound(V.begin(),V.end(),A[i])-V.begin();
        RM[B[i]] = A[i];
    }
    
    root[0] = build(0,N-1);
    for(i=1;i<=N;++i)
        root[i] = update(0,N-1,root[i-1],B[i]);
    for(;M;--M)
    {
        cin>>x>>y>>z;
        cout<<RM[query(0,N-1,root[x-1],root[y],z)]<<'\n';
    }

    return 0;
}
