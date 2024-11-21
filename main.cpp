// COMSC-210 | 210-lab-32 | Daniil Malakhov
// IDE used: Codeblocks
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int SIZE = 7;  // Size of the graph (number of intersections)

struct Edge {
    int src, dest, weight;  // Intersection 'src' to 'dest' with 'weight' (traffic time/distance)
};

typedef pair<int, int> Pair;  // Alias for pair<int, int> (used for edge destination and weight)

class Graph {
public:
    vector<vector<Pair>> adjList;

    // Constructor to initialize the graph using edges
    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);  // Resizes adjacency list to hold SIZE elements (intersections)

        // Add edges to the adjacency list (represent roads between intersections)
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));  // Directed road from src to dest
            adjList[dest].push_back(make_pair(src, weight));  // For undirected graph (bidirectional roads)
        }
    }

    // Print the city's road network (adjacency list)
    void printGraph() {
        cout << "City's road network (Adjacency list):" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Intersection " << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(Intersection " << v.first << ", Time: " << v.second << " mins) ";
            cout << endl;
        }
    }

    // Perform Breadth-First Search (BFS) to find the shortest path by number of roads
    void BFS(int start, int end) {
        vector<bool> visited(SIZE, false);  // Track visited intersections
        vector<int> parent(SIZE, -1);  // To store the path
        queue<int> q;  // Queue for BFS
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            // If we reached the destination, trace the path
            if (current == end) {
                cout << "Shortest path (by number of roads) from " << start << " to " << end << ": ";
                vector<int> path;
                for (int v = end; v != -1; v = parent[v])
                    path.push_back(v);
                for (int i = path.size() - 1; i >= 0; i--)
                    cout << path[i] << " ";
                cout << endl;
                return;
            }

            // Visit all adjacent intersections
            for (const auto &neighbor : adjList[current]) {
                int neighborNode = neighbor.first;
                if (!visited[neighborNode]) {
                    visited[neighborNode] = true;
                    parent[neighborNode] = current;
                    q.push(neighborNode);
                }
            }
        }

        cout << "No path found from " << start << " to " << end << "." << endl;
    }

    // Add a road (edge) to the network
    void addEdge(int src, int dest, int weight) {
        adjList[src].push_back(make_pair(dest, weight));
        adjList[dest].push_back(make_pair(src, weight));  // For undirected road
    }
};

// Menu for the traffic management system
void showMenu() {
    cout << "\n--- Traffic Management System ---" << endl;
    cout << "1. View Road Network" << endl;
    cout << "2. Find Shortest Path (BFS)" << endl;
    cout << "3. Add New Road" << endl;
    cout << "4. Exit" << endl;
    cout << "----------------------------------" << endl;
    cout << "Enter your choice: ";
}

int main() {
    // Initial roads (edges) in the city with traffic time (weight)
    vector<Edge> edges = {
        {0, 1, 12}, {0, 2, 8}, {0, 3, 21}, {2, 3, 6}, {2, 6, 2},
        {5, 6, 6}, {4, 5, 9}, {2, 4, 4}, {2, 5, 5}
    };

    // Create the graph (city's road network)
    Graph graph(edges);
    int choice, startNode, endNode, src, dest, weight;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:  // View Road Network
                graph.printGraph();
                break;

            case 2:  // Find Shortest Path (BFS)
                cout << "Enter the start intersection (0 to " << SIZE - 1 << "): ";
                cin >> startNode;
                cout << "Enter the destination intersection (0 to " << SIZE - 1 << "): ";
                cin >> endNode;
                graph.BFS(startNode, endNode);
                break;

            case 3:  // Add New Road
                cout << "Enter source intersection: ";
                cin >> src;
                cout << "Enter destination intersection: ";
                cin >> dest;
                cout << "Enter the traffic time (in minutes) for this road: ";
                cin >> weight;
                if (src >= 0 && src < SIZE && dest >= 0 && dest < SIZE) {
                    graph.addEdge(src, dest, weight);
                    cout << "New road added successfully!" << endl;
                } else {
                    cout << "Invalid intersection numbers!" << endl;
                }
                break;

            case 4:  // Exit
                cout << "Exiting the Traffic Management System. Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
