// 平衡子序列的最大和
// 给定一个长度为n的数组nums，下面定义平衡子序列
// 如果下标i和下标j被选进了子序列，i在j的左边
// 那么必须有nums[j] - nums[i] >= j - i
// 如果一个子序列中任意的两个下标都满足上面的要求，那子序列就是平衡的
// 返回nums所有平衡子序列里，最大的累加和是多少
// 1 <= n <= 10^5
// -10^9 <= nums[i] <= +10^9
// 测试链接 : https://leetcode.cn/problems/maximum-balanced-subsequence-sum/

#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Solution
{
public:
    static const int MAXN = 100001;
    int sortarr[MAXN];
    long long tree[MAXN];
    int n, m;

    long long maxBalancedSubsequenceSum(vector<int> &nums)
    {
        build(nums);
        long long pre;
        for (int i = 0; i < n; i++)
        {
            // k的含义为当前的指标是第几号指标
            int k = rank(nums[i] - i);
            // dp[1号..k号指标]中的最大值是多少
            pre = maxfunc(k);
            if (pre < 0)
            {
                // 如果之前的最好情况是负数，那么不要之前的数了
                // 当前数字自己单独形成平衡子序列
                // 去更新dp[k号指标]，看能不能变得更大
                update(k, nums[i]);
            }
            else
            {
                // 如果之前的最好情况不是负数，那么和当前数字一起形成更大的累加和
                // 去更新dp[k号指标]，看能不能变得更大
                update(k, pre + nums[i]);
            }
        }
        // 返回dp[1号..m号指标]中的最大值
        return maxfunc(m);
    }

    void build(vector<int> &nums)
    {
        n = nums.size();
        for (int i = 0; i < n; i++)
        {
            sortarr[i + 1] = nums[i] - i;
        }
        sortarr[0] = INT_MIN;               // 避免排序时出现undefined behavior
        sort(sortarr + 1, sortarr + n + 1); // 排序时使用标准库提供的sort函数
        m = 1;
        for (int i = 2; i <= n; i++)
        {
            if (sortarr[m] != sortarr[i])
            {
                sortarr[++m] = sortarr[i];
            }
        }
        fill(tree + 1, tree + m + 1, LLONG_MIN); // 初始化树数组
    }

    // 当前的指标值是v，返回这是第几号指标
    int rank(int v)
    {
        int left = 1, right = m, ans = 0;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (sortarr[mid] <= v)
            {
                ans = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return ans;
    }

    // dp[i号指标]，当前算出的值是v
    void update(int i, long long v)
    {
        while (i <= m)
        {
            tree[i] = max(tree[i], v);
            i += i & -i;
        }
    }

    // dp[1..i]，最大值多少返回
    long long maxfunc(int i)
    {
        long long ans = LLONG_MIN;
        while (i > 0)
        {
            ans = max(ans, tree[i]);
            i -= i & -i;
        }
        return ans;
    }
};
