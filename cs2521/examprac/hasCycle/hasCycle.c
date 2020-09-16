
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

bool dfs(Graph g, int v);
bool dfsCycleCheck (Graph g, int v, int u, bool* visited);

bool hasCycle(Graph g) {
	for (int i = 0; i < GraphNumVertices(g); i++) {
	    if (dfs(g, i)) return true;
	}
	return false;
}

bool dfs(Graph g, int v) {
    bool* visited = malloc(sizeof(bool) * GraphNumVertices(g));
    for (int i = 0; i < GraphNumVertices(g); i++) visited[i] = false;
    
    bool cycle = dfsCycleCheck (g, v, -1, visited);
    free(visited);
    return cycle;
}

bool dfsCycleCheck (Graph g, int src, int pred, bool* visited) {
    visited[src] = true;
    for (int w = 0; w < GraphNumVertices(g); w++) {
        if (GraphIsAdjacent(g, src, w)) {
            if (visited[w]) {
                if (w == src || w != pred) return true;
            } else if (dfsCycleCheck (g, w, src, visited)) return true;
        }
    }
    return false;
}
