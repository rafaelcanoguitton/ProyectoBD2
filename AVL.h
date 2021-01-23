#include<iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;

vector<char> abc{'A','a','B','b','C','c','D','d','E','e','F','f','G','g','H','h','I','i','J','j','K','k','L','l','M','m','N','n','O','o','P','p','Q','q','R','r','S','s','T','t','U','u','V','v','W','w','X','x','Y','y','Z','z','_','0','1','2','3','4','5','6','7','8','9'};
class TipoInt{
public:
    inline bool operator()(int a, int b){return a<b;}
};
class TipoString{
public:
    inline bool operator()(string a, string b)
    {
        if(a.size()==b.size())
        {
            for(int i=0;i<a.size();i++)
            {
                char temp=a[i];
                char temp2=b[i];
                int cont1=0;
                int cont2=0;
                for(int j=0;j<abc.size();j++)
                {
                    if(temp=abc[j])
                    {
                        cont1=j;
                        j=abc.size();
                    }
                }
                for(int j=0;j<abc.size();j++)
                {
                    if(temp2=abc[j])
                    {
                        cont2=j;
                        j=abc.size();
                    }
                }
                if(temp>temp2)
                {
                    return true;
                }
                if(temp2>temp)
                {
                    return false;
                }
            }
        }
        if(a.size()>b.size())
        {
            for(int i=0;i<b.size();i++)
            {
                char temp=a[i];
                char temp2=b[i];
                int cont1=0;
                int cont2=0;
                for(int j=0;j<abc.size();j++)
                {
                    if(temp=abc[j])
                    {
                        cont1=j;
                        j=abc.size();
                    }
                }
                for(int j=0;j<abc.size();j++)
                {
                    if(temp2=abc[j])
                    {
                        cont2=j;
                        j=abc.size();
                    }
                }
                if(temp>temp2)
                {
                    return true;
                }
                if(temp2>temp)
                {
                    return false;
                }
            }
            return true;
        }
        if(a.size()<b.size())
        {
            for(int i=0;i<a.size();i++)
            {
                char temp=a[i];
                char temp2=b[i];
                int cont1=0;
                int cont2=0;
                for(int j=0;j<abc.size();j++)
                {
                    if(temp=abc[j])
                    {
                        cont1=j;
                        j=abc.size();
                    }
                }
                for(int j=0;j<abc.size();j++)
                {
                    if(temp2=abc[j])
                    {
                        cont2=j;
                        j=abc.size();
                    }
                }
                if(temp>temp2)
                {
                    return true;
                }
                if(temp2>temp)
                {
                    return false;
                }
            }
            return false;
        }
    }

};
template<class T, class C>
class BST
{
    struct node
    {
        T data;
        vector<int> dir;
        node* left;
        node* right;
        int height;
    };

    node* root;
    C cmp;
    void makeEmpty(node* t)
    {
        if(t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    node* insert(T x,int y, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->dir.push_back(y);
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if(t->data==x)
        {
            t->dir.push_back(y);
            //sort(t->dir.begin(), t->dir.end());
        }
        else if(cmp(x, t->data))
        {
            t->left = insert(x,y, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(cmp(x,t->left->data))
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(cmp(t->data,x))
        {
            t->right = insert(x,y, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if( cmp(t->right->data,x))
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }

        t->height = max(height(t->left), height(t->right))+1;
        return t;
    }

    node* singleRightRotate(node* &t)
    {
        node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(u->left), t->height)+1;
        return u;
    }

    node* singleLeftRotate(node* &t)
    {
        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(t->right), t->height)+1 ;
        return u;
    }

    node* doubleLeftRotate(node* &t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    node* doubleRightRotate(node* &t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(int x, node* t)
    {
        node* temp;

        // Element not found
        if(t == NULL)
            return NULL;

        // Searching for element
        else if(cmp(x,t->data))
            t->left = remove(x, t->left);
        else if(cmp(t->data,x))
            t->right = remove(x, t->right);

        // Element found
        // With 2 children
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        // With one or zero child
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right))+1;

        // If node is unbalanced
        // If left node is deleted, right case
        if(height(t->left) - height(t->right) == 2)
        {
            // right right case
            if(height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            // right left case
            else
                return doubleLeftRotate(t);
        }
        // If right node is deleted, left case
        else if(height(t->right) - height(t->left) == 2)
        {
            // left left case
            if(height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int height(node* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(node* t)
    {
        if(t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void inorder(node* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }
    void inorderFILL(node * t,string filename)
    {
        if(t == NULL)
            return;
        inorderFILL(t->left,filename);
        ofstream myfile(filename + ".idx", ios::app);
        myfile << t->data;
        for(int i=0;i<t->dir.size();i++)
        {
            myfile<< " "<<t->dir[i];
        }
        myfile<<endl;
        myfile.close();
        inorderFILL(t->right,filename);
    }
    vector<int> searchReg(node* root,T a)
    {
        if (root == NULL || root->data == a) 
            return root->dir;
        if (root->data < a)
            return searchReg(root->right, a);
        return searchReg(root->left, a);
    }

public:
    BST()
    {
        root = NULL;
    }

    void insert(T x,int y)
    {
        root = insert(x,y, root);
    }

    void remove(T x)
    {
        root = remove(x, root);
    }
    vector<int> searchRegi(T d)
    {
        return searchReg(root,d);
    }
    void display()
    {
        inorder(root);
        cout << endl;
    }
    void fill(string filename)
    {
        inorderFILL(root,filename);
    }
};
