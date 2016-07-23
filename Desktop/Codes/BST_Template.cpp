#include<bits/stdc++.h>
using namespace std;

template < class T >
class BST
{
    struct Node
    {
        T data ;

        Node *left , *right ;
        Node(): data(-1),left(NULL),right(NULL) {}
        Node(int x): data(x),left(NULL),right(NULL) {}
    };
    Node *root;
    T INF ;
    public:
    BST(): root(NULL) {INF = numeric_limits<T>::max();}
    void Find(T foo  , Node *&X , Node*&Y)
    {
        Y = NULL , X = root;
        while(X!=NULL)
        {
            if(X->data == foo)return ;
            else if(X->data > foo){Y = X; X = X->left;}
            else
            {Y = X; X = X->right;}
        }
        return ;
    }
    void add(T key)
    {
        Node *X , *Y ;
        Find(key,X,Y);
        if(X!=NULL)return ;
        if(Y==NULL)
        {
            root = new Node(key);
            return ;
        }
        else
        {
            if(Y->data < key)
                Y->right = new Node(key);
            else
                Y->left  = new Node(key);
        }
    }
    void caseB(Node *X , Node *Y)
    {
        Node *P1 = X  , *H1 = X->right;
        while(H1->left)
        {
            P1 = H1;
            H1 = H1->left;
        }
        T save = H1->data;
        caseA(H1,P1);
        X->data = save;
    }
    void caseA(Node *X , Node *Y)
    {
        if(Y==NULL)
        {
            root = root->right?root->right:root->left;
            delete X;
        }
        else
        {
            if(Y->left == X)
                Y->left=X->right?X->right:X->left;
            else
                Y->right=X->right?X->right:X->left;
            delete X;
        }
    }
    void del_key(T key)
    {
        Node *X , *Y ;
        Find(key,X,Y);
        if(X==NULL)return ;
        if(X->left && X->right)
            caseB(X,Y);
        else
            caseA(X,Y);
    }
    void go(Node * r)
    {
        if(!r)return ;
        go(r->left);
        cout<<r->data<<" ";
        go(r->right);
    }
    void inorder()
    {
        go(root);
    }
    bool empty()
    {
        return root == NULL;
    }
    T lower_bound(T key)
    {
        T ret = INF;
        Node *X = root ;
        while(X!=NULL)
        {
            if(X->data < key )
                X = X->right;
            else
            {
                ret = X->data;
                X=X->left;
            }
        }
        return ret;
    }

    T upper_bound(T key)
    {
        T ret = INF;
        Node *X = root ;
        while(X!=NULL)
        {

            if(X->data <= key )
                X = X->right;
            else
            {
                ret = X->data;
                X=X->left;
            }
        }
        return ret;
    }

    T inorder_predecessor(T key)
    {
        T ret = INF;
        Node *X = root ;
        while(X!=NULL)
        {
            if(X->data < key )
            {
                ret = X->data;
                X = X->right;
            }
            else
            {
                X=X->left;
            }
        }
        return ret;
    }

    T begin()
    {
        if(!root)return INF;
        Node *H = root;
        while(H->left!=NULL)
        {
            H=H->left;
        }
        return H->data;
    }

    T end()
    {
        return INF ;
    }
    T next(T x)
    {
        return (*this).upper_bound(x);
    }
    T rbegin()
    {
        if(!root)return INF;
        return inorder_predecessor(INF);
    }
    T rnext(T x)
    {
        return (*this).inorder_predecessor(x);
    }
    bool rend(T x)
    {
        return x == (*this).begin();
    }
    T data()
    {
        return root->data;
    }
};

int main()
{
    srand(time(0));
    ios::sync_with_stdio(0);
    BST < int > st1 , st2;
    const int N = 10;

    st1.add(5);
    st1.add(1);
    st1.add(10);
    st1.add(0);
    st1.add(4);
    st1.add(7);
    st1.add(9);

    st2.add(10);
    st2.add(7);
    st2.add(20);
    st2.add(4);
    st2.add(9);

    int i = st1.begin();
    int j = st2.begin();



    for(;i!=INT_MAX && j!=INT_MAX;)
    {
        if(i>j)
        {
            j = st2.next(j);
        }
        else if(i<j)
        {
            i = st1.next(i);
        }
        else
        {
            cout<<i<<" ";
            i = st1.next(i);
            j = st2.next(j);
        }
    }


    return 0;
}
