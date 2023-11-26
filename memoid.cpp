#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Piece {
    int width;
    int height;
    int value;
};

struct Rect {
    int x;
    int y;
    int width;
    int height;
};

// Memoization table
vector<vector<int>> dp;

int guillotineMaximizeValue(const Rect& rect, vector<Piece>& pieces) {
    if (rect.width <= 0 || rect.height <= 0) {
        return 0;  // Base case: no area left
    }

    if (dp[rect.width][rect.height] != -1) {
        return dp[rect.width][rect.height];  // Return memoized result if available
    }

    int max_value = 0;

    for (Piece& piece : pieces) {
        for (int rotation = 0; rotation < 2; ++rotation) {
            int piece_width = (rotation == 0) ? piece.width : piece.height;
            int piece_height = (rotation == 0) ? piece.height : piece.width;

            if (piece_width <= rect.width && piece_height <= rect.height) {
                Rect rect1 = {rect.x + piece_width, rect.y, rect.width - piece_width, rect.height};
                Rect rect2 = {rect.x, rect.y + piece_height, piece_width, rect.height - piece_height};

                int current_value = piece.value + guillotineMaximizeValue(rect1, pieces) +
                                   guillotineMaximizeValue(rect2, pieces);

                max_value = max(max_value, current_value);
            }
        }
    }

    // Memoize the result
    dp[rect.width][rect.height] = max_value;
    return max_value;
}

int maximizeValue(int X, int Y, vector<Piece>& pieces) {
    Rect initial_rect = {0, 0, X, Y};
    dp.assign(X + 1, vector<int>(Y + 1, -1));  // Initialize memoization table
    return max(guillotineMaximizeValue(initial_rect, pieces), guillotineMaximizeValue({0, 0, Y, X}, pieces));
}

int main() {
    int X, Y;
    int inputCount1 = scanf("%d %d", &X, &Y);

    int n;
    int inputCount2 = scanf("%d", &n);

    vector<Piece> pieces(n);
    for (int i = 0; i < n; ++i) {
        int inputCount3 = scanf("%d %d %d", &pieces[i].width, &pieces[i].height, &pieces[i].value);
    }

    int result = maximizeValue(X, Y, pieces);
    printf("%d\n", result);

    return 0;
}
