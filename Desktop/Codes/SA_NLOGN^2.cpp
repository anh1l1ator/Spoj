#include<bits/stdc++.h>
using namespace std;
// https://www.codechef.com/problems/INSQ16F
struct SA
{

    int N , MAXLG;
    vector < vector < int > > P;
    vector < pair < pair  < int , int > , int >  > L;
    vector < int > RMAP;
    string _S;
    void compute()
    {
        int i , j ;
        for(i=1;(1<<(i-1))<=N;++i);
        MAXLG = i;
        L.resize(N);
        RMAP.resize(N);
        P.resize(MAXLG);
        for(i=0;i<MAXLG;++i)P[i].resize(N);
        for(i=0;i<N;++i)
            P[0][i] = _S[i];
        for(i=1;i<MAXLG;++i)
        {
            for(j=0;j<N;++j)
                L[j] = {{P[i-1][j] , j+(1<<(i-1))<N?P[i-1][j+(1<<(i-1))]:-1} , j};
            sort(L.begin(),L.end());
            for(j=0;j<N;++j)
                P[i][L[j].second] = j>0 && L[j-1].first==L[j].first ? P[i][L[j-1].second] : j;
        }
        for(i=0;i<N;++i)
            RMAP[L[i].second]=i;
    }
    SA(string S):  _S(S)  {N = (S.length());compute();}
    int compute_LCP(int x , int y)
    {
        int ret =  0 ;
        if(x==y)return N - x;
        for(int i=MAXLG-1;i>=0 && x<N && y<N;--i)
            if(P[i][x]==P[i][y])
                ret+=(1<<i),x+=(1<<i),y+=(1<<i);
        return ret;
    }
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
    SA obj1(S);
    cin>>Q;
    for(;Q;--Q)
    {
        cin>>x>>y;
        --x ; --y ;
        int to_find = obj1.compute_LCP(A[x],A[y]);
        to_find = min({B[x],B[y],to_find});
        int Lee = 0 , R = min(obj1.RMAP[A[x]],obj1.RMAP[A[y]]) , M;
        while(Lee<R)
        {
            M = (Lee+R)/2;
            if(  obj1.compute_LCP(obj1.L[M].second, A[x]) >= to_find )
                R = M;
            else
                Lee = M + 1 ;
        }
        int left = Lee;
        Lee = max(obj1.RMAP[A[x]],obj1.RMAP[A[y]]) , R =  S.length()-1 ;
        while(Lee<R)
        {
            M = (Lee+R+1)/2;
            if(  obj1.compute_LCP(obj1.L[M].second , A[x]) >= to_find )
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
