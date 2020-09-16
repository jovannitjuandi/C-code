
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int shortestDistance(Graph g, int src, int dest);

int furthestReachable(Graph g, int src) {
	// TODO
	int *distance = malloc(sizeof(int) * GraphNumVertices(g));
	for (int i = 0; i < GraphNumVertices(g); i++) {
	    distance[i] = shortestDistance(g, src, i);
	}
	
	int max = distance[0];
	int index = 0;
	for (int i = 0; i < GraphNumVertices(g); i++) {
	    if (max <= distance[i]) {
	        max = distance[i];
	        index = i;
        }
	}   
	free(distance);
	return index;
}

int shortestDistance(Graph g, int src, int dest) {
	int size = GraphNumVertices(g);
	int *visited = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) visited[i] = -1;
	bool found = false;
	visited[src] = src;
	
	Queue q = QueueNew();
	QueueEnqueue(q, src);
	
	while (!QueueIsEmpty(q) && !found) {
	    int vertex = QueueDequeue(q);
	    if (vertex == dest) {
	        found = true;
	    } else {
	        for (int i = 0; i < size; i++) {
	            if (GraphIsAdjacent(g, vertex, i) && visited[i] == -1) {
	                visited[i] = vertex;
	                QueueEnqueue(q, i);
	            }
	        }
	    }
	}
	
    int count = 0;
	if (found) {
        int current = dest;
	    while (current != src) {
	        count++;
	        current = visited[current];
	    }
	}
	
	QueueFree(q);
	free(visited);
	
	if (found) return count;
	return -1;
}


