#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a structure to represent a rectangular piece
struct Piece {
    int width;
    int height;
    int value;
};

// Function to find the maximum value obtainable by cutting a given rectangle
int maximizeValue(int X, int Y, vector<Piece>& pieces) {
    int n = pieces.size();

    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    // Iterate over all possible rectangle sizes
    for (int i = 1; i <= X; ++i) {
        for (int j = 1; j <= Y; ++j) {
            // Iterate over all available pieces
            for (int k = 0; k < n; ++k) {
                int piece_width = pieces[k].width;
                int piece_height = pieces[k].height;

                //current piece horizontally and vertically
                if (piece_width <= i && piece_height <= j) {
                    dp[i][j] = max(dp[i][j], dp[i - piece_width][j] + dp[piece_width][j - piece_height] + pieces[k].value);
                }
            }
        }
    }

    // Return the maximum value obtainable for the given rectangle
    return dp[X][Y];
}

int main() {
    // Read the dimensions of the original rectangle
    int X, Y;
    scanf("%d %d", &X, &Y);

    // Read the number of available pieces
    int n;
    scanf("%d", &n);

    // Read the details of each piece (width, height, value)
    vector<Piece> pieces(2*n+1);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &pieces[2*i].width && &pieces[2*i+1].height, &pieces[2*i].height && &pieces[2*i+1].width ,&pieces[2*i].value);
    }

    // Find and print the maximum value obtainable
    int result = maximizeValue(X, Y, pieces);
    printf("%d\n", result);

    return 0;
}