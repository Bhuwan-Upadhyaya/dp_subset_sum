// Name: Bhuwan
// ID: bxu9187
// Compilation Command: gcc -o Lab3 Lab3.c
//                     : .\Lab3
// CSE 3318 Lab Assignment 3
// This program uses dynamic programming to find two separate subsequences 
// in an input sequence such that each subsequence sums to two given target values.

#include <stdio.h>
#include <stdlib.h>

// Function to read input values and allocate memory for the sequence array
void readInput(int* n, int* target1, int* target2, int** S) {
    int i;

    // Read n, target1, and target2 from the first line
    scanf("%d %d %d", n, target1, target2);

    // Allocate memory for the sequence
    *S = (int*) malloc((*n + 1) * sizeof(int));
    if (!(*S)) {
        printf("malloc failed\n");
        exit(0);
    }

    // Sentinel zero for convenience
    (*S)[0] = 0;
    for (i = 1; i <= *n; i++) {
        scanf("%d", *S + i);
    }
}

// Dynamic programming function to fill the DP table for dual targets
void subsetSumDual(int n, int target1, int target2, int* S, int** C) {
    int i, sum1, sum2;

    // Initialize DP table with n + 1 as "no solution" indicator
    for (sum1 = 0; sum1 <= target1; sum1++) {
        for (sum2 = 0; sum2 <= target2; sum2++) {
            C[sum1][sum2] = n + 1; // Initialize with sentinel for "no solution"
        }
    }
    C[0][0] = 0; // Base case for DP

    // Populate the DP table for both targets
    for (i = 1; i <= n; i++) {
        for (sum1 = target1; sum1 >= S[i]; sum1--) {
            for (sum2 = target2; sum2 >= S[i]; sum2--) {
                if (C[sum1 - S[i]][sum2] < i) { // Check if target1 can be met
                    C[sum1][sum2] = i;
                }
                if (C[sum1][sum2 - S[i]] < i) { // Check if target2 can be met
                    C[sum1][sum2] = i;
                }
            }
        }
    }
}

// Function to backtrace the solution and output results
void backtraceAndOutput(int n, int target1, int target2, int* S, int** C) {
    int i;

    // Echo input sequence and targets
    printf("Targets are %d and %d\n", target1, target2);
    printf("  i   S\n");
    printf("-------\n");
    for (i = 1; i <= n; i++) {
        printf("  %d   %d\n", i, S[i]);
    }
    printf("\n");

    // Check if solution exists
    if (C[target1][target2] == n + 1) {
        printf("No solution\n");
        return;
    }

    printf("Solution found:\n");

    // Backtrace for target1, output in strictly descending order
    printf("Subsequence for %d:\n", target1);
    int t1 = target1;
    while (t1 > 0 && C[t1][target2] != 0) {
        printf("%d %d\n", C[t1][target2], S[C[t1][target2]]);
        t1 -= S[C[t1][target2]];
    }

    // Backtrace for target2, output in strictly descending order
    printf("Subsequence for %d:\n", target2);
    int t2 = target2;
    while (t2 > 0 && C[target1][t2] != 0) {
        printf("%d %d\n", C[target1][t2], S[C[target1][t2]]);
        t2 -= S[C[target1][t2]];
    }
}

int main() {
    int n, target1, target2;
    int *S;
    int **C;

    // Read input values
    readInput(&n, &target1, &target2, &S);

    // Allocate memory for DP table C as a 2D array
    C = (int**) malloc((target1 + 1) * sizeof(int*));
    for (int i = 0; i <= target1; i++) {
        C[i] = (int*) malloc((target2 + 1) * sizeof(int));
    }

    // Run DP to find dual subsets
    subsetSumDual(n, target1, target2, S, C);

    // Output result with backtrace
    backtraceAndOutput(n, target1, target2, S, C);

    // Free allocated memory
    free(S);
    for (int i = 0; i <= target1; i++) free(C[i]);
    free(C);
    return 0;
}
