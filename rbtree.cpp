#include <iostream>
#define RED true
#define BLACK false
using namespace std;

template<class T1, class T2>
struct Node {
    T1 key;
    T2 val;
    Node *left, *right;
    bool color;
    Node(T1 k, T2 v, bool c):key(k), val(v), left(NULL), right(NULL), color(c){}
};

template<class T1, class T2>
class BSTree{
public:
    Node<T1, T2>* root;

    BSTree():root(NULL){}

    Node<T1, T2>* get_root(){
        return root;
    }

    T2 get(T1 key){
        Node<T1, T2> *cur = root;
        while(cur){
            if(key == cur->key) return cur->val;
            else if(key > cur->key) cur = cur->right;
            else cur = cur->left;
        }
        //cout<<"hre"<<endl;
        return (T2)NULL;
    }

    bool isRed(Node<T1, T2> *x){

        if(x == NULL) {return false;}
        return x->color == RED;
    }

    Node<T1, T2>* rotateLeft(Node<T1, T2> *h){
        Node<T1, T2> *x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = h->color;
        h->color = RED;
        return x;
    }

    Node<T1, T2>* rotateRight(Node<T1, T2> *h){
        Node<T1, T2> *x = h->left;
        h->left = x->right;
        x->right = h;
        x->color = h->color;
        h->color = RED;
        return x;
    }

    Node<T1, T2>* colorFlip(Node<T1, T2> *h){
        h->color = !h->color;
        h->left->color = !h->left->color;
        h->right->color = !h->right->color;
        return h;
    }

    Node<T1, T2>* insert_node(Node<T1, T2>*h, T1 key, T2 value){
        if(h == NULL)
        {
            return new Node<T1, T2>(key, value, RED);
        }
        if(isRed(h->left) && isRed(h->right)){
            h = colorFlip(h);
        }

        if(key == h->key){
            h->val = value;
        } else if(key > h->key){
            h->right = insert_node(h->right, key, value);

        } else {
            h->left = insert_node(h->left, key, value);
        }
        if(isRed(h->right)){
            h = rotateLeft(h);
        }

        if(h->left && isRed(h->left) &&isRed(h->left->left)){
            h = rotateRight(h);
        }

        return h;
    }


};

template<class T1, class T2>
class Map :public BSTree<T1, T2>{
public:
    Map(){
        BSTree<T1, T2>();
    }

    void insert(T1 key, T2 value){
        this->root = this->insert_node(this->root, key, value);
    }
};

template<class T1>
class Set : public BSTree<T1, T1> {
public:
    Set(){
        BSTree<T1, T1>();
    }

    void insert(T1 key){
        this->root = this->insert_node(this->root, key, key);
    }
};

int main()
{
    Map<int, string> *b = new Map<int, string>();
    /*b->root = b->insert_node(b->get_root(), 6, "her");
    b->root = b->insert_node(b->get_root(), 5, "his");
    b->root = b->insert_node(b->get_root(), 4, "him");
    b->root = b->insert_node(b->get_root(), 2, "wo");
    b->root = b->insert_node(b->get_root(), 1, "h");
    b->root = b->insert_node(b->get_root(), 5, "eee");
    b->insert(6, "her");
    b->insert(5, "his");
    b->insert(4, "him");
    b->insert(2, "wo");
    b->insert(1, "h");
    b->insert(5, "eee");
    cout<<b->get(5);*/

    Set<int> *s = new Set<int>();
    s->insert(6);
    s->insert(5);
    s->insert(4);
    s->insert(2);
    s->insert(1);
    s->insert(5);
    cout<<s->get(7);
    return 0;
}
