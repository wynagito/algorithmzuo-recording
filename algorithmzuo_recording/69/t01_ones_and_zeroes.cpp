// 尝试函数有1个可变参数可以完全决定返回值，进而可以改出1维动态规划表的实现
// 同理
// 尝试函数有2个可变参数可以完全决定返回值，那么就可以改出2维动态规划的实现
// 同理
// 尝试函数有3个可变参数可以完全决定返回值，那么就可以改出3维动态规划的实现

// 大体过程都是：
// 写出尝试递归
// 记忆化搜索(从顶到底的动态规划)
// 严格位置依赖的动态规划(从底到顶的动态规划)
// 空间、时间的更多优化

// 一和零(多维费用背包)
// 给你一个二进制字符串数组 strs 和两个整数 m 和 n
// 请你找出并返回 strs 的最大子集的长度
// 该子集中 最多 有 m 个 0 和 n 个 1
// 如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集
// 测试链接 : https://leetcode.cn/problems/ones-and-zeroes/

class Solution
{
public:
    int findMaxForm1(vector<string> &strs, int m, int n)
    {
        return f1(strs, 0, m, n);
    }

    int zeros, ones;

    // 统计一个字符串中0的1的数量
    // 0的数量赋值给全局变量zeros
    // 1的数量赋值给全局变量ones
    void zerosAndOnes(string str)
    {
        zeros = 0;
        ones = 0;
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == '0')
            {
                zeros++;
            }
            else
            {
                ones++;
            }
        }
    }

    // strs[i....]自由选择，希望零的数量不超过z、一的数量不超过o
    // 最多能选多少个字符串
    int f1(vector<string> &strs, int i, int z, int o)
    {
        if (i == strs.size())
        {
            // 没有字符串了
            return 0;
        }
        // 不使用当前的strs[i]字符串
        int p1 = f1(strs, i + 1, z, o);
        // 使用当前的strs[i]字符串
        int p2 = 0;
        zerosAndOnes(strs[i]);
        if (zeros <= z && ones <= o)
        {
            p2 = 1 + f1(strs, i + 1, z - zeros, o - ones);
        }
        return max(p1, p2);
    }

    int findMaxForm2(vector<string> &strs, int m, int n)
    {
        vector<vector<vector<int>>> dp(strs.size(), vector<vector<int>>(m + 1, vector<int>(n + 1)));
        for (int i = 0; i < strs.size(); i++)
        {
            for (int z = 0; z <= m; z++)
            {
                for (int o = 0; o <= n; o++)
                {
                    dp[i][z][o] = -1;
                }
            }
        }
        return f2(strs, 0, m, n, dp);
    }

    int f2(vector<string> &strs, int i, int z, int o, vector<vector<vector<int>>> &dp)
    {
        if (i == strs.size())
        {
            return 0;
        }
        if (dp[i][z][o] != -1)
        {
            return dp[i][z][o];
        }
        int p1 = f2(strs, i + 1, z, o, dp);
        int p2 = 0;
        zerosAndOnes(strs[i]);
        if (zeros <= z && ones <= o)
        {
            p2 = 1 + f2(strs, i + 1, z - zeros, o - ones, dp);
        }
        int ans = max(p1, p2);
        dp[i][z][o] = ans;
        return ans;
    }

    int findMaxForm3(vector<string> &strs, int m, int n)
    {
        int len = strs.size();
        vector<vector<vector<int>>> dp(len, vector<vector<int>>(m + 1, vector<int>(n + 1)));
        for (int i = len - 1; i >= 0; i--)
        {
            zerosAndOnes(strs[i]);
            for (int z = 0, p1, p2; z <= m; z++)
            {
                for (int o = 0; o <= n; o++)
                {
                    p1 = dp[i + 1][z][o];
                    p2 = 0;
                    if (zeros <= z && ones <= o)
                    {
                        p2 = 1 + dp[i + 1][z - zeros][o - ones];
                    }
                    dp[i][z][o] = max(p1, p2);
                }
            }
        }
        return dp[0][m][n];
    }

    int findMaxForm4(vector<string> &strs, int m, int n)
    {
        // 代表i == len
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (string s : strs)
        {
            // 每个字符串逐渐遍历即可
            // 更新每一层的表
            // 和之前的遍历没有区别
            zerosAndOnes(s);
            for (int z = m; z >= zeros; z--)
            {
                for (int o = n; o >= ones; o--)
                {
                    dp[z][o] = max(dp[z][o], 1 + dp[z - zeros][o - ones]);
                }
            }
        }
        return dp[m][n];
    }
};