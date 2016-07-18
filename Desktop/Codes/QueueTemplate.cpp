#include<bits/stdc++.h>
using namespace std;
template < class T>
struct Node
{
    T data;
    Node *Next , *Prev;
    Node(): Next(NULL),Prev(NULL) {}
};
template < class T >
class Que
{
    Node  < T >  *rear , *front;
    public:
    Que(): rear(NULL) , front(NULL){}
    void push(T data)
    {
        if(rear==NULL){
            rear = front = new Node<T>;
            front->data = data;
            return ;
        }
        rear->Next = new Node<T>;
        rear->Next->Prev = rear;
        rear=rear->Next;
        rear->data = data;
        return ;
    }
    T top()
    {
        assert(front!=NULL);
        return front->data;
    }
    void pop()
    {
        assert(front!=NULL);
        if(front->Next==NULL){
            delete front;
            front = rear = NULL;
            return ;
        }
        front = front->Next;
        delete front->Prev;
    }
    bool empty()
    {
        return front==NULL;
    }
};

int main()
{
    Que < int > Q;
    int i;
    for(i=1;i<=10;++i)
        Q.push(i);
    while(!Q.empty())
    {
        cout<<Q.top()<<" ";
        Q.pop();
    }

    return 0;
}
