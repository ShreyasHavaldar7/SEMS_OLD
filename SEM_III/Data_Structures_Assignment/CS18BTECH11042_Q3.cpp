#include <iostream>
#include <sstream>
#include <string.h>

#define f(i,k,j) for(int i=k; i<j; i++)

using namespace std;

class Graph{ // Class to implement basic directed graph required by using adjacency matrix representaion

    public:
    int **mat;
    int n;
    
    Graph(int n) { // Constructor to initialize adjacency matrix
        this->n=n;
        mat = new int*[n];
        f(i,0,n) {
            mat[i] = new int[n];
        }

        f(i,0,n) {
            f(j,0,n) {
                mat[i][j] = -1;
            }
        }
    }

    bool edgeCheck(int u, int v) { // Function to check if edge exists
        if(mat[u][v]!=-1) {
            return true;
        } else {
            return false;
        }
    }

    void neighbours(int u) { // Prints all incoming and outgoing neighbours

        f(i,0,n) {
            if(mat[u][i]!=-1) {
                cout << i<< " ";
            }
        }
        f(i,0,n) {
            if(mat[i][u]!=-1) {
                cout << i<< " ";
            }
        }
        cout<<"\n";
    } 

    void edgeWeight(int u, int v) { // Prints the edge weight if edge exists else prints that edge does not exist
        if(mat[u][v]!=-1) {
            cout <<  mat[u][v]<<"\n";
        } else {
            cout << "No edge exists\n";
        }
    }

    void insert(int u, int v, int w) { // Inserts the edge weight in the adjacency matrix

        mat[u][v] = w;
    }


};

int main(){

    int n; string p;
    getline(cin, p); // Taking input of the no of vertices and assuming vertices numbered 0 to n-1
    istringstream ss0(p);
    ss0>>n;
    Graph g1(n); // Creating graph object with n vertices
    string s;

    while(getline(cin,s)) { // Taking functionality input till 2 newline not encountered
        if(s.length()==0) {
            break;
        }
        istringstream ss(s);
        char ch;
        int u,v,w;
        ss>>ch;
        switch(ch) {
            case 'E': case 'e': // Inserting an edge on first letter E or e
                ss >>u>>v>>w;
                g1.insert(u,v,w); //(AS DIRECTED GRAPH ONLY U->V considered a edge but both are neighbours of each other)
                break;
            case 'N': case 'n': // Printing neighbours of the given vertex u on first letter N or n
                ss >> u;
                g1.neighbours(u);
                break;     
            case 'V': case 'v': // Printing if the vertex exists in the graph on first letter V or v
                ss >> u;
                if(u>=n) {
                    cout <<"NO\n";
                } else {
                    cout <<"YES\n";
                }
                break; 
            case 'W': case 'w': // Printing weight of edge between 2 vertices if it exists on first letter W or w 
                ss >> u >>v;
                g1.edgeWeight(u,v);
                break; 
            case 'C': case 'c': // Checks if edge exists between 2 vertices on first letter c or C
                ss >> u >> v;
                if(g1.edgeCheck(u,v)==true) {
                    cout<<"YES\n";
                } else {
                    cout<<"NO\n";
                }
                break; 
            case 'R': case 'r': // Returns list of all vertices in the graph on first letter r or R
                f(i,0,n) {
                    cout<<i<<" ";
                }
                cout<<"\n";
                
                break;
            default:
                cout<< "Wrong Input Format\n";

        }

    
    }
    
    
    return 0;
}