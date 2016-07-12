#include<bits/stdc++.h>
using namespace std;


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
        arr[indx-1]=val;
    }
};

//!Base indexing 0
//!Base indexing 0
//!Base indexing 0
//!Base indexing 0
//!Base indexing 0
//!Base indexing 0

int main()
{

    int N , Q , i ;
    scanf("%d%d",&N,&Q);
    vector < int > A(N);
    for(i=0;i<N;++i)scanf("%d",&A[i]);
    FenwickTree <int>tree0(N,A);
    for(;Q;--Q)
    {
        int x , y ;
        scanf("%d%d",&x,&y);
        --x;--y;
        printf("%d\n",tree0.query(x,y).first-tree0.query(x,y).second);
    }
    return 0;
}
