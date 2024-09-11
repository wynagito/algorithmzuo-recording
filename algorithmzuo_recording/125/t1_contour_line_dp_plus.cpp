#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 12;
const int MAXM = 12;
const int MOD = 100000000;

int grid[MAXN][MAXM];
int dp[MAXN][MAXM][1 << MAXM];
int n, m, maxs;

int compute();
int f(int i, int j, int s);
int get(int s, int j);
int set(int s, int j, int v);

int main() {
    cin >> n >> m;
    maxs = 1 << m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << compute() << endl;
    return 0;
}

int compute() {
    return f(0, 0, 0);
}

int f(int i, int j, int s) {
    if (i == n) {
        return 1;
    }
    if (j == m) {
        return f(i + 1, 0, s);
    }
    if (dp[i][j][s] != -1) {
        return dp[i][j][s];
    }
    int ans = f(i, j + 1, set(s, j, 0));
    if (grid[i][j] == 1 && (j == 0 || get(s, j - 1) == 0) && get(s, j) == 0) {
        ans = (ans + f(i, j + 1, set(s, j, 1))) % MOD;
    }
    dp[i][j][s] = ans;
    return ans;
}

int get(int s, int j) {
    return (s >> j) & 1;
}

int set(int s, int j, int v) {
    return v == 0 ? (s & ~(1 << j)) : (s | (1 << j));
}
