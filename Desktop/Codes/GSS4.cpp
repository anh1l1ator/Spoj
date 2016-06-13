#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL   A[100012];
int   L[100012];
int   R[100012];
LL tree[100012];
LL query(int idx)
{
    LL ret = 0;
    for(idx+=1;idx;idx-=idx&-idx)
        ret+=tree[idx];
    return ret;
}

void update(int idx , LL val)
{
    for(idx+=1;idx<=100011;idx+=idx&-idx)
        tree[idx]+=val;
}

int main()
{

    ios::sync_with_stdio(0);cin.tie(0);
    int N ,e = 1;
    while(cin>>N)
    {
        cout<<"Case #"<<e<<":\n";
        int Q, i , x , y , type;
        for(i=0;i<100012;++i)tree[i] = 0;
        set < int > indices;
        for(i=0;i<N;++i)
        {
            cin>>A[i];
            indices.insert(i);
            L[i] = i-1;
            R[i] = i+1;
            update(i,A[i]);
//            cout<<A[i]<<" "<<query(i)-query(i-1)<<'\n';
        }
//        cout<<endl;
        cin>>Q;
        int save;
        for(;Q;--Q)
        {

            cin>>type>>x>>y;
            --x;--y;
            if(x>y)swap(x,y);

            if(!type)
            {
                auto it = indices.lower_bound(x);
                if(it==indices.end())continue;
                int strt=*it;
                while(strt<=y)
                {
                    update(strt,-A[strt]);
                    A[strt] = (LL)sqrt(A[strt]);
                    update(strt,A[strt]);
                    if(A[strt]<=1)
                    {
                        if(L[strt]!=-1)
                            R[L[strt]]=R[strt];
                        if(R[strt]!=N)
                            L[R[strt]]=L[strt];
                        auto jt = indices.lower_bound(strt);

                        indices.erase(jt);
                    }
                    strt = R[strt];
                }
            }
            else
                cout<<query(y)-query(x-1)<<'\n';
        }
        cout<<'\n';++e;
//        return 0;
    }
    return 0;
}
