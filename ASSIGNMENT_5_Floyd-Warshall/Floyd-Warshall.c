#include <stdio.h>
#include <limits.h>
#define MAX_V 10
#define INF 99999

void printSolution(int dist[][MAX_V], int parent[][MAX_V], int V) {
    printf("The following matrix shows the shortest distances between every pair of vertices \n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }

    printf("\nParent matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%7d", parent[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall(int dist[][MAX_V], int V) {
    int parent[MAX_V][MAX_V]; // To store the intermediate vertices for paths

    // Initialize parent matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            parent[i][j] = i;
        }
    }

    for (int k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (int i = 0; i < V; i++) {
            // Pick all vertices as destination for the source
            for (int j = 0; j < V; j++) {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j]; // Update the intermediate vertex
                }
            }
        }
    }

    // Check for negative cycles
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            printf("Graph contains a negative cycle\n");
            return;
        }
    }

    // Print the shortest distance matrix and parent matrix
    printSolution(dist, parent, V);
}

int main() {
    int V;
    printf("Enter the number of vertices (max %d): ", MAX_V);
    if (scanf("%d", &V) != 1) {
        printf("Invalid input. Please enter an integer.\n");
        return 1;
    }

    int graph[MAX_V][MAX_V];

    printf("Enter the adjacency matrix for the graph (INF for infinity):\n");

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            char input[20]; // Assuming a reasonable maximum length for an input
            scanf("%s", input);

            if (strcmp(input, "INF") == 0) {
                graph[i][j] = INF;
            } else {
                char* endptr;
                long value = strtol(input, &endptr, 10);

                if (*endptr != '\0') {
                    printf("Invalid input. Please enter integers or 'INF'.\n");
                    return 1;
                }

                graph[i][j] = (int)value;
            }
        }
    }

    floydWarshall(graph, V);
    return 0;
}

// The auxiliary space complexity of the program is O(n^2), where n is the number of vertices in the graph. 
