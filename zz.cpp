#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Piece {
    int width;
    int height;
    int value;
};

// Matrix for memoization
vector<vector<int>> dp;

int guillotineMaximizeValue(int x, int y, int width, int height, vector<Piece>& pieces) {
    if (width <= 0 || height <= 0) {
        return 0;
    }

    if (dp[width][height] != -1) {
        return dp[width][height];
    }

    int max_value = 0;

    for (Piece& piece : pieces) {
        int piece_width, piece_height;

        piece_width = piece.width;
        piece_height = piece.height;

        if (piece_width <= width && piece_height <= height) {
            int rect1_x = x + piece_width;
            int rect1_y = y;
            int rect1_width = width - piece_width;
            int rect1_height = height;

            int rect2_x = x;
            int rect2_y = y + piece_height;
            int rect2_width = piece_width;
            int rect2_height = height - piece_height;

            int current_value = piece.value + guillotineMaximizeValue(rect1_x, rect1_y, rect1_width, rect1_height, pieces) +
                                guillotineMaximizeValue(rect2_x, rect2_y, rect2_width, rect2_height, pieces);

            max_value = max(current_value, max_value);
        }
    }

    dp[width][height] = max_value;
    return max_value;
}

int maximizeValue(int X, int Y, vector<Piece>& pieces) {
    // Initialize the memoization table with -1
    dp.assign(X + 1, vector<int>(Y + 1, -1));

    // Calculate maximum value for both orientations
    int result = max(guillotineMaximizeValue(0, 0, X, Y, pieces), guillotineMaximizeValue(0, 0, X, Y, pieces));

    return result;
}

int main() {
    int X, Y;
    scanf("%d %d", &X, &Y);

    int n;
    scanf("%d", &n);

    vector<Piece> pieces(2 * n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &pieces[2 * i].width, &pieces[2 * i].height, &pieces[2 * i].value);
        pieces[2 * i + 1] = {pieces[2 * i].height, pieces[2 * i].width, pieces[2 * i].value};
    }

    int result = maximizeValue(X, Y, pieces);
    printf("%d\n", result);

    // Print the dp matrix
    cout << "Memoization table (dp):" << endl;
    for (int i = 0; i <= X; ++i) {
        for (int j = 0; j <= Y; ++j) {
            cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
        }
    }

    return 0;
}
