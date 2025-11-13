#include <stdio.h>
#include <limits.h>

// Function to find maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find maximum subarray sum that crosses mid
int maxCrossingSum(int arr[], int l, int m, int r, int constraint, int *bestLeft, int *bestRight) {
    int sum = 0;
    int left_sum = -1;
    int left_idx = m;

    // Include elements on left of mid
    for (int i = m; i >= l; i--) {
        sum += arr[i];
        if (sum <= constraint && sum > left_sum) {
            left_sum = sum;
            left_idx = i;
        }
    }

    sum = 0;
    int right_sum = -1;
    int right_idx = m + 1;

    // Include elements on right of mid
    for (int i = m + 1; i <= r; i++) {
        sum += arr[i];
        if (left_sum != -1 && (left_sum + sum) <= constraint && (left_sum + sum) > right_sum) {
            right_sum = left_sum + sum;
            right_idx = i;
        }
    }

    if (left_sum == -1 && right_sum == -1)
        return -1;

    *bestLeft = left_idx;
    *bestRight = right_idx;
    return max(left_sum, right_sum);
}

// Divide and conquer function to find max subarray sum under constraint
int maxSubArraySum(int arr[], int l, int r, int constraint, int *start, int *end) {
    if (l > r)
        return -1;
    if (l == r) {
        if (arr[l] <= constraint) {
            *start = l;
            *end = l;
            return arr[l];
        }
        return -1;
    }

    int m = (l + r) / 2;

    int left_start = -1, left_end = -1;
    int right_start = -1, right_end = -1;
    int cross_start = -1, cross_end = -1;

    int left_sum = maxSubArraySum(arr, l, m, constraint, &left_start, &left_end);
    int right_sum = maxSubArraySum(arr, m + 1, r, constraint, &right_start, &right_end);
    int cross_sum = maxCrossingSum(arr, l, m, r, constraint, &cross_start, &cross_end);

    int max_sum = -1;
    if (left_sum > max_sum) {
        max_sum = left_sum;
        *start = left_start;
        *end = left_end;
    }
    if (right_sum > max_sum) {
        max_sum = right_sum;
        *start = right_start;
        *end = right_end;
    }
    if (cross_sum > max_sum) {
        max_sum = cross_sum;
        *start = cross_start;
        *end = cross_end;
    }

    return max_sum;
}

// Main driver to handle input and testing
int main() {
    int test_cases[][10] = {
        {2, 1, 3, 4},               // 1
        {2, 2, 2, 2},               // 2
        {1, 5, 2, 3},               // 3
        {6, 7, 8},                  // 4
        {1, 2, 3, 2, 1},            // 5
        {1, 1, 1, 1, 1},            // 6
        {4, 2, 3, 1},               // 7
        {},                         // 8
        {1, 2, 3}                   // 9
    };

    int sizes[] = {4, 4, 4, 3, 5, 5, 4, 0, 3};
    int constraints[] = {5, 4, 5, 5, 5, 4, 5, 10, 0};

    for (int t = 0; t < 9; t++) {
        int n = sizes[t];
        int constraint = constraints[t];

        printf("\nTest Case %d:\n", t + 1);
        printf("Constraint = %d\n", constraint);
        if (n == 0) {
            printf("No feasible subarray (empty array)\n");
            continue;
        }

        int start = -1, end = -1;
        int max_sum = maxSubArraySum(test_cases[t], 0, n - 1, constraint, &start, &end);

        if (max_sum == -1) {
            printf("No feasible subarray found.\n");
        } else {
            printf("Best subarray: [");
            for (int i = start; i <= end; i++) {
                printf("%d", test_cases[t][i]);
                if (i < end) printf(", ");
            }
            printf("] → sum = %d\n", max_sum);
        }
    }

    return 0;
}
