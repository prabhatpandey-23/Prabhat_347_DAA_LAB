#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 999999

void dijkstra(int G[MAX][MAX], int n, int startnode) {
    int distance[MAX], pred[MAX];
    int visited[MAX];
    int count, mindistance, nextnode, i, j;

    // Initialize distance, pred, and visited arrays
    for (i = 1; i <= n; i++) {
        distance[i] = G[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }

    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;

    while (count < n) {
        mindistance = INF;

        // Find the node at the minimum distance
        for (i = 1; i <= n; i++) {
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }
        }

        if (mindistance == INF) {
            break;
        }

        visited[nextnode] = 1;
        count++;

        // Update distances of neighboring nodes
        for (i = 1; i <= n; i++) {
            if (!visited[i]) {
                if (mindistance + G[nextnode][i] < distance[i]) {
                    distance[i] = mindistance + G[nextnode][i];
                    pred[i] = nextnode;
                }
            }
        }
    }

    // Print the header exactly matching the tab structure
    printf("Node\tDistance\tPath\n");

    // Print results for all nodes except the start node with proper spacing
    for (i = 1; i <= n; i++) {
        if (i != startnode) {
            if (distance[i] == INF) {
                // Matches "   1\t     INF\tNO PATH\n"
                printf("   %d\t     INF\tNO PATH\n", i);
            } else {
                // Matches "   2\t       4\t2<-1\n"
                printf("   %d\t       %d\t%d", i, distance[i], i);
                j = i;
                while (j != startnode) {
                    j = pred[j];
                    printf("<-%d", j);
                }
                printf("\n");
            }
        }
    }
}

int main() {
    int G[MAX][MAX];
    int n, edges, i, j;
    int src, dest, weight, startnode;

    printf("Enter the number of vertices : ");
    if (scanf("%d", &n) != 1) return 0;

    printf("Enter the number of edges : ");
    if (scanf("%d", &edges) != 1) return 0;

    // Initialize graph adjacency matrix
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i == j) G[i][j] = 0;
            else G[i][j] = INF;
        }
    }

    // Read all edges
    for (i = 0; i < edges; i++) {
        printf("Enter source : ");
        scanf("%d", &src);
        printf("Enter destination : ");
        scanf("%d", &dest);
        printf("Enter weight : ");
        scanf("%d", &weight);
        G[src][dest] = weight;
    }

    printf("Enter the source :");
    if (scanf("%d", &startnode) != 1) return 0;

    dijkstra(G, n, startnode);

    return 0;
}
