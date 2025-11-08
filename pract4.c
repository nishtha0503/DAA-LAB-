#include <stdio.h>

void optimal_bst(float p[], float q[], int n) {
    float e[n+2][n+1]; 
    float w[n+2][n+1]; 
    int root[n+1][n+1];
    
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1]; 
    }
    
    for (int l = 1; l <= n; l++) { 
        for (int i = 1; i <= n - l + 1; i++) { 
            int j = i + l - 1; 
            e[i][j] = 999999;  
            w[i][j] = w[i][j - 1] + p[j - 1] + q[j];  
            
            for (int r = i; r <= j; r++) {
                float t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
    
    printf("\nOptimal cost of the binary search tree: %.2f\n", e[1][n]);
}

int main() {
    int n = 4;
    float p[] = {0.1, 0.2, 0.4, 0.3};  
    float q[] = {0.05, 0.1, 0.05, 0.05, 0.1}; 

    optimal_bst(p, q, n);

    return 0;
}