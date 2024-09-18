// 统计重复个数
// 如果字符串x删除一些字符，可以得到字符串y，那么就说y可以从x中获得
// 给定s1和a，代表s1拼接a次，记为字符串x
// 给定s2和b，代表s2拼接b次，记为字符串y
// 现在把y拼接m次之后，得到的字符串依然可能从x中获得，返回尽可能大的m
// s1、s2只由小写字母组成
// 1 <= s1长度、s2长度 <= 100
// 1 <= a、b <= 10^6
// 测试链接 : https://leetcode.cn/problems/count-the-repetitions/

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

class Solution
{
public:
    // 该题的题解中有很多打败比例优异，但是时间复杂度不是最优的方法
    // 如果数据苛刻一些，就通过不了，所以一定要做到时间复杂度与a、b的值无关
    // 本方法时间复杂度O(s1长度 * s2长度)，一定是最优解，而且比其他方法更好理解
    int getMaxRepetitions(string str1, int a, string str2, int b)
    {
        int n = str1.length();
        int m = str2.length();
        // next[i][j] : 从i位置出发，至少需要多少长度，能找到j字符
        vector<vector<int>> next(n, vector<int>(26, -1));

        // 如果找不到 s2 的字符，在此返回 0
        if (!find(str1, n, next, str2))
        {
            return 0;
        }
        // st[i][p] : 从i位置出发，至少需要多少长度，可以获得2^p个s2
        vector<vector<long long>> st(n, vector<long long>(30, 0));

        // 计算 st[i][0]
        for (int i = 0; i < n; i++)
        {
            int cur = i;
            long long len = 0;
            for (char c : str2)
            {
                len += next[cur][c - 'a'];
                cur = (cur + next[cur][c - 'a']) % n;
            }
            st[i][0] = len;
        }

        // 计算 st[i][p]
        for (int p = 1; p <= 29; p++)
        {
            for (int i = 0; i < n; i++)
            {
                st[i][p] = st[i][p - 1] + st[(st[i][p - 1] + i) % n][p - 1];
            }
        }

        long long ans = 0;
        int start = 0;

        // 计算答案
        for (int p = 29; p >= 0; p--)
        {
            if (st[start % n][p] + start <= n * a)
            {
                ans += 1LL << p;
                start += st[start % n][p];
            }
        }
        return ans / b;
    }

private:
    // 时间复杂度O(s1长度 + s2长度)
    bool find(const string &s1, int n, vector<vector<int>> &next, const string &s2)
    {
        vector<int> right(26, -1);
        for (int i = n - 1; i >= 0; i--)
        {
            right[s1[i] - 'a'] = i + n;
        }
        for (int i = n - 1; i >= 0; i--)
        {
            right[s1[i] - 'a'] = i;
            for (int j = 0; j < 26; j++)
            {
                if (right[j] != -1)
                {
                    next[i][j] = right[j] - i + 1;
                }
                else
                {
                    next[i][j] = -1;
                }
            }
        }
        for (char c : s2)
        {
            if (next[0][c - 'a'] == -1)
            {
                return false;
            }
        }
        return true;
    }
};