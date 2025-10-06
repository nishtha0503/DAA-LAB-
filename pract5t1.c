#include <stdio.h>
#include <string.h>

#define MAX 100

void printLCS(char X[], char Y[], int m, int n, int dp[MAX][MAX]) {
    int i = m, j = n;
    char lcs[MAX];
    int index = dp[m][n];
    lcs[index] = '\0';  // Null-terminate the LCS string

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    printf("LCS: %s\n", lcs);
}

void LCS(char X[], char Y[]) {
    int m = strlen(X);
    int n = strlen(Y);
    int dp[MAX][MAX];

    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    printf("Final LCS cost: %d\n", dp[m][n]);
    printLCS(X, Y, m, n, dp);
}

int main() {
    char X[] = "AGCCCTAAGGGCTACCTAGCTT";
    char Y[] = "GACAGCCTACAAGCGTTAGCTTG";
    LCS(X, Y);
    return 0;
}
