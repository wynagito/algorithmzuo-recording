// 最长数对链
// 给你一个由n个数对组成的数对数组pairs
// 其中 pairs[i] = [lefti, righti] 且 lefti < righti
// 现在，我们定义一种 跟随 关系，当且仅当 b < c 时
// 数对 p2 = [c, d] 才可以跟在 p1 = [a, b] 后面
// 我们用这种形式来构造 数对链
// 找出并返回能够形成的最长数对链的长度
// 测试链接 : https://leetcode.cn/problems/maximum-length-of-pair-chain/

class Solution
{
public:
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        return a[0] < b[0];
    }
    int findLongestChain(vector<vector<int>> &pairs)
    {
        int n = pairs.size();
        // 数对根据开始位置排序，从小到大
        // 结束位置无所谓！
        sort(pairs.begin(), pairs.end(), cmp);
        // 结尾的数值
        vector<int> ends(n);
        int len = 0;
        for (auto pair : pairs)
        {
            int find = bs(ends, len, pair[0]);
            if (find == -1)
            {
                ends[len++] = pair[1];
            }
            else
            {
                ends[find] = min(ends[find], pair[1]);
            }
        }
        return len;
    }
    int bs(vector<int> &ends, int len, int num)
    {
        int l = 0, r = len - 1, m, ans = -1;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (ends[m] >= num)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        return ans;
    }

    // 最优解利用贪心
    int findLongestChain2(vector<vector<int>> &pairs)
    {
        int pre = INT_MIN, ans = 0;
        sort(pairs.begin(), pairs.end(), [](vector<int> &a, vector<int> &b)
             { return a[1] < b[1]; });
        for (auto pair : pairs)
        {
            if (pre < pair[0])
            {
                pre = pair[1];
                ans++;
            }
        }
        return ans;
    }
};