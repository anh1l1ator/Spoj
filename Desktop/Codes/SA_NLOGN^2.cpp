#include<bits/stdc++.h>
// https://www.codechef.com/problems/INSQ16F
using namespace std;
struct SA
{
    vector < vector < int > > P;
    vector < vector < int > > dp;
    vector < pair < pair < int , int > , int > > L;
    vector < int >    RMAP , LG;
    int N  , i  , MAXLG  , j ;
    bool save ;
    string _S;
    void ini()
    {
        int i , j ;
        N = _S.length();
        for(i=1;(1<<i-1)<=N;++i);
        MAXLG = i;
        P.resize(MAXLG);
        RMAP.resize(N);
        for(i=0;i<MAXLG;++i)P[i].resize(N);
        L.resize(N);
        for(i=0;i<N;++i)P[0][i] = _S[i];
 
        for(i=1;i<MAXLG;++i)
        {
            for(j=0;j<N;++j)L[j] = {{P[i-1][j]  , j +  (1<<i-1) < N ? P[i-1][j+(1<<i-1)]:-1  }, j };
            sort(L.begin(),L.end());
            for(j=0;j<N;++j)
                P[i][L[j].second] = j!=0 && L[j].first==L[j-1].first ? P[i][L[j-1].second] : j;
        }
        for(i=0;i<N;++i)RMAP[L[i].second] = i ;
//        for(i=0;i<N;++i)
//            cout<<_S.substr(L[i].second,_S.length()-L[i].second)<<'\n';
    }
    int compute_LCP(int x , int y )
    {
        if(x==y)return N - x;
        int ret = 0 ;
        for(int k = MAXLG-1;k>=0 && x<N && y<N;--k)
            if(P[k][x]==P[k][y])
                x+=(1<<k) , y+=(1<<k) , ret+=(1<<k);
        return ret;
    }
 
    void compute_LCP()
    {
        int i , j ;
        dp.resize(MAXLG);
        LG.resize(N+1);
        for(i=0;i<MAXLG;++i)dp[i].resize(N);
        for(i=0;i<N-1;++i){
            dp[0][i] = compute_LCP(L[i].second,L[i+1].second);
        }
 
        LG[1] = 0;
        LG[0] = -1e9;
        for(i=2;i<=N;++i)LG[i] = LG[i/2]+1;
        for(i=1;i<MAXLG;++i)
            for(j=0;j<N-1;++j)
                dp[i][j] = min(dp[i-1][j] , (1<<i-1)+j<N-1?dp[i-1][(1<<i-1)+j]:0);
    }
 
    int query(int x , int y)
    {
        if(!save){
            cout<<"Send second parameter as 1\n\n";
            assert(0);
        }
        int L = x , R = y;
        assert(L<=R);
        return min(dp[LG[(R-L+1)]][L] , dp[LG[R-L+1]][R-(1<<LG[R-L+1])+1]);
    }
    int query_by_index(int x , int y)
    {
        if(x==y)return N - x;
        return query(min(RMAP[x],RMAP[y]),max(RMAP[x],RMAP[y])- 1);
    }
    SA(string S ,bool go = 0 ): _S(S) {ini();if(go)compute_LCP();save = go;}
};
 
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    string S = "", T;
    int N , i , Q , x , y;
    cin>>N;
    vector < int > A(N), B(N);
    for(i=0;i<N;++i)
    {
        cin>>T;
        A[i] = S.length() + (i!=0);
        B[i] = T.length();
        if(i!=0)
            T = "$" + T;
        S+=T;
    }
    SA obj1(S,1);
    cin>>Q;
    for(;Q;--Q)
    {
        cin>>x>>y;
        --x ; --y ;
        int to_find = obj1.query_by_index(A[x],A[y]);
        to_find = min({B[x],B[y],to_find});
        int Lee = 0 , R = min(obj1.RMAP[A[x]],obj1.RMAP[A[y]]) , M;
        while(Lee<R)
        {
            M = (Lee+R)/2;
            if(  obj1.query_by_index(obj1.L[M].second, A[x]) >= to_find )
                R = M;
            else
                Lee = M + 1 ;
        }
        int left = Lee;
        Lee = max(obj1.RMAP[A[x]],obj1.RMAP[A[y]]) , R =  S.length()-1 ;
        while(Lee<R)
        {
            M = (Lee+R+1)/2;
            if(  obj1.query_by_index(obj1.L[M].second , A[x]) >= to_find )
                Lee = M;
            else
                R = M - 1 ;
        }
        if(to_find==0)
            left = R +1;
        cout<<R-left+1<<'\n';
    }
    return 0;
}
 
