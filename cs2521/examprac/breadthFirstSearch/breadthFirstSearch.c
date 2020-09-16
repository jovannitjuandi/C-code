
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void breadthFirstSearch(Graph g, int src) {
	// TODO
	int size = GraphNumVertices(g);
	bool *visited = malloc(sizeof(bool) * size);
	for (int i = 0; i < size; i++) visited[i] = false;
	
	Queue q = QueueNew();
	QueueEnqueue(q, src);
	
	while (!QueueIsEmpty(q)) {
	    int vertex = QueueDequeue(q);
	    if (visited[vertex]) continue;
	    
	    visited[vertex] = true;
	    printf("%d ", vertex);
	    
	    for (int i = 0; i < size; i++) {
	        if (GraphIsAdjacent(g, vertex, i)) {
	            QueueEnqueue(q, i);
	        }
	    }
	}
	
	QueueFree(q);
	free(visited);
}

