
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

bool pathCheck(Graph g, int src, int dest);
bool pathExist(Graph g, int src, int dest, bool* visited);

int numReachable(Graph g, int src) {
	// TODO
	int count = 0;
	
	for (int i = 0; i < GraphNumVertices(g); i++) {
	    if (pathCheck(g, src, i)) count++;
	}
	
	return count;
}

bool pathCheck(Graph g, int src, int dest) {
    int size = GraphNumVertices(g);
	bool *visited = malloc(sizeof(bool) * size);
	for (int i = 0; i < size; i++) visited[i] = false;
	
	bool exists = pathExist(g, src, dest, visited);
	free(visited);
	return exists;
}

bool pathExist(Graph g, int src, int dest, bool* visited) {
    for (int i = 0; i < GraphNumVertices(g); i++) {
        if (GraphIsAdjacent(g, src, i) || src == i) {
            if (visited[i] == false) {
                visited[i] = true;
                
                if (i == dest) return true;
                else if (pathExist(g, i, dest, visited)) return true;
            }
        }
    }   
    return false;
}
