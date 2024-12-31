// 删除至少几个字符可以变成另一个字符串的子串
// 给定两个字符串s1和s2
// 返回s1至少删除多少字符可以成为s2的子串
// 对数器验证

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

// 生成 s1 的所有子序列
void f(string s1, int i, string path, vector<string> &list)
{
    if (i == s1.size())
    {
        list.push_back(path);
    }
    else
    {
        f(s1, i + 1, path, list);
        f(s1, i + 1, path + s1[i], list);
    }
};

// 暴力方法
int minDelete1(const string &s1, const string &s2)
{
    vector<string> list;

    f(s1, 0, "", list);

    // 排序 : 长度大的子序列先考虑
    // 因为如果长度大的子序列是s2的子串
    // 那么需要删掉的字符数量 = s1的长度 - s1子序列长度
    // 子序列长度越大，需要删掉的字符数量就越少
    // 所以长度大的子序列先考虑
    sort(list.begin(), list.end(), [](const string &a, const string &b)
         { return a.length() > b.length(); });

    // 检查 s2 是否包含某个子序列
    for (const string &str : list)
    {
        if (s2.find(str) != string::npos)
        {
            return s1.length() - str.length();
        }
    }

    return s1.length();
}

// 正式方法，动态规划
int minDelete2(const string &s1, const string &s2)
{
    int n = s1.size(), m = s2.size();
    // dp[i][j] 表示 s1 的前 i 个字符，至少删掉几个字符可以变成 s2 的前 j 个字符的任意后缀串
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        dp[i][0] = i; // 删除所有字符到空串
        for (int j = 1; j <= m; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = dp[i - 1][j] + 1;
            }
        }
    }

    int ans = INT_MAX;
    for (int j = 0; j <= m; ++j)
    {
        ans = min(ans, dp[n][j]);
    }

    return ans;
}

// 生成随机字符串
string randomString(int n, int v)
{
    string ans;
    for (int i = 0; i < n; ++i)
    {
        ans += char('a' + rand() % v);
    }
    return ans;
}

// 主函数
int main()
{
    // 测试的数据量比较小
    // 那是因为数据量大了，暴力方法过不了
    // 但是这个数据量足够说明正式方法是正确的
    srand(time(0)); // 初始化随机种子

    int n = 12; // 最大字符串长度
    int v = 3;  // 字符集种类
    int testTime = 20000;

    cout << "测试开始" << endl;
    for (int i = 0; i < testTime; ++i)
    {
        int len1 = rand() % n + 1;
        int len2 = rand() % n + 1;

        string s1 = randomString(len1, v);
        string s2 = randomString(len2, v);

        int ans1 = minDelete1(s1, s2);
        int ans2 = minDelete2(s1, s2);

        if (ans1 != ans2)
        {
            cout << "出错了!" << endl;
            cout << "s1: " << s1 << ", s2: " << s2 << endl;
            cout << "暴力答案: " << ans1 << ", 动态规划答案: " << ans2 << endl;
            break;
        }
    }
    cout << "测试结束" << endl;

    return 0;
}
