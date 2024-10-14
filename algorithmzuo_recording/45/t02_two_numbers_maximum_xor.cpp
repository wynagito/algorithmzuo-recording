// 数组中两个数的最大异或值
// 给你一个整数数组 nums ，返回 nums[i] XOR nums[j] 的最大运算结果，其中 0<=i<=j<=n
// 1 <= nums.length <= 2 * 10^5
// 0 <= nums[i] <= 2^31 - 1
// 测试链接 : https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/

class Solution
{
public:
    // 前缀树的做法
    // 好想
    int findMaximumXOR1(vector<int> &nums)
    {
        build(nums);
        int ans = 0;
        for (int num : nums)
        {
            ans = max(ans, maxXor(num));
        }
        return ans;
    }
    // 准备这么多静态空间就够了，实验出来的
    // 如果测试数据升级了规模，就改大这个值
    static const int MAXN = 3000001;

    int tree[MAXN][2];

    // 前缀树目前使用了多少空间
    int cnt;

    // 数字只需要从哪一位开始考虑
    int high;

    void build(vector<int> &nums)
    {
        cnt = 1;
        // 找个最大值
        int maxval = INT_MIN;
        for (int num : nums)
        {
            maxval = max(num, maxval);
        }
        // 计算数组最大值的二进制状态，有多少个前缀的0
        // 可以忽略这些前置的0，从left位开始考虑
        high = 31 - numberOfLeadingZeros(maxval);
        for (int num : nums)
        {
            insert(num);
        }
    }

    int numberOfLeadingZeros(int number)
    {
        int count = 0;
        if (number == 0)
            return 32; // 所有位都是零
        while ((number & (1 << 31)) == 0)
        {
            count++;
            number <<= 1; // 左移一位
        }
        return count;
    }

    void insert(int num)
    {
        int cur = 1;
        for (int i = high, path; i >= 0; i--)
        {
            path = (num >> i) & 1;
            if (tree[cur][path] == 0)
            {
                tree[cur][path] = ++cnt;
            }
            cur = tree[cur][path];
        }
    }

    int maxXor(int num)
    {
        // 最终异或的结果(尽量大)
        int ans = 0;
        // 前缀树目前来到的节点编号
        int cur = 1;
        for (int i = high, status, want; i >= 0; i--)
        {
            // status : num第i位的状态
            status = (num >> i) & 1;
            // want : num第i位希望遇到的状态
            want = status ^ 1;
            if (tree[cur][want] == 0)
            { // 询问前缀树，能不能达成
                // 不能达成
                want ^= 1;
            }
            // want变成真的往下走的路
            ans |= (status ^ want) << i;
            cur = tree[cur][want];
        }
        return ans;
    }

    // 用哈希表的做法
    // 难想
    int findMaximumXOR2(vector<int> &nums)
    {
        int maxval = INT_MIN;
        for (int num : nums)
        {
            maxval = max(num, maxval);
        }
        int ans = 0;
        unordered_set<int> set;
        for (int i = 31 - numberOfLeadingZeros(maxval); i >= 0; i--)
        {
            // ans : 31....i+1 已经达成的目标
            int better = ans | (1 << i);
            set.clear();
            for (int num : nums)
            {
                // num : 31.....i 这些状态保留，剩下全成0
                num = (num >> i) << i;
                set.insert(num);
                // num ^ 某状态 是否能 达成better目标，就在set中找 某状态 : better ^ num
                if (set.count(better ^ num))
                {
                    ans = better;
                    break;
                }
            }
        }
        return ans;
    }
};