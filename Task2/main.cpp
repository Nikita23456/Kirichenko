#include <iostream> 
#include <stack>
using namespace std;

struct Node
{
    int val;
    Node* l, * r;
    Node(int _val, Node* _l= NULL, Node* _r= NULL) : val(_val), l(_l), r(_r) {}
};

void printLTR(ostream& o, Node* c)
{
    if (c == NULL) return;
    printLTR(o, c->l);
    cout << c->val << " ";
    printLTR(o, c->r);
}
class FTree
{
    Node* root;

    pair<Node*, stack<Node*>> findKey(int key)
    {
        pair<Node*, stack<Node*>> res;
        res.first = NULL;
        if (root == NULL) return res;
        Node* t;
        t = root;
        if (t->val == key)
        {
            res.first = root;
            return res;
        }
        while (true)
        {
            if (t == NULL) return res;
            if (key > t->val)
            {
                res.second.push(t);
                t = t->r;
            }
            else if (key == t->val)
            {
                res.first = t;
                return res;
            }
            else
            {
                res.second.push(t);
                t = t->l;

            }
        }
        return res;
    }
    struct Node* deleteFromcurr(struct Node* curr, int key)
    {

        if (curr == NULL) return curr;


        if (key < curr->val)
            curr->l = deleteFromcurr(curr->l, key);


        else if (key > curr->val)
            curr->r = deleteFromcurr(curr->r, key);


        else
        {

            if (curr->l == NULL)
            {
                struct Node* temp = curr->r;
                delete(curr);
                return temp;
            }
            else if (curr->r == NULL)
            {
                struct Node* temp = curr->l;
                delete(curr);
                return temp;
            }


            struct Node* temp = minValueNode(curr->r);


            curr->val = temp->val;


            curr->r = deleteFromcurr(curr->r, temp->val);
        }
        return curr;
    }
public:
    FTree()
    {
        root = NULL;
    }

    bool contain(int key)
    {
        pair<Node*, stack<Node*>> res = findKey(key);
        return res.first != NULL;
    }
    void deleteNode(int key)
    {
        deleteFromcurr(root, key);
    }
    void add(int key)
    {
        pair<Node*, stack<Node*> > res = findKey(key);
        if (res.first != NULL) throw - 1;
        Node* p = new Node(key);
        if (root == NULL)
        {
            root = p;
            return;
        }
        Node* t = res.second.top();
        if (key > t->val)
        {
            t->r = p;
        }
        else
        {
            t->l = p;
        }
    }
    struct Node* minValueNode(struct Node* node)
    {
        struct Node* current = node;


        while (current && current->l != NULL)
            current = current->l;

        return current;
    }

    friend ostream& operator << (ostream& o, FTree& t);
};

ostream& operator << (ostream& o, FTree& t)
{
    printLTR(o, t.root);
    o << endl;
    return o;
}

int main()
{
    FTree tree;
    tree.add(10);
    tree.add(5);
    tree.add(20);
    tree.add(-1);
    tree.add(8);
    cout << tree;
    cout << "tree.contain(-1)" << tree.contain(-1) << endl;
    cout << "tree.contain(6)" << tree.contain(6) << endl;
    tree.deleteNode(5);
    cout << tree;
    return 0;
}
