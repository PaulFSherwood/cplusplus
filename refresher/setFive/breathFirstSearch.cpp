/*
   (0)----3                                            (0)----3
    |\                                                  |\
    | \         | 0 |   |   |   |   | Visited           | \         | 0 | 1 |   |   |   | Visited
    |  2        --------------------|                   |  2        --------------------|
    | / \       | 1 | 2 | 3 |   |   | Queue             | / \       | 2 | 3 |   |   |   | Queue
    |/   \                                              |/   \
    1-----4                                            (1)----4
*/
/*
   (0)----3                                            (0)---(3)
    |\                                                  |\
    | \         | 0 | 1 | 2 |   |   | Visited           | \         | 0 | 1 | 2 | 3 |   | Visited
    | (2)       --------------------|                   | (2)       --------------------|
    | / \       | 3 | 4 |   |   |   | Queue             | / \       | 4 |   |   |   |   | Queue
    |/   \                                              |/   \
   (1)----4                                            (1)----4
*/
// https://www.programiz.com/dsa/graph-bfs

#include <iostream>
#include <list>

class Graph {
    int numVerticies;
    list<int> *adjLists;
    bool *visited;

    public:
    Graph(int vertices);
    void addEdge(int src, int dest);
    void BFS(int startVertex);
};

// Create a graph with given vertices,
// and maintain and adjacency list
Graph::Graph(int vertices) {
    numVerticies = vertices;
    adjLists = new list<int>[vertices];
}

// Add edges to the graph
void Graph::addEdge(int src, int dest) {
    adjLists[src].push_back(dest);
    adjLists[dest].push_back(src);
}

// BFS algorith
void Graph::BFS(int startVertex) {
    visited = new bool(numVerticies);
    for (int i = 0; i < numVerticies; i++){
        visited[i] = false;
    }
}