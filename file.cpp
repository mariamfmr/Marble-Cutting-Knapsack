#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

/**
 * Structure to represent the characteristics of a rectangular piece.
 */
struct Piece {
    int width;   /**< Width of the piece. */
    int height;  /**< Height of the piece. */
    int value;   /**< Value associated with the piece. */
};

/**
 * Structure to represent the characteristics of a rectangular area.
 */
struct Rect {
    int x;      /**< X-coordinate of the top-left corner of the rectangle. */
    int y;      /**< Y-coordinate of the top-left corner of the rectangle. */
    int width;  /**< Width of the rectangle. */
    int height; /**< Height of the rectangle. */
};

/**
 * Recursive function to maximize the total value by placing pieces into a rectangular container
 * using the Guillotine Bin Packing algorithm with both horizontal and vertical cuts.
 *
 * @param rect The rectangular area available for placing pieces.
 * @param pieces A vector containing information about each type of piece.
 * @return The maximum total value achievable by placing pieces into the given space.
 */
int guillotineMaximizeValue(const Rect& rect, vector<Piece>& pieces) {
    int max_value = 0;

    // Iterate over each type of piece
    for (const Piece& piece : pieces) {
        // Consider both orientations of the piece (original and rotated)
        for (int rotation = 0; rotation < 2; ++rotation) {
            int piece_width, piece_height;

            // Determine the dimensions of the piece based on its orientation
            if (rotation == 0) {
                piece_width = piece.width;
                piece_height = piece.height;
            } else {
                piece_width = piece.height;
                piece_height = piece.width;
            }

            // Check if the piece can fit into the current available space
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

/**
 * Function to calculate the maximum total value by placing pieces into a rectangular container
 * using the Guillotine Bin Packing algorithm.
 *
 * @param X Width of the rectangular container.
 * @param Y Height of the rectangular container.
 * @param pieces A vector containing information about each type of piece.
 * @return The maximum total value achievable by placing pieces into the given space.
 */
int maximizeValue(int X, int Y, vector<Piece>& pieces) {
    Rect initial_rect = {0, 0, X, Y};
    return guillotineMaximizeValue(initial_rect, pieces);
}

/**
 * The main function that reads input, calls the maximizeValue function,
 * and prints the result.
 *
 * @return 0 to indicate successful execution of the program.
 */
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
