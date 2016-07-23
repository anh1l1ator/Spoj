#include<bits/stdc++.h>
using namespace std;
template < typename T>
class BST
{
    struct Node
    {
        T data ;
        int ele ;
        Node *left , *right;
        Node(): ele(0),data(0),left(NULL),right(NULL){}
        Node(T x): ele(1),data(x),left(NULL),right(NULL){}
    };
    Node *root;
    public:
    BST(): root(NULL){}
    bool Find(T x)
    {
        Node *H = root ;
        while(H!=NULL)
        {
            if(H->data == x)
                return 1;
            if(H->data < x)
                H = H->right;
            else
                H = H->left;
        }
        return 0;
    }

    void push(T data)
    {
        if(root==NULL)
        {
            root = new Node(data);
            return ;
        }
        if((*this).Find(data))return ;
        Node *H = root , *prev = NULL;
        while(H!=NULL)
        {
            H->ele+=1;
            prev = H ;
            if(H->data < data)
                H = H->right;
            else
                H = H->left;
        }
        assert(prev);
        if(prev->data < data)
            prev->right = new Node(data);
        else
            prev->left  = new Node(data);
    }
    int size_of(Node *X)
    {
        if(!X)return 0;
        return X->ele;
    }

    T kTh(int k)
    {
        assert(k<=size_of(root));
        Node *H = root;
        while(k>0)
        {
            if(size_of(H->left) >= k)
                H = H->left;
            else if(size_of(H->left) < k)
            {
                k-=size_of(H->left);
                if(k==1)return H->data;
                k-=1;
                H = H->right;
            }
        }
        assert(0);
    }

    void del(Node *H , Node *prev)
    {
        if(H->left && H->right)
        {
            Node *X = H->right;
            Node *P2= H;
            while(X->left)
            {
                X->ele-=1;
                P2=X;
                X=X->left;
            }
            int data = P2->data;
            del(X,P2);
            H->data = data;
        }
        else
        {
            if(prev->data==-1)
            {
                root = root->right?root->right:root->left;
                delete H;
                return ;
            }
            if(prev->right==H)prev->right=H->right?H->right:H->left;
            else prev->left=H->right?H->right:H->left;
            delete H;
        }
    }

    void del_key(T x)
    {
        if(!Find(x))return;
        Node *H = root , *prev = new Node(-1);
        while(H->data!=x && H->data!=x)
        {
            H->ele-=1;
            prev = H ;
            if(H->data < x)
                H = H->right;
            else
                H = H->left;
        }
        assert(H);
        H->ele-=1;
        del(H,prev);
    }

    int size()
    {
        return size_of(root);
    }
    bool empty()
    {
        return size_of(root)>0;
    }
};
int main()
{
    srand(time(0));
    BST < int > tree;
    vector < int > V;
    const int N = 1e6;
    int i;
    for(i=0;;++i)
    {
        int x = rand()%3;
        if(x==0)
        {
            int y = rand();
            tree.push(y);
            if(!binary_search(V.begin(),V.end(),y))
            {
                V.push_back(y);
                sort(V.begin(),V.end());
            }
        }
        else
        {
            if(!tree.size())continue;
            int k = rand()%tree.size()+1;
            if(i%2)
            {
                tree.del_key(V[k-1]);
                V.erase(V.begin()+k-1,V.begin()+k);
            }
            else
            {
                if(tree.kTh(k)!=V[k-1])
                {
                    cout<<"ERROR\n";
                }
            }
        }
    }

//    tree.push(1);
//    tree.push(2);
//    tree.push(33);
//    tree.push(43);
//    tree.push(-1);
//    tree.del_key(1);
//    cout<<tree.kTh(1)<<'\n';
//    cout<<tree.kTh(2)<<'\n';
//    cout<<tree.kTh(3)<<'\n';
//    cout<<tree.kTh(4)<<'\n';
//    tree.del_key(33);
//    cout<<tree.kTh(1)<<'\n';
//    cout<<tree.kTh(2)<<'\n';
//    cout<<tree.kTh(3)<<'\n';
//    tree.del_key(43);
//    cout<<tree.kTh(1)<<'\n';
//    cout<<tree.kTh(2)<<'\n';
//    tree.del_key(-1);
//    cout<<tree.kTh(1)<<'\n';
//    tree.del_key(1);
//    tree.push(1);
//    tree.push(2);
//    tree.push(33);
//    tree.push(43);
//    tree.push(-1);
//    tree.del_key(1);
//    cout<<tree.kTh(1)<<'\n';
//    cout<<tree.kTh(2)<<'\n';
//    cout<<tree.kTh(3)<<'\n';
//    cout<<tree.kTh(4)<<'\n';
//    tree.del_key(33);
//    cout<<tree.kTh(1)<<'\n';
//    cout<<tree.kTh(2)<<'\n';
//    cout<<tree.kTh(3)<<'\n';
//    tree.del_key(43);
//    cout<<tree.kTh(1)<<'\n';
//    cout<<tree.kTh(2)<<'\n';
//    tree.del_key(-1);
//    cout<<tree.kTh(1)<<'\n';
//    tree.del_key(1);


    return 0;
}
