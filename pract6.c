#include <stdio.h>

#define N 5  

int G[N][N] = {
    {0, 1, 1, 0, 1},  // A
    {1, 0, 1, 1, 0},  // B
    {1, 1, 0, 1, 0},  // C
    {0, 1, 1, 0, 1},  // D
    {1, 0, 0, 1, 0}   // E
};

int x[N];


void NextValue(int k) {
    int j;
    while (1) {
        x[k] = (x[k] + 1) % (N + 1);  
        if (x[k] == 0)
            return; 

        if (G[x[k - 1]][x[k]] != 0) { 
            for (j = 0; j < k; j++)   
                if (x[j] == x[k])
                    break;

            if (j == k) { 
                if ((k < N - 1) || ((k == N - 1) && (G[x[N - 1]][x[0]] != 0)))
                    return;
            }
        }
    }
}


void Hamiltonian(int k) {
    while (1) {
        NextValue(k);
        if (x[k] == 0)
            return;

        if (k == N - 1) { 
            printf("\nHamiltonian Cycle Found: ");
            for (int i = 0; i < N; i++)
                printf("%c -> ", 'A' + x[i]);
            printf("%c\n", 'A' + x[0]); 
        } else {
            Hamiltonian(k + 1);
        }
    }
}

int main() {
    printf("Smart City Hamiltonian Cycle Finder (Areas: A, B, C, D, E)\n");
    printf("-----------------------------------------------------------\n");

    // Initialize path with zeros
    for (int i = 0; i < N; i++)
        x[i] = 0;

    x[0] = 0; // Start from vertex A (index 0)
    Hamiltonian(1);

    return 0;
}
