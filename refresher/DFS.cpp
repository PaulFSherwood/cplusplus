// https://www.softwaretestinghelp.com/cpp-dfs-program-to-traverse-graph/
#include <iostream>
using namespace std;

// Step 1: Insert the root node or starting node of a tree or a graph in the stack
// Step 2: Pop item from the stack and add it to the visited list.
// Step 3: Find all the adjacent nodes of the node marked visited and add the ones that are not yet visited, to the stack.
// Step 4: Repeat steps 2 and 3 until the stack is empty.

// Procedure DFS(G, x)

// G->graph to be traversed
//
// x->start node
//
// begin
//
// x.visited = true
//
// for each v   G.Adj[x]
//
// if v.visited == false
//
// DFS(G, v)
//
// end procedure
//
// init() {
//
// For each x   G
//
// x.visited = false
//
// For each x    G
//
// DFS(G, x)
//
// }
