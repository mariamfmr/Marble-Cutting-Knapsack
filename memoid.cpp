#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Piece {
    int width;
    int height;
    int value;
};

unordered_map<int, unordered_map<int, int>> dp;  // Memoization table

int guillotineMaximizeValue(int x, int y, int width, int height, vector<Piece>& pieces) {
    if (width <= 0 || height <= 0) {
        return 0;
    }

    if (dp.find(width) != dp.end() && dp[width].find(height) != dp[width].end()) {
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
    return max(guillotineMaximizeValue(0, 0, X, Y, pieces), guillotineMaximizeValue(0, 0, Y, X, pieces));
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

    return 0;
}
