#include<bits/stdc++.h>
using namespace std;

const int nax = 1e6;

template < class T >
class PriorityQueue
{
    #define pi(x)  ((x)/2)
    #define lc(x)  (2*x)
    #define rc(x)  (2*x+1)
    vector < T > Q;
    int idx ;
    public:
    PriorityQueue() : idx(1) {Q.resize(nax);}

    void push(T x)
    {
        Q[idx] = x;
        int i = idx;
        ++idx;

        while(i>1 && Q[i]<Q[pi(i)])
        {
            swap(Q[i],Q[pi(i)]) ;
            i = pi(i);
        }
    }

    T top()
    {
        assert(idx>1);
        return Q[1];
    }

    bool empty()
    {
        return idx<=1;
    }

    void pop()
    {
        assert(idx>1);
        swap(Q[idx-1],Q[1]);
        --idx;
        for(int i=1;;)
        {
            int x = i;
            if(lc(i)<idx && Q[lc(i)]<Q[x])x = lc(i);
            if(rc(i)<idx && Q[rc(i)]<Q[x])x = rc(i);
            if(x==i)break;
            swap(Q[x],Q[i]);
            i = x;
        }
    }
    #undef pi
    #undef lc
    #undef rc
};





int main()
{
    ios::sync_with_stdio(0);cin.tie(0);

    int N , i  , x;
    PriorityQueue < int > Q;
    cin>>N;
    for(i=0;i<N;++i)
    {
        cin>>x;
        Q.push(x);
    }
    while(!Q.empty())
    {
        cout<<Q.top()<<" ";
        Q.pop();
    }
    cout<<'\n';
    return 0;
}

