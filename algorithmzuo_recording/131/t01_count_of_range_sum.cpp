// 达标子数组的个数
// 给定一个长度为n的数组nums，给定两个整数lower和upper
// 子数组达标的条件是累加和在[lower, upper]范围上
// 返回nums中有多少个达标子数组
// 1 <= n <= 10^5
// nums[i]可能是任意整数
// -10^5 <= lower <= upper <= +10^5
// 测试链接 : https://leetcode.cn/problems/count-of-range-sum/

#include <vector>
#include <algorithm>

using namespace std;

class Solution1
{
public:
    static const int MAXN = 100001;
    long sum[MAXN];
    long help[MAXN];
    int low, up;

    int countRangeSum(vector<int> &nums, int lower, int upper)
    {
        int n = nums.size();
        sum[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            sum[i] = sum[i - 1] + nums[i];
        }
        low = lower;
        up = upper;
        return f(0, n - 1);
    }

    int f(int l, int r)
    {
        if (l == r)
        {
            return low <= sum[l] && sum[l] <= up ? 1 : 0;
        }
        int m = (l + r) / 2;
        return f(l, m) + f(m + 1, r) + merge(l, m, r);
    }

    int merge(int l, int m, int r)
    {
        int ans = 0;
        int wl = l, wr = l;
        long long maxval, minval;
        for (int i = m + 1; i <= r; i++)
        {
            maxval = sum[i] - low;
            minval = sum[i] - up;
            // 有效窗口是 [wl, wr)，左闭右开
            while (wr <= m && sum[wr] <= maxval)
            {
                wr++;
            }
            while (wl <= m && sum[wl] < minval)
            {
                wl++;
            }
            ans += wr - wl;
        }
        // 正常排序的合并过程
        int p1 = l;
        int p2 = m + 1;
        int i = l;
        while (p1 <= m && p2 <= r)
        {
            help[i++] = sum[p1] <= sum[p2] ? sum[p1++] : sum[p2++];
        }
        while (p1 <= m)
        {
            help[i++] = sum[p1++];
        }
        while (p2 <= r)
        {
            help[i++] = sum[p2++];
        }
        for (i = l; i <= r; i++)
        {
            sum[i] = help[i];
        }
        return ans;
    }
};

class Solution2
{
public:
    static const int MAXN = 100002;
    int n, m;
    long long sortarr[MAXN];
    int tree[MAXN];

    // 树状数组 + 离散化的解法，理解难度较低
    int countRangeSum(vector<int> &nums, int lower, int upper)
    {
        build(nums);
        long long sum = 0;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            sum += nums[i];
            ans += sumfunc(rank(sum - lower)) - sumfunc(rank(sum - upper - 1));
            if (lower <= sum && sum <= upper)
            {
                ans++;
            }
            add(rank(sum), 1);
        }
        return ans;
    }

    void build(vector<int> &nums)
    {
        // 生成前缀和数组
        n = nums.size();
        for (int i = 1, j = 0; i <= n; i++, j++)
        {
            sortarr[i] = sortarr[i - 1] + nums[j];
        }
        // 前缀和数组排序和去重，最终有m个不同的前缀和
        sort(sortarr + 1, sortarr + n + 1);
        m = 1;
        for (int i = 2; i <= n; i++)
        {
            if (sortarr[m] != sortarr[i])
            {
                sortarr[++m] = sortarr[i];
            }
        }
        // 初始化树状数组，下标1~m
        fill(tree + 1, tree + m + 1, 0);
    }

    // 返回 <=v 并且尽量大的前缀和是第几号前缀和
    int rank(long long v)
    {
        int left = 1, right = m, mid;
        int ans = 0;
        while (left <= right)
        {
            mid = (left + right) / 2;
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

    // 树状数组模版代码，没有任何修改
    // i号前缀和，个数增加c个
    void add(int i, int c)
    {
        while (i <= m)
        {
            tree[i] += c;
            i += i & -i;
        }
    }

    // 查询1~i号前缀和一共有几个
    int sumfunc(int i)
    {
        int ans = 0;
        while (i > 0)
        {
            ans += tree[i];
            i -= i & -i;
        }
        return ans;
    }
};
