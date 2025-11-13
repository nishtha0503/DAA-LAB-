#include <stdio.h>
#include <float.h>  // for DBL_MAX

int main() {
    int n;
    printf("Enter number of book IDs (n): ");
    scanf("%d", &n);

    int keys[n + 1];
    double p[n + 1], q[n + 2];
    double e[n + 2][n + 2];  // Expected cost
    double w[n + 2][n + 2];  // Weight sum
    int root[n + 1][n + 1];  // For reconstruction (optional)

    printf("Enter %d sorted book IDs:\n", n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &keys[i]);

    printf("Enter %d successful search probabilities (p[i]):\n", n);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);

    printf("Enter %d unsuccessful search probabilities (q[i]):\n", n + 1);
    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    // Initialize e[i][i-1] and w[i][i-1]
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // Main DP computation
    for (int l = 1; l <= n; l++) { // l = length of subtree
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum expected cost of OBST = %.4lf\n", e[1][n]);
    return 0;
}

