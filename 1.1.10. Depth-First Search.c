#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Graph represented using adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX_VERTICES];
int visited[MAX_VERTICES];

// Function to create a new adjacency list node
Node* createNode(int vertex) {
    //write your code here...
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->vertex = vertex;
    newNode->next = NULL;

    return newNode;
    
    
    
}

// Function to add an edge to the graph
void addEdge(int u, int v) {
    //write your code here...
    Node* newNode = createNode(v);

    if (adjList[u] == NULL) {
        adjList[u] = newNode;
    } else {
        Node* temp = adjList[u];

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
	}
    
    
    
}

// Function to sort the adjacency list for each vertex
void sortAdjList(int V) {
    //write your code here...
    for (int i = 0; i < V; i++) {
        Node* current = adjList[i];

        while (current != NULL) {
            Node* next = current->next;

            while (next != NULL) {
                if (current->vertex > next->vertex) {
                    int temp = current->vertex;
                    current->vertex = next->vertex;
                    next->vertex = temp;
                }

                next = next->next;
            }

            current = current->next;
        }
	}
    
    
    
}

// Depth-First Search (DFS) function
void DFS(int start) {
    //write your code here...
        visited[start] = 1;

    printf("%d ", start);

    Node* temp = adjList[start];

    while (temp != NULL) {
        if (!visited[temp->vertex]) {
            DFS(temp->vertex);
        }

        temp = temp->next;
    }

    
    
    
}

int main() {
    int V, E;
    int u, v, start;

    // Read number of vertices and edges
    scanf("%d %d", &V, &E);

    // Initialize adjacency list
    for (int i = 0; i < V; i++) {
        adjList[i] = NULL;
        visited[i] = 0;
    }

    // Read the edges
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    // Sort the adjacency list for each vertex
    sortAdjList(V);

    // Read the starting node
    scanf("%d", &start);

    // Perform DFS starting from the given node
    DFS(start);

    return 0;
}
