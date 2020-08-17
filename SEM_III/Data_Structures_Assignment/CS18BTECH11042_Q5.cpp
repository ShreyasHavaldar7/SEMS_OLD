#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>

#define f(i,k,j) for(int i=k; i<j; i++)

using namespace std;

struct node { // Stores each node of tree with pointer to its representative parent and its rank
    int p;
    int rank;
};

struct edge { // Struct to store edge vertices and weight
    int u;
    int v;
    int w;
};

class DisjointSet // Class to implement disjoint set data strucutre with union find data structure as tree with rank based implementation
{
    public:
    node** nd; int size=0;

    DisjointSet(int n) { // Allocating memory equal to no of vertices
        nd = (node**)(malloc((n)*sizeof(node)));
        size=n;
        MakeSet();

    }

    void MakeSet() { // Creating n sets corresponding to the n vertices
        
        f(i,0,size) {
            nd[i] = new node;
            nd[i]->p = i;
            nd[i]->rank = 0;

        }
    }

    void UnionByRank(int x, int y) { // Performing union of two sets using rank based heuristics

        int px = FindSet(x);
        int py = FindSet(y);

        if(px==py) { // Checking the representative element of the set
            return;
        }

        if (nd[px]->rank<nd[py]->rank) {

            nd[px]->p = py;

        } else if (nd[px]->rank>nd[py]->rank) {

            nd[py]->p = px;

        } else {

            nd[py]->p = px;
            nd[px]->rank += 1; 

        }
    }

    int FindSet(int i) { // Function to recursively find the representative element of the vertex i

        if(nd[i]->p==i) {
            return i;
        } else {
            return FindSet(nd[i]->p);
        }
    }
};

int main() {

    int n; string p;  // Taking input of the no of vertices and assuming vertices numbered 0 to n-1 
    getline(cin, p);
    istringstream ss0(p);
    ss0>>n;
    DisjointSet ob(n); // Creating an object of data structureof disjoint set

    vector<edge> edges;

    edge e; int u,v,w; edge t; // Utility variables to store input
    string str;
        while(getline(cin, str)) { // Taking input of edges until 2 newlines are encountered
                edge e;
                if(str.length()==0)
                    break;
                istringstream ss(str);
                char q;
                ss >> q;
                ss >> e.u >> e.v >> e.w;
                edges.push_back(e); // Adding edges to the vector of edges
        }

    
    f(i, 0, edges.size()) { // Sorting the edges according to their weight in ascending order
        f(j, i+1, edges.size()) {
            if(edges[i].w>edges[j].w) {

                t = edges[i];
                edges[i] = edges[j];
                edges[j] = t;

            }
        }
    }

    vector<edge> mst; // Vector to store mst formed evcentually using Kruskals algorithm

    for(edge i: edges) { // If both vertices do not belong to same set add them to mst
        if(ob.FindSet(i.u)!=ob.FindSet(i.v)) {
            mst.push_back(i);
            ob.UnionByRank(i.u, i.v);
        }

    }
    if(mst.size()!=n-1) { // If no of edges in the mst is not equal to n-1 then it is not a mst, all edges are not connected
        cout<< "No MST exists\n";
    } else {
        for(edge i:mst) { // Printing edges seperated by whitespace who are a part of the mst
        cout << "(" << i.u << "," << i.v <<") ";    
        }
        cout<<"\n";
    }  
    return 0;  

}

