// 完成配对需要的最少字符数量
// 给定一个由'['、']'、'('，')'组成的字符串
// 请问最少插入多少个括号就能使这个字符串的所有括号正确配对
// 例如当前串是 "([[])"，那么插入一个']'即可满足
// 输出最少需要插入多少个字符
// 测试链接 : https://www.nowcoder.com/practice/e391767d80d942d29e6095a935a5b96b

#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 让s[l...r]配对至少需要几个字符
int f(string s, int l, int r, vector<vector<int>> &dp)
{
    if (l == r)
    {
        return 1;
    }
    if (l == r - 1)
    {
        if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']'))
        {
            return 0;
        }
        return 2;
    }
    // l...r字符数量 >= 3
    if (dp[l][r] != -1)
    {
        return dp[l][r];
    }
    // 可能性1 : [l]、[r]本来就是配对的
    int p1 = INT_MAX;
    if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']'))
    {
        p1 = f(s, l + 1, r - 1, dp);
    }
    // 可能性2 : 基于每个可能的划分点，做左右划分
    int p2 = INT_MAX;
    for (int m = l; m < r; m++)
    {
        p2 = min(p2, f(s, l, m, dp) + f(s, m + 1, r, dp));
    }
    int ans = min(p1, p2);
    dp[l][r] = ans;
    return ans;
}

// 时间复杂度O(n^3)
int compute(string s)
{
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return f(s, 0, n - 1, dp);
}

int main()
{
    string s;
    cin >> s;
    cout << compute(s) << endl;
    return 0;
}