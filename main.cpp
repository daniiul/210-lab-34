#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Alias for pair<int, int>

class Graph {
public:
    vector<vector<Pair>> adjList;

    // Constructor to initialize the graph using edges
    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);  // Resizes adjacency list to hold SIZE elements (7 for this case)

        // Add edges to the adjacency list
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight)); // For undirected graph
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    // Depth-First Search (DFS) using recursion
    void DFS(int start) {
        vector<bool> visited(SIZE, false);  // Track visited nodes
        cout << "DFS starting from node " << start << ": ";
        DFSUtil(start, visited);  // Helper function for DFS
        cout << endl;
    }

    // Helper function for DFS (recursive)
    void DFSUtil(int node, vector<bool> &visited) {
        visited[node] = true;  // Mark the node as visited
        cout << node << " ";    // Print the node

        // Recur for all the vertices adjacent to this node
        for (const auto &neighbor : adjList[node]) {
            int neighborNode = neighbor.first;
            if (!visited[neighborNode]) {
                DFSUtil(neighborNode, visited);
            }
        }
    }

    // Breadth-First Search (BFS) using a queue
    void BFS(int start) {
        vector<bool> visited(SIZE, false);  // Track visited nodes
        queue<int> q;  // Queue for BFS
        visited[start] = true;
        q.push(start);  // Start BFS from the given node

        cout << "BFS starting from node " << start << ": ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";  // Print the node

            // Visit all the neighbors of the current node
            for (const auto &neighbor : adjList[node]) {
                int neighborNode = neighbor.first;
                if (!visited[neighborNode]) {
                    visited[neighborNode] = true;
                    q.push(neighborNode);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Creates a vector of graph edges with weights
    vector<Edge> edges = {
        {0,1,12},{0,2,8},{1,3,6},{2,3,6},{2,6,2},{2,4,2},{5,6,6},{4,5,9},{3,0,2},{4,0,1},{6,3,2},{0,1,2},{5,4,12},{2,5,5}

    };

    // Create graph from edges
    Graph graph(edges);

    // Print adjacency list of the graph
    graph.printGraph();

    // Perform DFS and BFS
    graph.DFS(0);  // Start DFS from node 0
    graph.BFS(0);  // Start BFS from node 0

    return 0;
}
