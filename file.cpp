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

int guillotineMaximizeValue(const Rect& rect, vector<Piece>& pieces) {
    int max_value = 0;

    for (const Piece& piece : pieces) {
        // Consider both orientations of the piece
        for (int rotation = 0; rotation < 2; ++rotation) {
            int piece_width = (rotation == 0) ? piece.width : piece.height;
            int piece_height = (rotation == 0) ? piece.height : piece.width;

            if (piece_width <= rect.width && piece_height <= rect.height) {
                // Create two possible rectangles after placing the current piece
                Rect rect1 = { rect.x + piece_width, rect.y, rect.width - piece_width, piece_height };
                Rect rect2 = { rect.x, rect.y + piece_height, rect.width, rect.height - piece_height };

                // Calculate the value for the current piece placement
                int current_value = piece.value + guillotineMaximizeValue(rect1, pieces) + guillotineMaximizeValue(rect2, pieces);

                // Update the maximum value
                max_value = max(max_value, current_value);
            }
        }
    }

    return max_value;
}

int maximizeValue(int X, int Y, vector<Piece>& pieces) {
    Rect initial_rect = {0, 0, X, Y};
    return guillotineMaximizeValue(initial_rect, pieces);
}

int main() {
    int X, Y;
    scanf("%d %d", &X, &Y);

    int n;
    scanf("%d", &n);

    vector<Piece> pieces(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &pieces[i].width, &pieces[i].height, &pieces[i].value);
    }

    int result = maximizeValue(X, Y, pieces);
    printf("%d\n", result);

    return 0;
}
