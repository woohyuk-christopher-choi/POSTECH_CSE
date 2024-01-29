#include "graph.h"
#include <fstream>
#include <iostream>
#include <ratio>
#include <string>
#define INF 2147483647 
#define MAX_EDGES 10000
#define MAX_NODES 1000
using namespace std;


string Graph::DFS() {
    string visited[MAX_NODES];
    string result;
    int visitedNodes = 0;
    int connectedComponents = 0;

    for (int i = 0; i < totalNodes; i++) {
        visited[i] = "";
    }

    for (int j = 0; j < totalNodes; j++) {
        bool nodeVisited = false;
        for (int i = 0; i < visitedNodes; i++) {
            if (visited[i] == nodes[j]) {
                nodeVisited = true;
                break;
            }
        }

        if (nodeVisited) {
            continue;
        }

        connectedComponents++;
        string startNode = nodes[j];

        // Stack to perform DFS traversal
        string stack[MAX_NODES];
        int stackTop = -1;
        stack[++stackTop] = startNode;

        while (stackTop != -1) {
            string node = stack[stackTop--];

            bool isVisited = false;
            for (int i = 0; i < visitedNodes; i++) {
                if (visited[i] == node) {
                    isVisited = true;
                    break;
                }
            }

            if (!isVisited) {
                visited[visitedNodes++] = node;
                result += node + " ";

                // Find neighbors of the current node and add them to the stack
                string neighbors[MAX_NODES];
                int neighborsCount = 0;
                for (int i = 0; i < totalEdges; i++) {
                    if (edges[i].first == node || edges[i].second == node) {
                        string neighbor = (edges[i].first == node) ? edges[i].second : edges[i].first;
                        neighbors[neighborsCount++] = neighbor;
                    }
                }

                // Sort the neighbors in lexicographical order
                for (int i = 0; i < neighborsCount - 1; i++) {
                    for (int j = 0; j < neighborsCount - i - 1; j++) {
                        if (neighbors[j] > neighbors[j + 1]) {
                            string temp = neighbors[j];
                            neighbors[j] = neighbors[j + 1];
                            neighbors[j + 1] = temp;
                        }
                    }
                }

                // Add neighbors to the stack in reverse order to maintain lexicographical order during traversal
                for (int i = neighborsCount - 1; i >= 0; i--) {
                    stack[++stackTop] = neighbors[i];
                }
            }
        }

        result += "\n";
    }

    result = to_string(connectedComponents) + "\n" + result;

    
    if (!result.empty() && result[result.length() - 1] == '\n') {
        result = result.substr(0, result.length() - 1);
    }

    return result;
}


string Graph::BFS() {
    string visited[MAX_NODES];
    string queue[MAX_NODES];
    string result;
    int front = 0, rear = 0;
    int connectedComponents = 0;


    for(int i=0; i<totalNodes; i++){
        visited[i] = "";
        queue[i] = "";
    }

    for(int j = 0; j < totalNodes; j++){
        bool nodeVisited = false;
        for(int i=0; i<totalNodes; i++){
            if(visited[i] == nodes[j]){
                nodeVisited = true;
                break;
            }
        }

        if(nodeVisited){
            continue;
        }

        connectedComponents++;
        queue[rear++] = nodes[j];

        while (front != rear) {
            string node = queue[front++];

            bool isVisited = false;
            for(int i=0; i<totalNodes; i++){
                if(visited[i] == node){
                    isVisited = true;
                    break;
                }
            }

            if (!isVisited) {
                visited[totalNodes++] = node;
                result += node + " ";
                
                for (int i=0; i<totalEdges; i++) {
                    if (edges[i].first == node || edges[i].second == node) {
                        string neighbor = (edges[i].first == node) ? edges[i].second : edges[i].first;

                        // Find the correct position for the neighbor in the queue
                        int pos = front;
                        while (pos < rear && neighbor > queue[pos]) {
                            pos++;
                        }
                        
                        // Shift all elements to the right of pos to make space for the neighbor
                        for (int j = rear; j > pos; j--) {
                            queue[j] = queue[j - 1];
                        }

                        // Insert the neighbor at pos
                        queue[pos] = neighbor;
                        rear++;
                    }
                }
            }
        }

        result += "\n";
    }

    result = to_string(connectedComponents) + "\n" + result;

    if (!result.empty() && result[result.length() - 1] == '\n') {
        result = result.substr(0, result.length() - 1);
    }

    return result;
}



int Graph::addDirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    // Check if the edge already exists
    for (int i = 0; i < totalEdges; i++) {
        if (edges[i].first == nodeA && edges[i].second == nodeB) {
            return 0;
        }
    }

    // Add the nodes if they don't exist
    bool isANew = true;
    bool isBNew = true;
    for (int i = 0; i < totalNodes; i++) {
        if (nodes[i] == nodeA) {
            isANew = false;
        }
        if (nodes[i] == nodeB) {
            isBNew = false;
        }
    }
    if (isANew) {
        nodes[totalNodes++] = nodeA;
    }
    if (isBNew) {
        nodes[totalNodes++] = nodeB;
    }

    // Add the directed edge
    edges[totalEdges++] = make_pair(nodeA, nodeB);

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
	/////////////////////////////////////////////////////////
	//////////  TODO: Implement From Here      //////////////

    return 0;
	///////////      End of Implementation      /////////////
	///////////////////////////////////////////////////////
}


int Graph::addUndirectedEdge(string nodeA, string nodeB) {
    for (int i=0; i<totalEdges; i++) {
        if ((edges[i].first == nodeA && edges[i].second == nodeB) || (edges[i].first == nodeB && edges[i].second == nodeA)) {
            return 0;
        }
    }

    bool isAExist = false, isBExist = false;
    for(int i=0; i<totalNodes; i++){
        if(nodes[i] == nodeA) isAExist = true;
        if(nodes[i] == nodeB) isBExist = true;
    }

    if(!isAExist){
        int i = totalNodes - 1;
        while(i >= 0 && nodes[i] > nodeA) {
            nodes[i+1] = nodes[i];
            i--;
        }
        nodes[i+1] = nodeA;
        totalNodes++;
    }

    if(!isBExist){
        int i = totalNodes - 1;
        while(i >= 0 && nodes[i] > nodeB) {
            nodes[i+1] = nodes[i];
            i--;
        }
        nodes[i+1] = nodeB;
        totalNodes++;
    }

    edges[totalEdges++] = make_pair(min(nodeA, nodeB), max(nodeA, nodeB));

    return 0;
}


int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    // Check if the edge already exists
    for (int i = 0; i < totalEdges; i++) {
        if ((edges[i].first == nodeA && edges[i].second == nodeB) ||
            (edges[i].first == nodeB && edges[i].second == nodeA)) {
            return 0;
        }
    }

    // Add the nodes if they don't exist
    bool isANew = true;
    bool isBNew = true;
    int nodeAIndex = -1;
    int nodeBIndex = -1;

    for (int i = 0; i < totalNodes; i++) {
        if (nodes[i] == nodeA) {
            isANew = false;
            nodeAIndex = i;
        }
        if (nodes[i] == nodeB) {
            isBNew = false;
            nodeBIndex = i;
        }
    }
    if (isANew) {
        nodeAIndex = totalNodes;
        nodes[totalNodes++] = nodeA;
    }
    if (isBNew) {
        nodeBIndex = totalNodes;
        nodes[totalNodes++] = nodeB;
    }

    // Add the undirected edge with weight
    edges[totalEdges++] = make_pair(nodeA, nodeB);
    adjMatrix[nodeAIndex][nodeBIndex] = weight;
    adjMatrix[nodeBIndex][nodeAIndex] = weight;

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}





string Graph::StronglyConnectedComponent() {
    
    return "";
}


int Graph::getNodeIndex(string node) {
    for (int i = 0; i < totalNodes; i++) {
        if (nodes[i] == node) {
            return i;
        }
    }
    return -1;  // Node not found
}

string Graph::formatOutput(const string& output) {
    string formattedOutput;
    bool isFirstNode = true;

    for (char ch : output) {
        if (ch == '\n') {
            formattedOutput += ch;
            isFirstNode = true;
        } else if (ch != ' ') {
            if (!isFirstNode) {
                formattedOutput += ' ';
            }
            formattedOutput += ch;
            isFirstNode = false;
        }
    }

    return formattedOutput;
}



string Graph::getShortestPath_task5(string source, string destination) {
    // Check if the source and destination nodes exist
    int sourceIndex = -1, destIndex = -1;
    for (int i = 0; i < totalNodes; i++) {
        if (nodes[i] == source) {
            sourceIndex = i;
        }
        if (nodes[i] == destination) {
            destIndex = i;
        }
    }
    if (sourceIndex == -1 || destIndex == -1) {
        return "error";
    }

    // Dijkstra's algorithm
    int distance[MAX_NODES];
    string path[MAX_NODES];
    bool visited[MAX_NODES];

    for (int i = 0; i < totalNodes; i++) {
        distance[i] = INF;
        path[i] = "";
        visited[i] = false;
    }

    distance[sourceIndex] = 0;

    for (int count = 0; count < totalNodes - 1; count++) {
        int u = -1;
        int minDistance = INF;

        // Find the node with the minimum distance
        for (int i = 0; i < totalNodes; i++) {
            if (!visited[i] && distance[i] < minDistance) {
                minDistance = distance[i];
                u = i;
            }
        }

        if (u == -1) {
            break; // All remaining nodes are unreachable
        }

        visited[u] = true;

        // Update the distances and paths of the neighboring nodes
        for (int v = 0; v < totalNodes; v++) {
            if (!visited[v] && adjMatrix[u][v] != 0) {
                int newDistance = distance[u] + adjMatrix[u][v];
                if (newDistance < distance[v]) {
                    distance[v] = newDistance;
                    path[v] = path[u] + nodes[u] + " ";
                } else if (newDistance == distance[v]) {
                    string newPath = path[u] + nodes[u] + " ";
                    if (newPath < path[v]) {
                        path[v] = newPath;
                    }
                }
            }
        }
    }

    if (distance[destIndex] == INF) {
        return "error";
    }

    string shortestPath = path[destIndex] + nodes[destIndex];
    string output = shortestPath + " " + to_string(distance[destIndex]);
    return output;
}


string Graph::getShortestPath_task6(string source, string destination) {
    int sourceIndex = getNodeIndex(source);
    int destIndex = getNodeIndex(destination);
    if (sourceIndex == -1 || destIndex == -1) {
        return "INF";
    }

    int dist[NodeMaxCount][NodeMaxCount];
    int next[NodeMaxCount][NodeMaxCount];

    // Initialize distances with the adjacency matrix
    for (int i = 0; i < totalNodes; i++) {
        for (int j = 0; j < totalNodes; j++) {
            if (i == j) {
                dist[i][j] = 0;
                next[i][j] = -1;  // no next node for self-loop
            }
            else if (adjMatrix[i][j]) {
                dist[i][j] = adjMatrix[i][j];
                next[i][j] = j;  // next node is j if i and j are connected
            }
            else {
                dist[i][j] = INF;
                next[i][j] = -1;  // no next node if i and j are not connected
            }
        }
    }

    // Calculate shortest paths using dynamic programming
    for (int k = 0; k < totalNodes; k++) {
        for (int i = 0; i < totalNodes; i++) {
            for (int j = 0; j < totalNodes; j++) {
                if (i!=j && dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    if (dist[sourceIndex][destIndex] == INF) {
        return "INF";
    }

    // Path reconstruction
    int at = sourceIndex;
    string path = source;
    
    while (at != destIndex) {
        // Move to the next node based on the `next` array
        int nextNode = next[at][destIndex];

        // If no next node can be found, the shortest path doesn't exist.
        if (nextNode == -1) {
            return "INF";
        }

        // Add the next node to the path
        path += " " + nodes[nextNode];
        at = nextNode;
    }
    

    return path + " " + to_string(dist[sourceIndex][destIndex]);
}



int Graph::primMST(ofstream &fout, string startNode) {
    int startNodeIndex = getNodeIndex(startNode);
    if (startNodeIndex == -1) {
        fout << "MST: Invalid start node" << endl;
        return -1;
    }

    int inMST[NodeMaxCount];
    int key[NodeMaxCount];
    int parent[NodeMaxCount];

    for (int i = 0; i < totalNodes; i++) {
        inMST[i] = false;
        key[i] = INF;
        parent[i] = -1;
    }

    key[startNodeIndex] = 0;
    for (int count = 0; count < totalNodes - 1; count++) {
        int u = -1;
        for (int i = 0; i < totalNodes; i++) {
            if (!inMST[i] && (u == -1 || key[i] < key[u]))
                u = i;
        }

        inMST[u] = true;

        for (int v = 0; v < totalNodes; v++) {
            if (inMST[v] == false) {
                int weight = adjMatrix[u][v];

                if (weight != 0 && key[v] > weight) {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }
    }

    int totalWeight = 0;
    string paths[NodeMaxCount];  // 경로들을 저장하기 위한 배열
    int pathIndex = 0;

    for (int i = 0; i < totalNodes; i++) {
        if (i != startNodeIndex) {
            string path = "";
            int j = i;
            while (j != -1) {
                path = nodes[j] + (j == i ? "" : " ") + path;
                j = parent[j];
            }
            paths[pathIndex++] = path;  // 경로를 배열에 추가
            totalWeight += key[i];
        }
    }

    insertionSort(paths, pathIndex);  // 사전식 순서로 경로들을 정렬

    for (int i = 0; i < pathIndex; i++) {
        fout << paths[i] << "\n";  // 정렬된 경로들을 출력
    }

    return totalWeight;
}

void Graph::insertionSort(string arr[], int n) {
    for (int i = 1; i < n; i++) {
        string key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int Graph::kruskalMST(ofstream& fout, string endNode) {
    Edge* edgesList = new Edge[totalEdges];

    for (int i = 0; i < totalEdges; ++i) {
        edgesList[i] = {edges[i].first, edges[i].second, adjMatrix[getNodeIndex(edges[i].first)][getNodeIndex(edges[i].second)]};
    }

    sortEdges(edgesList, totalEdges);

    UnionFind uf(totalNodes);
    int cost = 0;
    string* parent = new string[totalNodes];
    string startNode = edgesList[0].node1 < edgesList[0].node2 ? edgesList[0].node1 : edgesList[0].node2;

    bool* inMST = new bool[totalNodes];
    for (int i = 0; i < totalNodes; ++i) {
        inMST[i] = false;
    }

    for (int i = 0; i < totalEdges; ++i) {
        Edge edge = edgesList[i];
        int idx1 = getNodeIndex(edge.node1);
        int idx2 = getNodeIndex(edge.node2);
        if (uf.find(idx1) != uf.find(idx2)) {
            fout << min(edge.node1, edge.node2) << " " << max(edge.node1, edge.node2) << " " << edge.weight << std::endl;
            uf.merge(idx1, idx2);
            cost += edge.weight;

            inMST[idx1] = true;
            inMST[idx2] = true;

            if (edge.node1 < edge.node2) {
                parent[idx2] = edge.node1;
            } else {
                parent[idx1] = edge.node2;
            }
        }
    }

    // Construct the path from startNode to endNode
    string path = endNode;
    while (endNode != startNode) {
        if (parent[getNodeIndex(endNode)].empty()) {
            fout << "No path exists from " << startNode << " to " << endNode << std::endl;
            delete[] edgesList;
            delete[] parent;
            delete[] inMST;
            return -1; // Or any suitable error code
        }
        endNode = parent[getNodeIndex(endNode)];
        path = endNode + " " + path;
    }

    fout << path << " " ;

    delete[] edgesList;
    delete[] parent;
    delete[] inMST;

    return cost;
}




void Graph::sortEdges(Edge* edges, int totalEdges) {
    for(int i = 0; i < totalEdges - 1; ++i) {
        for(int j = 0; j < totalEdges - i - 1; ++j) {
            bool shouldSwap = false;
            if(edges[j].weight > edges[j + 1].weight) {
                shouldSwap = true;
            } else if(edges[j].weight == edges[j + 1].weight) {
                if(edges[j].node1 > edges[j + 1].node1) {
                    shouldSwap = true;
                } else if(edges[j].node1 == edges[j + 1].node1 && edges[j].node2 > edges[j + 1].node2) {
                    shouldSwap = true;
                }
            }

            if(shouldSwap) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}
