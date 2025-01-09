// 使数组K递增的最少操作次数
// 给你一个下标从0开始包含n个正整数的数组arr，和一个正整数k
// 如果对于每个满足 k <= i <= n-1 的下标 i
// 都有 arr[i-k] <= arr[i] ，那么称 arr 是K递增的
// 每一次操作中，你可以选择一个下标i并将arr[i]改成任意正整数
// 请你返回对于给定的 k ，使数组变成K递增的最少操作次数
// 测试链接 : https://leetcode.cn/problems/minimum-operations-to-make-the-array-k-increasing/

class Solution
{
public:
    int nums[100001], ends[100001];
    int kIncreasing(vector<int> &arr, int k)
    {
        int n = arr.size();
        int ans = 0;
        for (int i = 0, size; i < k; i++)
        {
            size = 0;
            // 把每一组的数字放入容器
            for (int j = i; j < n; j += k)
            {
                nums[size++] = arr[j];
            }
            // 当前组长度 - 当前组最长不下降子序列长度 =
            // 当前组至少需要修改的数字个数
            ans += size - lengthOfNoDecreasing(size);
        }
        return ans;
    }
    // nums[0...size-1]中的最长不下降子序列长度
    int lengthOfNoDecreasing(int size)
    {
        int len = 0;
        for (int i = 0, find; i < size; i++)
        {
            find = bs(len, nums[i]);
            if (find == -1)
            {
                ends[len++] = nums[i];
            }
            else
            {
                ends[find] = nums[i];
            }
        }
        return len;
    }

    int bs(int len, int num)
    {
        int l = 0, r = len - 1, m, ans = -1;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (num < ends[m])
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
};