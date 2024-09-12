#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class Solution_t2 {
public:
    static const int MAXN = 1001;
    static const int MAXM = 5;
    static const int MAXS = 243; // std::pow(3, MAXM)
    static const int MOD = 1000000007;

    int n;
    int m;
    int maxs;
    std::vector<std::vector<std::vector<int>>> dp;
    std::vector<int> first;
    int size;

    int colorTheGrid(int rows, int cols) {
        build(rows, cols);
        int ans = 0;
        for (int i = 0; i < size; i++) {
            ans = (ans + f(1, 0, first[i], 1)) % MOD;
        }
        return ans;
    }

    void build(int rows, int cols) {
        n = std::max(rows, cols);
        m = std::min(rows, cols);
        maxs = std::pow(3, m);
        dp.resize(MAXN, std::vector<std::vector<int>>(MAXM, std::vector<int>(MAXS, -1)));
        first.resize(MAXS);
        size = 0;
        dfs(0, 0, 1);
    }

    // 取得所有第一行的有效状态
    void dfs(int j, int s, int bit) {
        if (j == m) {
            first[size++] = s;
        } else {
            int left = j == 0 ? -1 : get(s, bit / 3);
            if (left != 0) {
                dfs(j + 1, set(s, bit, 0), bit * 3);
            }
            if (left != 1) {
                dfs(j + 1, set(s, bit, 1), bit * 3);
            }
            if (left != 2) {
                dfs(j + 1, set(s, bit, 2), bit * 3);
            }
        }
    }

    int f(int i, int j, int s, int bit) {
        if (i == n) {
            return 1;
        }
        if (j == m) {
            return f(i + 1, 0, s, 1);
        }
        if (dp[i][j][s] != -1) {
            return dp[i][j][s];
        }
        // 上方的颜色
        int up = get(s, bit);
        // 左侧的颜色，-1代表左侧没有格子
        int left = j == 0 ? -1 : get(s, bit / 3);
        int ans = 0;
        if (up != 0 && left != 0) {
            ans = (ans + f(i, j + 1, set(s, bit, 0), bit * 3)) % MOD;
        }
        if (up != 1 && left != 1) {
            ans = (ans + f(i, j + 1, set(s, bit, 1), bit * 3)) % MOD;
        }
        if (up != 2 && left != 2) {
            ans = (ans + f(i, j + 1, set(s, bit, 2), bit * 3)) % MOD;
        }
        dp[i][j][s] = ans;
        return ans;
    }

    int get(int s, int bit) {
        return s / bit % 3;
    }

    int set(int s, int bit, int v) {
        return s - get(s, bit) * bit + v * bit;
    }
};

class Solution_t1 {
public:
    static const int MAXN = 5;
    static const int MAXM = 5;
    static const int MAXP = 7;
    static const int MAXS = 243; // std::pow(3, MAXM)

    int n;
    int m;
    int maxs;
    std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> dp;

    int getMaxGridHappiness(int rows, int cols, int in, int ex) {
        n = std::max(rows, cols);
        m = std::min(rows, cols);
        maxs = static_cast<int>(std::pow(3, m));
        dp.resize(MAXN, std::vector<std::vector<std::vector<std::vector<int>>>>(MAXM, std::vector<std::vector<std::vector<int>>>(MAXS, std::vector<std::vector<int>>(MAXP, std::vector<int>(MAXP, -1)))));

        return f(0, 0, 0, in, ex, 1);
    }

    // 当前来到i行j列的格子
    // s表示轮廓线的状态，可以得到左侧格子放了什么人，上侧格子放了什么人
    // 内向的人还有a个，外向的人还有b个
    // 返回最大的幸福感
    // 注意 : bit等于3的j次方，bit不是关键可变参数，因为bit的值被j的值决定
    int f(int i, int j, int s, int a, int b, int bit) {
        if (i == n) {
            return 0;
        }
        if (j == m) {
            return f(i + 1, 0, s, a, b, 1);
        }
        if (dp[i][j][s][a][b] != -1) {
            return dp[i][j][s][a][b];
        }
        // 当前格子不安置人
        int ans = f(i, j + 1, set(s, bit, 0), a, b, bit * 3);
        // 上方邻居的状态
        int up = get(s, bit);
        // 左方邻居的状态
        int left = j == 0 ? 0 : get(s, bit / 3);
        // 邻居人数
        int neighbor = 0;
        // 如果放置人，之前得到的幸福感要如何变化
        int pre = 0;
        if (up != 0) {
            neighbor++;
            // 上邻居是内向的人，幸福感要减30；是外向的人，幸福感要加20
            pre += up == 1 ? -30 : 20;
        }
        if (left != 0) {
            neighbor++;
            // 左邻居是内向的人，幸福感要减30；是外向的人，幸福感要加20
            pre += left == 1 ? -30 : 20;
        }
        if (a > 0) {
            // 当前格子决定放内向的人
            ans = std::max(ans, pre + 120 - neighbor * 30 + f(i, j + 1, set(s, bit, 1), a - 1, b, bit * 3));
        }
        if (b > 0) {
            // 当前格子决定放外向的人
            ans = std::max(ans, pre + 40 + neighbor * 20 + f(i, j + 1, set(s, bit, 2), a, b - 1, bit * 3));
        }
        dp[i][j][s][a][b] = ans;
        return ans;
    }

    // s表示当前状态，按照3进制来理解
    // 当前来到第j号格，3的j次方是bit
    // 返回s第j号格的值
    int get(int s, int bit) {
        return s / bit % 3;
    }

    // s表示当前状态，按照3进制来理解
    // 当前来到第j号格，3的j次方是bit
    // 把s第j号格的值设置成v，返回新状态
    int set(int s, int bit, int v) {
        return s - get(s, bit) * bit + v * bit;
    }
};


