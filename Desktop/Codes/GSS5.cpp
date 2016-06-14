#include<bits/stdc++.h>
using namespace std;

#define mid(l,r) (l+r)/2
#define lc(idx) (2*idx+1)
#define rc(idx) (2*idx+2)


vector < int > A(10001+1);
template <class T>
struct FenwickTree {
    T INF;
    int n;
	vector < vector < T >  > inter;
	vector < T > arr;
	FenwickTree(int N,vector < T > &A) {
        this->arr = A;
        inter.resize(2);
        inter[0].resize(N+1);
        inter[1].resize(N+1);
        INF = std::numeric_limits<T>::max();
        INF-=1e9+7;
        this->n = N;
        for (int i = 0; i <= n; ++i)
        {
            inter[1][i] = -INF;
            inter[0][i] = INF;
        }

        for (int i = 1; i <= n; ++i)
            update(i-1, arr[i-1]);
    }

	int ls(int indx){
        return indx & (-indx);
    }

    pair < T , T >  query(int l, int r)
    {

            ++l;++r;
            ++l;++r;

            T mx = -INF, mn = INF;
            while (r >= l)
            {
                while (r - ls(r) < l && r >= l)
                {
                    mx = max(mx, arr[r-1]);
                    mn = min(mn, arr[r-1]);
                    --r;
                }
                if (r >= l)
                    mx = max(mx, inter[1][r]), mn = min(mn, inter[0][r]);
                r -= ls(r);
            }
            return {mx ,mn};
    }

    void update(int indx, T val) {
        ++indx;

        T mx = val, mn = val;
        for (; indx <= n; indx += ls(indx)) {
        inter[1][indx] = mx = max(mx, inter[1][indx]);
		inter[0][indx] = mn = min(mn, inter[0][indx]);
        }
    }
};
struct Node
{
    int Left,Right,Sum,Best;
};
Node tree[8*10001];

Node join(Node a,Node b)
{
    Node temp;
    temp.Sum=a.Sum+b.Sum;
    temp.Left=max(a.Left,a.Sum+b.Left);
    temp.Right=max(b.Right,b.Sum+a.Right);
    temp.Best=max(a.Best,max(b.Best,a.Right+b.Left));
    return temp;
}
void create(int l,int r,int idx)
{
    if(l==r)
    {
        tree[idx].Left=tree[idx].Right=tree[idx].Sum=tree[idx].Best=A[l];
        return;
    }
    create(l,mid(l,r),lc(idx));
    create(mid(l,r)+1,r,rc(idx));
    tree[idx]=join(tree[lc(idx)],tree[rc(idx)]);
}
Node query(int l,int r,int qe,int qr,int idx)
{
    if(l==qe && qr==r)
        return tree[idx];
    Node y,z,w;
    if(mid(l,r)>=qr)
        return query(l,mid(l,r),qe,qr,lc(idx));
    else if (mid(l,r)<qe)
        return query(mid(l,r)+1,r,qe,qr,rc(idx));
    y=query(l,mid(l,r),qe,mid(l,r),lc(idx));
    z=query(mid(l,r)+1,r,mid(l,r)+1,qr,rc(idx));
    w=join(y,z);
    return w;
}
const int INF = (int)1e9;

int main()
{
    int T;
    cin>>T;
    for(;T;--T)
    {
        int N , i , Q , x1 ,x2 , y1 , y2 ;
        cin>>N;
        vector < int  > Pre(N+1);
        Pre[0] = 0;
        for(i=1;i<=N;++i)
        {
            cin>>A[i];
            Pre[i] = A[i] + Pre[i-1];
        }
        FenwickTree < int > tree0(N+1,Pre);
        create(1,N,0);
        cin>>Q;
        for(;Q;--Q)
        {
            cin>>x1>>y1>>x2>>y2;
            int ans = -INF;
            if(x2<=y1)
            {
                ans = max(ans,query(1,N,x2,y1,0).Best);
                if(y1!=y2)
                    ans = max(ans,tree0.query(y1,y2-1).first-tree0.query(x1-2,y1-2).second);
                ans = max(ans,tree0.query(x2-1,y2-1).first-tree0.query(x1-2,x2-2).second);
            }
            else
                ans = max(ans,tree0.query(x2-1,y2-1).first-tree0.query(x1-2,y1-2).second);
            cout<<ans<<'\n';
        }
    }
    return 0;
}
