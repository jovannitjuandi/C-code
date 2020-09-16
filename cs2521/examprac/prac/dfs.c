#include "dfs.h"

void dfs(Graph g, int src, bool *visited) {
    if (visited[src]) return;
    
    visited[src] = true;
    printf("%d ", src);
    
    for (int i = 0; i < GraphNumVertices(g); i++) {
        if (GraphIsAdjacent(g, src, i)) {
            dfs(g, i, visited);
        }
    }
}

void depthFirstSearch(Graph g, int src) {
	// TODO
	int size = GraphNumVertices(g);
	bool *visited = malloc(sizeof(bool) * size);
	for (int i = 0; i < size; i++) visited[i] = false;
	
	dfs(g, src, visited);
	
	free(visited);
}

