#include<bits/stdc++.h>
using namespace std;

template < class T >
class Que
{
    template < class TT>
    struct Node
    {
        TT data;
        Node *Next , *Prev;
        Node(): Next(NULL),Prev(NULL) {}
    };

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
    ~Que()
    {
        while(!(*this).empty())
        {
            (*this).pop();
        }
    }
};
int main()
{
    Que < int > Q;
    int i;
    for(i=1;i<=10;++i)Q.push(i);
//    cout<<Q.top()<<" ";

    return 0;
}
