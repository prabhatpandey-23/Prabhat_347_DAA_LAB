#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct {
    int u;
    int v;
    int w;
} Edge;

void bellmanFord(Edge edges[], int V, int E, int src)
{
    int dist[V + 1];
    int parent[V + 1];

    // Initialization
    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        int changed = 0;

        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INF &&
                dist[u] + w < dist[v]) {

                dist[v] = dist[u] + w;
                parent[v] = u;
                changed = 1;
            }
        }

        // Optimization: stop if no distance changed
        if (!changed)
            break;
    }

    // Check for negative weight cycle
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (dist[u] != INF &&
            dist[u] + w < dist[v]) {

            printf("Negative cycle detected\n");
            return;
        }
    }

    // Print shortest distances and paths
    for (int v = 1; v <= V; v++) {

        if (v == src)
            continue;

        if (dist[v] == INF) {
            printf("%d INF None\n", v);
        }
        else {
            int path[V + 1];
            int count = 0;
            int current = v;

            // Store path in reverse
            while (current != -1) {
                path[count++] = current;

                if (current == src)
                    break;

                current = parent[current];
            }

            printf("%d %d ", v, dist[v]);

            // Print path from source to destination
            for (int i = count - 1; i >= 0; i--) {
                printf("%d", path[i]);

                if (i != 0)
                    printf("->");
            }

            printf("\n");
        }
    }
}

int main()
{
    int V, E, src;

    scanf("%d", &V);
    scanf("%d", &E);

    Edge edges[E];

    for (int i = 0; i < E; i++) {
        scanf("%d %d %d",
              &edges[i].u,
              &edges[i].v,
              &edges[i].w);
    }

    scanf("%d", &src);

    bellmanFord(edges, V, E, src);

    return 0;
}
