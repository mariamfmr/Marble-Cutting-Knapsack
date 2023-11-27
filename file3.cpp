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

struct Rect {
    int x;
    int y;
    int width;
    int height;
};

unordered_map<int, unordered_map<int, int>> dp;  // Memoization table

int guillotineMaximizeValue(const Rect& rect, vector<Piece>& pieces) {
    if (rect.width <= 0 || rect.height <= 0) {
        return 0;
    }

    if (dp.find(rect.width) != dp.end() && dp[rect.width].find(rect.height) != dp[rect.width].end()) {
        return dp[rect.width][rect.height];
    }

    int max_value = 0;

    for (Piece& piece : pieces) {
        for (int rotation = 0; rotation < 2; ++rotation) {
            int piece_width, piece_height;

            if (rotation == 0) {
                piece_width = piece.width;
                piece_height = piece.height;
            } else {
                piece_width = piece.height;
                piece_height = piece.width;
            }

            if (piece_width <= rect.width && piece_height <= rect.height) {
                Rect rect1 = {rect.x + piece_width, rect.y, rect.width - piece_width, rect.height};
                Rect rect2 = {rect.x, rect.y + piece_height, piece_width, rect.height - piece_height};

                int current_value = piece.value + guillotineMaximizeValue(rect1, pieces) + guillotineMaximizeValue(rect2, pieces);

                max_value = max(max_value, current_value);
            }
        }
    }

    dp[rect.width][rect.height] = max_value;
    return max_value;
}

int maximizeValue(int X, int Y, vector<Piece>& pieces) {
    Rect initial_rect = {0, 0, X, Y};
    return max(guillotineMaximizeValue(initial_rect, pieces), guillotineMaximizeValue({0, 0, Y, X}, pieces));
}

int main() {
    int X, Y;
    cin >> X >> Y;

    int n;
    cin >> n;

    vector<Piece> pieces(n);
    for (int i = 0; i < n; ++i) {
        cin >> pieces[i].width >> pieces[i].height >> pieces[i].value;
    }

    int result = maximizeValue(X, Y, pieces);
    cout << result << endl;

    return 0;
}
