#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void bfs(int adj[MAX][MAX], int n, int start_vertex) {
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;

    printf("BFS of graph: \n");

    // Enqueue the start vertex and mark it as visited
    queue[rear++] = start_vertex;
    visited[start_vertex] = 1;

    while (front < rear) {
        // Dequeue a vertex from the queue
        int current_vertex = queue[front++];
        printf("%d\n", current_vertex);

        // Check all adjacent vertices of current_vertex
        // Vertices can be numbered from 1 to n (or 0 to n-1, standard loop covers 1 to n)
        for (int i = 1; i <= n; i++) {
            if (adj[current_vertex][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int n, edges;
    int adj[MAX][MAX] = {0};

    printf("Enter the number of vertices: ");
    if (scanf("%d", &n) != 1) return 0;

    printf("Enter the number of edges: ");
    if (scanf("%d", &edges) != 1) return 0;

    for (int i = 0; i < edges; i++) {
        int src, dest;
        printf("Enter source: ");
        scanf("%d", &src);
        printf("Enter destination: ");
        scanf("%d", &dest);
        
        // This sets up an unweighted directed graph based on the problem description
        adj[src][dest] = 1;
    }

    int start_vertex;
    printf("Enter Start Vertex for BFS: ");
    if (scanf("%d", &start_vertex) != 1) return 0;

    bfs(adj, n, start_vertex);

    return 0;
}
