#include <iostream>
#include <string.h>
#include <sstream>

#define f(i,k,j) for(int i=k; i<j; i++)

using namespace std;

struct node { // Struct to store node attributes like key, count to denote the which occurence of the same key in the list, and pointer to next node.
    char key;
    int count;
    node *r;

};

class Big { // Class to emulate the data structure with necessary functions and attributes to deal with big strings input by the user
    public:
    int unique; int *a; int check=0; // Unique stores the no of unique elements in the list

    Big() { // Constructor to initialize variables

        a = new int[26]; // Array to store no of occurences of each letter
        unique = 0;
        f(i,0,26) {
            a[i] =0;
        }
    }

    node* createNode(char c){ // Function to create a node with given key c

        node* nd = (node*)(malloc(sizeof(node)));
        nd->key=c;
        nd->r=NULL;

        return nd;

    }

    void store(string s, node* head) { // To store all the created nodes in the singly linked list format

        node* nd = head; check = 1;
        f(i,1,s.length()) {
        nd->r=createNode(s[i]);
        nd = nd->r;
        }
        cout << head->key <<" "<< nd->key<<"\n"; // Printing first and last element of list
        nd = head;

        f(j,0,26) { // Calculating the no of occurences of each letter
            while(nd!=NULL) {
            if((int)(nd->key)==j+65) {
                a[j]++;
                nd->count=a[j];
            }
            nd = nd->r;
            }
            nd=head;
        }
        nd = head;
        while(nd!=NULL) { // Calculating the no of unique letters by counting only the first occurence if any of each letter
            if(a[(int)(nd->key)-65]!=0 && nd->count==1) {
            unique++;
        }
        nd=nd->r;

        }

    }

    void print(node* head) { // Printing each occuring letter followed by it's occurence in the list
        node* n=head;

        while(n!=NULL) {
            if(a[(int)(n->key)-65]!=0 && n->count==1) {
                cout << (n->key) << " " << a[(int)(n->key)-65] << " ";
            }
            n=n->r;
        }
        cout << "\n";
    

    }

    void sorter(node* head) { // Printing the letters in descending order of their occurence

        node* nd=head; int maxx; node* temp =NULL; maxx=0; int t[26];
        f(i,0,26) {
            t[i] = a[i];
        }

        f(i,0,unique) { // Printing only the unique letters so no repetition occurs
            while(nd!=NULL) {
                if(nd->count>maxx && t[(int)(nd->key)-65]!=0) {
                    maxx = nd->count;
                    temp=nd;
                }
                nd=nd->r;
            }
            t[(int)(temp->key)-65]=0;
            cout<<temp->key;
            maxx=0;
            nd=head;

        }
        cout<<"\n";

    }

    void remove(node* head, int t) { // Removing nodes with more same consecutive letters than t and also updating the linked list
        node* nd =head; node* temp;
        int c=1;
        while(nd->r!=NULL) {

            if(nd->r->key == nd->key) {
                c++;
            } else {
                c=1;
            }
            if(c>t) {
                temp = nd->r;
                if(temp->r!=NULL){
                    while(temp->r->key == temp->key) {
                        if(temp->r==NULL) {
                            break;
                        }
                        temp = temp->r;
                        if(temp->r==NULL) {
                            break;
                        }
                    }

                }
                nd->r = temp->r;
                c=1;
            
            }
            if(nd->r==NULL) {
                break;
            }

            nd=nd->r;

        
        }
        f(i,0,26) { // Initializing and then Updating the count of each letter
            a[i] =0;
        }

        nd = head;
        f(j,0,26) {
            while(nd!=NULL) {
                if((int)(nd->key)==j+65) {
                    a[j]++;
                    nd->count=a[j];
                }
            nd = nd->r;
            }
            nd=head;
        }

        node* n=head;

        while(n!=NULL) {  //Printing the new linked list formed after deletion of nodes         
            
                cout << (n->key);
                n=n->r;
        }
        cout << "\n";
    }
};

int main(){

    string s; string inp; 
    node* head =NULL; 
    
    Big lr; // Creating object lr of the Data Structures

    getline(cin,inp); // Taking the first string input which will be stored in the linked list. Assuming the entire string is in Uppercase.
    istringstream ss(inp);
    ss>>s;
    head=lr.createNode(s[0]); // Head node created

    while(getline(cin, inp)) { // Taking input till empty newline not encountered
        if(inp.length()==0) {
            break;
        }
        istringstream ss(inp);
        string in1;
        int x;
        ss>>in1;
        if(inp.length()==0)
            break;
        if(in1[0]=='S'||in1[0]=='s') { // First letter must be S or s for store function to be invoked 

            lr.store(s,head);

        } else if(in1[0]=='P'||in1[0]=='p') { // First letter must be p or P for print function to be invoked 

            if (lr.check ==1 ) lr.print(head);
            else cout << "Please Store First\n";

        } else if(in1[0]=='a'||in1[0]=='A') { // First letter must be A or a for ascend/sort function to be invoked 

            if (lr.check ==1 ) lr.sorter(head);
            else cout << "Please Store First\n";


        } else {

            if (lr.check ==1 ) { // All other cases are treated as remove unction to be invoked 
                ss>>x;
                lr.remove(head,x);
            } else {
                cout << "Please Store First\n";
            }

        }
    }

    return 0;

}