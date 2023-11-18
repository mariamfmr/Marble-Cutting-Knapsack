#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maximizeValue(int X, int Y, vector<vector<int>>& pieces) {
    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    for (int i = 1; i <= X; ++i) {
        for (int j = 1; j <= Y; ++j) {
            for (auto& piece : pieces) {
                int ai = piece[0];
                int bi = piece[1];
                int pi = piece[2];

                if (i >= ai && j >= bi) {
                    dp[i][j] = max(dp[i][j], dp[i - ai][j - bi] + pi);
                }
            }
        }
    }

    return dp[X][Y];
}

int main() {
    int X, Y;
    cin >> X >> Y;

    int n;
    cin >> n;

    vector<vector<int>> pieces(n, vector<int>(3));

    for (int i = 0; i < n; ++i) {
        cin >> pieces[i][0] >> pieces[i][1] >> pieces[i][2];
    }

    int result = maximizeValue(X, Y, pieces);

    cout << result << endl;

    return 0;
}
