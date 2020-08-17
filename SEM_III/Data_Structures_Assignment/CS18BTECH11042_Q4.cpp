#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <limits.h>
#include <string.h>

#define f(i,k,j) for(int i=k; i<j; i++)

using namespace std;
 
struct edge { // Struct to store edge vertices and weight
    int u;
    int v;
    int w;
};

class Graph { // Class to implement undirected graph for part a as well as directed graph for part b
    public:
    int n;
    vector<pair<int, int>> *adj; // For undirected graph adjacency vectors of each vertex
    vector<edge> edges; //Vector of all edges
    vector<pair<int, int>> *dir_adj; // For directed graph adjacency vectors of each vertex
    
    vector<int> *comp; 

    Graph(int n){
        this->n = n;
        adj = new vector<pair<int, int>>[n];
        dir_adj = new vector<pair<int, int>>[n];
        comp = new vector<int>[n];

    }

    void addEdge(int u, int v, int w){ // For adding undirected edge for part a
        adj[v].push_back((make_pair(u,w)));
        adj[u].push_back((make_pair(v,w)));

        edge e;
        e.u=u;
        e.v=v;
        e.w=w;
        edges.push_back(e);

    }

    void addDirEdge(int u, int v, int w){ // For adding directed edge for part b

        dir_adj[u].push_back((make_pair(v,w)));
    }

    void Search(int v, int connect[], int count) { // Utility function to implement DFS
        
        connect[v] =1;
        comp[count].push_back(v);

        for(vector<pair<int, int>>::iterator it = adj[v].begin(); it!= adj[v].end(); it++) {
            if(connect[(*it).first]!=1) {
                Search((*it).first, connect, count);
            }
        }
    }

    void FindCompo() { // Function to find connected components in the graph
        int count=0;

        int connect[n]; // Initializing
        f(i,0,n) {
            connect[i] = 0;
        }
        f(i,0,n) { // Recursively seraching
            if(connect[i]==0) {
                Search(i, connect, count);
                count++;
            }
        }
        cout<<count<< " component(s) \n"; // No. of components
        f(i,0,count) {
            for(vector<int>::iterator it = comp[i].begin(); it!= comp[i].end(); it++) {
                cout << (*it) << " ";
            }
            cout << "\n";
        }



    }

    void ShortestPath(int S) { // Main function to find shrtest pasth from source S

        priority_queue<pair<int,int>, vector<pair<int, int>>, greater<pair<int,int>>> Q; // Priority queue to store visited vertices
        vector<int> d(n, INT_MAX);

        d[S] = 0; int count=1;
        Q.push(make_pair(0, S));

        while(Q.empty()==false) {

            int v = Q.top().second;
            Q.pop();

            for(vector<pair<int, int>>::iterator it = dir_adj[v].begin(); it!= dir_adj[v].end(); it++) {
                
                if(d[(*it).first] > d[v] + (*it).second) {
                    d[(*it).first] = d[v] + (*it).second;
                    Q.push(make_pair(d[(*it).first],(*it).first));
                    count++;
                }
            }
        }

        f(i,0,n) { // Printing shortest distance to every connected vertex i from S
            if(d[i]!=INT_MAX) { 
                cout<<S<<" "<<i<< " " << d[i] << "\n";
            }
        }
    }
};

int main() {

    int n; string p;  // Taking input of the no of vertices and assuming vertices numbered 0 to n-1 
    getline(cin, p);
    istringstream ss0(p);
    ss0>>n;

    Graph g1(n); // Creating graph object with n vertices
    edge e; int u,v,w; edge t; int S=0;
    string s;

    while(getline(cin,s)) { // Taking functionality input till 2 newline not encountered
        if(s.length()==0) {
            break;
        }
        istringstream ss(s);
        char ch; string t;
        int u,v,w;
        ss>>t;
        ch=t[0];
        switch(ch) {
                case 'E': case 'e': //Inserting an edge in the graph
                    ss >>u>>v>>w;
                    g1.addEdge(u,v,w);
                    g1.addDirEdge(u,v,w);
                    break;
                case 'F': case 'f': // First letter must be F or f for finding connected components
                    g1.FindCompo(); // Order of vertices in the components may be different for different cases
                    break;     
                case 's': case 'S': // First letter s or S for finding shortest path distance from vertex S 
                    ss >> S;
                    g1.ShortestPath(S);
                    break;
        }
    }

    return(0);

}

