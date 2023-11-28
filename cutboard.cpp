#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the maximum value obtainable by cutting a given rectangle
int maximizeValue(int X, int Y, vector<vector<int>>& pieces) {
    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    // Organize the matrix with the pieces and their costs
    for (const vector<int>& piece : pieces) {
        int pieceWidth = piece[0];
        int pieceHeight = piece[1];
        int pieceValue = piece[2];

        // Check if the piece fits without rotation
        if (pieceWidth <= X && pieceHeight <= Y) {
            dp[pieceWidth][pieceHeight] = max(dp[pieceWidth][pieceHeight], pieceValue);
        }

        // Check if the rotated piece fits
        if (pieceHeight <= X && pieceWidth <= Y) {
            dp[pieceHeight][pieceWidth] = max(dp[pieceHeight][pieceWidth], pieceValue);
        }
    }

    // Iterate over all possible combinations of guillotine cuts
    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y; j++) {
            // Consider each guillotine cut and check if it can fit in the current rectangle
            for (int cutWidth = 1; cutWidth <= i; cutWidth++) {
                dp[i][j] = max(dp[i][j], dp[cutWidth][j] + dp[i - cutWidth][j]);
            }

            for (int cutHeight = 1; cutHeight <= j; cutHeight++) {
                dp[i][j] = max(dp[i][j], dp[i][cutHeight] + dp[i][j - cutHeight]);
            }
        }
    }

    // Return the maximum value obtainable for the given rectangle
    return dp[X][Y];
}

// Main function
int main() {
    // Read the dimensions of the original rectangle
    int X, Y;
    scanf("%d %d", &X, &Y);

    // Read the number of available pieces
    int n;
    scanf("%d", &n);

    // Read the details of each piece (width, height, value)
    vector<vector<int>> pieces(n, vector<int>(3));
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &pieces[i][0], &pieces[i][1], &pieces[i][2]);
    }

    // Find and print the maximum value obtainable
    int result = maximizeValue(X, Y, pieces);
    printf("%d\n", result);

    return 0;
}
