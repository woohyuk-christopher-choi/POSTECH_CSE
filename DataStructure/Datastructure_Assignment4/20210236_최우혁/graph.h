#pragma once
#include <fstream>
#include <iostream>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647 
#define MAX_EDGES 10000
#define MAX_NODES 1000
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////
class UnionFind {
public:
    int* parent;
    int* rank;
    int n;

    UnionFind(int n) : n(n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }

    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void merge(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rootX != rootY) { // Unless x and y are already in same set, merge them
            parent[rootY] = rootX;
            ++rank[rootX];
        }
    }
};

struct Edge {
    std::string node1;
    std::string node2;
    int weight;
};
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph{
public:
    Graph() {
    for (int i = 0; i < NodeMaxCount; i++) {
        for (int j = 0; j < NodeMaxCount; j++) {
            adjMatrix[i][j] = 0;
        }
    }
    for (int i = 0; i < NodeMaxCount; i++) {
        nodes[i] = "";
    }
    for (int i = 0; i < MAX_EDGES; i++) {
        edges[i] = make_pair("", "");
    }
    totalEdges = 0;
    totalNodes = 0;
    };

    ~Graph() { };
    

    string DFS();
    string BFS();
    
    int addDirectedEdge(string nodeA, string nodeB);
    int addDirectedEdge(string nodeA, string nodeB, int weight);
    int addUndirectedEdge(string nodeA, string nodeB);
    int addUndirectedEdge(string nodeA, string nodeB, int weight);

    string StronglyConnectedComponent();

    string getShortestPath_task5(string source, string destination);
    string getShortestPath_task6(string source, string destination);
    int primMST(ofstream &, string startNode);
    int kruskalMST(ofstream &, string endNode);
    


private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    int adjMatrix[NodeMaxCount][NodeMaxCount];
    string nodes[NodeMaxCount];
    pair<string, string> edges[MAX_EDGES];
    int totalEdges = 0;
    int totalNodes = 0;
    int getNodeIndex(string node);
    void insertionSort(string arr[], int n);
    string formatOutput(const string& output);
    void sortEdges(Edge* edges, int totalEdges);
    void getSortedSCCs(string& result);
    ////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
