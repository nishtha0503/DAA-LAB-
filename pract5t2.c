#include <stdio.h>
#include <string.h>

#define MAX 100

void printLRS(char str[], int n, int dp[MAX][MAX]) {
    int i = n, j = n;
    char lrs[MAX];
    int index = dp[n][n];
    lrs[index] = '\0';

    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i - 1][j - 1] + 1 && str[i - 1] == str[j - 1] && i != j) {
            lrs[index - 1] = str[i - 1];
            i--;
            j--;
            index--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    printf("LRS: %s\n", lrs);
}

void LRS(char str[]) {
    int n = strlen(str);
    int dp[MAX][MAX];

    // Build the dp table
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (str[i - 1] == str[j - 1] && i != j)
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = (dp[i][j - 1] > dp[i - 1][j]) ? dp[i][j - 1] : dp[i - 1][j];
        }
    }

    printf("Length of LRS: %d\n", dp[n][n]);
    printLRS(str, n, dp);
}

int main() {
    char str[] = "AABCBDC";
    LRS(str);
    return 0;
}
