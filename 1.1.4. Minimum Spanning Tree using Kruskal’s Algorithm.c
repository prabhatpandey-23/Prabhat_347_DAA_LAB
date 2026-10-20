#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
struct Edge {
    int u, v, weight;
};

// Disjoint Set Union (DSU) functions for Cycle Detection
int findSet(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = findSet(parent, parent[i]);
}

void unionSets(int parent[], int rank[], int x, int y) {
    int rootX = findSet(parent, x);
    int rootY = findSet(parent, y);
    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// Comparator function to sort edges strictly as per constraints:
// 1. Ascending order of weights.
// 2. Tiebreaker: Row-wise order in the upper triangular part (u first, then v).
int compareEdges(const void *a, const void *b) {
    struct Edge *e1 = (struct Edge *)a;
    struct Edge *e2 = (struct Edge *)b;
    if (e1->weight != e2->weight) {
        return e1->weight - e2->weight;
    }
    if (e1->u != e2->u) {
        return e1->u - e2->u;
    }
    return e1->v - e2->v;
}

// Function to find and print the MST using Kruskal's Algorithm
void kruskalMST(int **cost, int V) {
    int edgeCount = 0;

    // 1. Calculate how many valid edges exist in the upper triangular matrix
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (cost[i][j] != 9999) {
                edgeCount++;
            }
        }
    }

    // 2. Allocate memory and store the edges
    struct Edge *edges = (struct Edge *)malloc(edgeCount * sizeof(struct Edge));
    int index = 0;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (cost[i][j] != 9999) {
                edges[index].u = i;
                edges[index].v = j;
                edges[index].weight = cost[i][j];
                index++;
            }
        }
    }

    // 3. Sort edges by weight and row-wise positioning
    qsort(edges, edgeCount, sizeof(struct Edge), compareEdges);

    // 4. Initialize Disjoint Set components
    int *parent = (int *)malloc(V * sizeof(int));
    int *rank = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int totalCost = 0;
    int mstEdgesCount = 0;

    // 5. Select V-1 edges to form the MST
    for (int i = 0; i < edgeCount && mstEdgesCount < V - 1; i++) {
        int rootU = findSet(parent, edges[i].u);
        int rootV = findSet(parent, edges[i].v);

        // If including this edge doesn't cause a cycle
        if (rootU != rootV) {
            printf("Edge %d:(%d, %d) cost:%d\n", mstEdgesCount, edges[i].u, edges[i].v, edges[i].weight);
            totalCost += edges[i].weight;
            unionSets(parent, rank, rootU, rootV);
            mstEdgesCount++;
        }
    }

    printf("Minimum cost= %d\n", totalCost);

    // Free local dynamic allocations
    free(edges);
    free(parent);
    free(rank);
}

// Driver code matching the exact standard configuration
int main() {
    int V;
    printf("No of vertices: ");
    if (scanf("%d", &V) != 1) return 0;

    printf("Adjacency matrix:\n");
    int **cost = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        cost[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    kruskalMST(cost, V);

    // Free dynamically allocated adjacency matrix
    for (int i = 0; i < V; i++) {
        free(cost[i]);
    }
    free(cost);

    return 0;
}

