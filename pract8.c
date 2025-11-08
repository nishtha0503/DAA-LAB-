#include <stdio.h>
#include <stdbool.h>

#define V 5  // Number of vertices


bool isSafe(int v, int graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}


bool graphColoringUtil(int graph[V][V], int m, int color[], int v) {
    if (v == V)
        return true;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;

            if (graphColoringUtil(graph, m, color, v + 1))
                return true;

            color[v] = 0; // backtrack
        }
    }
    return false;
}


void printSolution(int color[], char vertices[]) {
    char *colorNames[] = {"", "Red", "Green", "Blue"};

    for (int i = 0; i < V; i++)
        printf("Area %c ---> %s\n", vertices[i], colorNames[color[i]]);
}


void graphColoring(int graph[V][V], int m, char vertices[], char *graphName) {
    int color[V] = {0};

    printf("\n===== %s =====\n", graphName);

    if (!graphColoringUtil(graph, m, color, 0)) {
        printf("❌ No valid coloring possible with %d colors.\n", m);
        return;
    }

    printf(" Solution exists with %d colors:\n", m);
    printSolution(color, vertices);
}

int main() {
    // Graph 1: City areas A–E
    int graph1[V][V] = {
        {0, 1, 1, 0, 1},  // A
        {1, 0, 1, 1, 0},  // B
        {1, 1, 0, 1, 0},  // C
        {0, 1, 1, 0, 1},  // D
        {1, 0, 0, 1, 0}   // E
    };
    char vertices1[V] = {'A', 'B', 'C', 'D', 'E'};

    // Graph 2: City areas T–M–S–H–C
    int graph2[V][V] = {
        {0, 1, 1, 0, 1},  // T
        {1, 0, 1, 1, 0},  // M
        {1, 1, 0, 1, 1},  // S
        {0, 1, 1, 0, 1},  // H
        {1, 0, 1, 1, 0}   // C
    };
    char vertices2[V] = {'T', 'M', 'S', 'H', 'C'};

    int m1 = 3; // Colors for Graph 1
    int m2 = 3; 

    
    graphColoring(graph1, m1, vertices1, "Graph 1 (A–E)");
    graphColoring(graph2, m2, vertices2, "Graph 2 (T–M–S–H–C)");

    return 0;
}
