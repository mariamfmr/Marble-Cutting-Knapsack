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

    for (Piece& piece : pieces) {
        // Consider both orientations of the piece
        for (int rotation = 0; rotation < 2; ++rotation) {
            int piece_width = (rotation == 0) ? piece.width : piece.height;
            int piece_height = (rotation == 0) ? piece.height : piece.width;

            if (piece_width <= rect.width && piece_height <= rect.height) {
                // Create two possible rectangles after placing the current piece
                Rect rect1 = { rect.x + piece_width, rect.y, rect.width - piece_width, rect.height };
                Rect rect2 = { rect.x, rect.y + piece_height, piece_width, rect.height - piece_height };

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
    // Test both orientations and choose the one with the maximum value
    return max(guillotineMaximizeValue(initial_rect, pieces), guillotineMaximizeValue({0, 0, Y, X}, pieces));
}

int main() {
    int X, Y;
    int inputCount1 = scanf("%d %d", &X, &Y);
    if (inputCount1 != 2) {
        cerr << "Error reading input for X and Y." << endl;
        return 1;  // Return an error code
    }

    int n;
    int inputCount2 = scanf("%d", &n);
    if (inputCount2 != 1) {
        cerr << "Error reading input for n." << endl;
        return 1;  // Return an error code
    }

    vector<Piece> pieces(n);
    for (int i = 0; i < n; ++i) {
        int inputCount3 = scanf("%d %d %d", &pieces[i].width, &pieces[i].height, &pieces[i].value);
        if (inputCount3 != 3) {
            cerr << "Error reading input for piece " << i + 1 << "." << endl;
            return 1;  // Return an error code
        }
    }

    int result = maximizeValue(X, Y, pieces);
    printf("%d\n", result);

    return 0;
}
