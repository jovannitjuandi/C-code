void breadthFirst(Graph g, Vertex v)
{
   int *visited = calloc(g->nV, sizeof(int));
   Queue q = newQueue();
   QueueJoin(q, v);
   while (QueueLength (q) > 0) {
      Vertex x = QueueLeave(q);
      if (visited[x])
         continue;
      visited[x] = 1;
      printf("%d\\n", x);
      for (Vertex y = 0; y < g->nV; y++) {
         if (!g->edges[x][y])
            continue;
         if (!visited[y])
            QueueJoin(q, y);
      }
   }
}

void depthFirst(Graph g, Vertex v)
{
   int *visited = calloc(g->nV, sizeof(int));
   Stack s = newStack();
   StackPush(s, v);
   while (!StackIsEmpty (s)) {
      Vertex x = StackPop(s);
      if (visited[x])
         continue;
      visited[x] = 1;
      printf("%d\\n", x);
      for (Vertex y = g->nV - 1; y >= 0; y--) {
         if (!g->edges[x][y])
            continue;
         if (!visited[y])
            StackPush(s, y);
      }
   }
}
