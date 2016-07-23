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

};

int main()
{
    srand(time(0));
    ios::sync_with_stdio(0);
    BST < int > st;
    int N = 10099, i ;
    vector < int > V;
    for(i=0;i<N;++i)
        V.push_back(rand());
    sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    for(auto v:V)
        st.add(v);
    st.inorder();
    random_shuffle(V.begin(),V.end());

    for(auto v:V)
    {
        cout<<v<<":\n";
        st.inorder();
        cout<<'\n';
        cout<<st.lower_bound(v)<<'\n';
        cout<<st.upper_bound(v)<<'\n';
        cout<<st.inorder_predecessor(st.upper_bound(v))<<'\n';
        cout<<"\n\n";
    }



    return 0;
}
