
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"
#include "Stack.h"

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

void depthFirstSearch(Graph g, int src)
{
    int size = GraphNumVertices(g);
    bool *visited = malloc(sizeof(bool) * size);
    for (int i = 0; i < size; i++) visited[i] = false;
    
    Stack s = StackNew();
    StackPush(s, src);
    
    while (!StackIsEmpty(s)) {
        int vertex = StackPop(s);
        if (visited[vertex]) continue;

        visited[vertex] = true;
        printf("%d ", vertex);
        
        for (int i = size - 1; i >= 0; i--) {
            if (GraphIsAdjacent(g, vertex, i)) {
                StackPush(s, i);
            }
        }
    }
}
