#include <iostream>
#include <string.h>
#include <sstream>

#define f(i,k,j) for(int i=k; i<j; i++)

using namespace std;


struct node{ // Struct to emulate a node storing the key, pointer to left child, pointer to right child, pointer to parent
    int key;
    node *l;
    node *r;
    node *p;

};

node* createNode(int val){ // Creating a node with key = value

    node* leaf = (node*)(malloc(sizeof(node)));
    leaf->key=val;
    leaf->l=NULL;
    leaf->r=NULL;
    leaf->p=NULL;
    return leaf;

}

node* searchKey(node* root, int key) { //Searching for the key within the whole tree by recursion and returning node which contains it

    if(root->key == key || root == NULL) {
        return root;
    } else if (root->key > key) {
        return searchKey(root->l, key);
    } else if (root->key < key) {
        return searchKey(root->r, key);
    }
}

node* insertKey(node* nd, int val){ // Inserting a key at its correct position by recursively traversing down the tree

    if(nd==NULL) {
        return createNode(val);
    }
    if(val> nd->key) {
        nd->r = insertKey(nd->r,val);
        (nd->r)->p = nd;
    } else {
        nd->l = insertKey(nd->l, val);
        (nd->l)->p = nd;
    }

return nd;

}

node* minKey(node* nd) { // returns node with min key of the subtree rooted at nd

    node* temp = nd;
    while(temp->l!=NULL) {
        temp = temp ->l;
    }
    return temp;
}

node* maxKey(node* nd) { // returns node with max key of subtree rooted at nd

    node* temp = nd;
    while(temp->r!=NULL) {
        temp = temp ->r;
    }
    return temp;
}

node* Successor(node* nd) { // Finds successor of nd recursively 

    if(nd->r!=NULL) {
        return minKey(nd->r);
    } else {
        node* temp = nd->p;
        while(temp!=NULL && nd == temp->r) {

            nd= temp;
            temp=temp->p;
        }
        return temp;
    }

    return NULL;


}
node* Predecessor(node* nd) { // Finds predecessor of nd recursively 

    if(nd->l!=NULL) {
        return maxKey(nd->l);
    } else {
        node* temp = nd->p;
        while(temp!=NULL && nd == temp->l) {

            nd= temp;
            temp=temp->p;   
        }
        return temp;
    }
    
    return NULL;

}

int depth(node* nd) { // Utility function to calculate depth of node for LowestCommonAncestor

    int dep=0;
    while(nd->p!=NULL) {
        dep++;
        nd = nd->p;
    }

    return dep;

}

node* LowestCommonAncestor(node* nd1, node* nd2) { // Function which utilizes the idea of bring nodes to same depth to check if parents match to find lowest common ancestor

    int dep1= depth(nd1);
    int dep2= depth(nd2);

    if(dep1==0) { // if anyone is the root it itslef is the lowest common ancestor
        return nd1;
    } else if(dep2==0) {
        return nd2;
    }

    int dif = dep1 - dep2;


    while(dif>0) {
        nd1 = nd1->p;
        dif--;
    }

    while(dif<0) {
        nd2 = nd2->p;
        dif++;
    }

    //now dif=0 so both nodes at same depth

    while(nd1->p!=NULL && nd2->p!=NULL) {
        if(nd1->p==nd2->p) {
            return nd1->p;
        } else {
            nd1 = nd1->p;
            nd2 = nd2->p;
        }

    }
}

int main(){

    int inp=0; char ch = ' '; string s; 
    node* root = NULL; int val=0; int val1=0; int val2=0;
    getline(cin, s);
    istringstream ss1(s);
    ss1>>val; // First value is the root
    root = createNode(val);

    while(ss1>>val) { // Taking all keys of the BST
        insertKey(root, val);

    }
    while(getline(cin, s)) { // Taking input till empty newline not encountered
        if(s.length()==0) {
            break;
        }
        istringstream ss(s);
        ss>> ch;
        ss>> val1;// node key
        switch (ch) // switch case to handle input possibilities
        {
        case 'M':
            cout<<(minKey(searchKey(root, val1)))->key<<" "<<(maxKey(searchKey(root, val1)))->key <<"\n";
            break;
        case 'P':
            cout<<(Predecessor(searchKey(root, val1)))->key<<"\n";
            break;
        case 'S':
            cout<<(Successor(searchKey(root, val1)))->key<<"\n";
            break;
        case 'C':
            ss>>val2;
            cout<<(LowestCommonAncestor(searchKey(root, val1),searchKey(root, val2)))->key<<"\n";
            break;        
        default:
            cout<<"Invalid Input";
            break;
        }


    }

    return 0;
}

