use std::cmp::max;
use std::io;

// Function to find the maximum value obtainable by cutting a given rectangle
fn maximize_value(x: usize, y: usize, dp: &mut Vec<Vec<usize>>) -> usize {
    // Iterate over all possible combinations of guillotine cuts
    for i in 1..=x {
        for j in 1..=y {
            // Consider each guillotine cut and check if it can fit in the current rectangle
            for cut_width in 1..=i / 2 {
                dp[i][j] = std::cmp::max(dp[i][j], dp[cut_width][j] + dp[i - cut_width][j]);
            }

            for cut_height in 1..=j / 2 {
                dp[i][j] = std::cmp::max(dp[i][j], dp[i][cut_height] + dp[i][j - cut_height]);
            }
        }
    }

    // Return the maximum value obtainable for the given rectangle
    dp[x][y]
}


fn main() {
    // Read the dimensions of the original rectangle
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let mut dimensions = input_line.split_whitespace().map(|s| s.parse::<usize>().unwrap());
    let x = dimensions.next().unwrap();
    let y = dimensions.next().unwrap();

    // Read the number of available pieces
    input_line.clear();
    io::stdin().read_line(&mut input_line).unwrap();
    let n: usize = input_line.trim().parse().unwrap();

    // Read the details of each piece (width, height, value) and organize in the matrix
    let mut dp = vec![vec![0; y + 1]; x + 1];
    for _ in 0..n {
        input_line.clear();
        io::stdin().read_line(&mut input_line).unwrap();
        let mut piece_info = input_line.split_whitespace().map(|s| s.parse::<usize>().unwrap());
        let piece_width = piece_info.next().unwrap();
        let piece_height = piece_info.next().unwrap();
        let piece_value = piece_info.next().unwrap();

        // Check if the piece fits without rotation
        if piece_width <= x && piece_height <= y {
            dp[piece_width][piece_height] = max(dp[piece_width][piece_height], piece_value);
        }

        // Check if the rotated piece fits
        if piece_height <= x && piece_width <= y {
            dp[piece_height][piece_width] = max(dp[piece_height][piece_width], piece_value);
        }
    }

    // Find and print the maximum value obtainable
    let result = maximize_value(x, y, &mut dp);
    println!("{}", result);
}
