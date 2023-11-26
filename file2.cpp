#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

// Represents a type of rectangular piece with width, height, and value.
struct Piece {
    int width;
    int height;
    int value;
};

// Represents a rectangle with top-left corner coordinates (x, y), width, and height.
struct Rect {
    int x;
    int y;
    int width;
    int height;
};

/**
 * Recursive function to maximize the value of packing pieces into a rectangular space.
 *
 * @param rect The current available rectangular space.
 * @param pieces A vector containing different types of pieces to be packed.
 * @return The maximum value achievable by packing the pieces into the given space.
 */
int guillotineMaximizeValue(const Rect& rect, vector<Piece>& pieces) {
    int max_value = 0;

    // Iterate through each piece in the vector.
    for (Piece& piece : pieces) {
        // Consider both orientations of the piece.
        for (int rotation = 0; rotation < 2; ++rotation) {
            // Dynamically determine piece width and height based on rotation.
            int piece_width, piece_height;

            if (rotation == 0) {
                piece_width = piece.width;
                piece_height = piece.height;
            } else {
                piece_width = piece.height;
                piece_height = piece.width;
            }

            // Check if the piece can fit into the current available space.
            if (piece_width <= rect.width && piece_height <= rect.height) {
                // Create two possible rectangles after placing the current piece.
                Rect rect1 = {rect.x + piece_width, rect.y, rect.width - piece_width, rect.height};
                Rect rect2 = {rect.x, rect.y + piece_height, piece_width, rect.height - piece_height};

                // Calculate the value for the current piece placement recursively.
                int current_value = piece.value + guillotineMaximizeValue(rect1, pieces) + guillotineMaximizeValue(rect2, pieces);

                // Update the maximum value.
                max_value = max(max_value, current_value);
            }
        }
    }

    return max_value;
}

/**
 * Function to find the maximum value achievable by packing pieces into a rectangular space.
 *
 * @param X Width of the initial rectangular space.
 * @param Y Height of the initial rectangular space.
 * @param pieces A vector containing different types of pieces to be packed.
 * @return The maximum value achievable by packing the pieces into the given space.
 */
int maximizeValue(int X, int Y, vector<Piece>& pieces) {
    // Create an initial rectangle representing the full available space.
    Rect initial_rect = {0, 0, X, Y};

    // Test both orientations and choose the one with the maximum value.
    return max(guillotineMaximizeValue(initial_rect, pieces), guillotineMaximizeValue({0, 0, Y, X}, pieces));
}

int main() {
    int X, Y;
    scanf("%d %d", &X, &Y);

    int n;
    scanf("%d", &n);

    // Read information about each type of piece
    vector<Piece> pieces(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &pieces[i].width, &pieces[i].height, &pieces[i].value);
    }

    // Calculate the maximum total value and print the result
    int result = maximizeValue(X, Y, pieces);
    printf("%d\n", result);

    return 0;
}
