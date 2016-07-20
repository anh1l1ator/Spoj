#include<bits/stdc++.h>
using namespace std;
template < class T>
class PriorityQueue
{
    vector < T > A;
    int idx;
    bool (*cmp)(T &B , T & D);
    public:
    PriorityQueue(int x): idx(1) {A.resize(x);cmp=NULL;}
    PriorityQueue(int x,bool (*y)(T &B , T & D)): idx(1) {A.resize(x);cmp=y;}
    void push(T v)
    {
        A[idx] = v;
        int x= idx;
        ++idx;
        for(;x>1 &&(cmp==NULL?A[x]<A[x/2]:cmp(A[x],A[x/2]));x/=2){
            swap(A[x],A[x/2]);
        }
    }
    bool empty()
    {
        return idx<=1;
    }
    T top()
    {
        assert(idx>1);
        return A[1];
    }
    void pop()
    {
        A[1]=A[idx-1];
        --idx;
        int x = 1;
        for(;x<idx;)
        {
            int save = x;
            if(2*x<idx && (cmp==NULL?(A[2*x] < A[save]):cmp(A[2*x],A[save])))save = 2*x;
            if(2*x+1<idx && (cmp==NULL?(A[2*x+1] < A[save]):cmp(A[2*x+1],A[save])))save = 2*x+1;
            if(save==x)break;
            swap(A[x],A[save]);
            x = save;
        }
    }
};

bool cmp(int &A , int &B){
    return A>B;
}
//Example Usage
int main()
{
    PriorityQueue < int > Q(200,cmp);
    int i;
    for(i=1;i<=10;++i)
        Q.push(rand()%10);
    while(!Q.empty())
    {
        cout<<Q.top()<<" ";
        Q.pop();
    }
    cout<<'\n';
    cout<<'\n';
    PriorityQueue < int > Q1(200);
    for(i=1;i<=10;++i)
        Q1.push(rand()%10);
    while(!Q1.empty())
    {
        cout<<Q1.top()<<" ";
        Q1.pop();
    }

    return 0;
}
