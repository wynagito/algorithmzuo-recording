// 分割数组的最大值(画匠问题)
// 给定一个非负整数数组 nums 和一个整数 m
// 你需要将这个数组分成 m 个非空的连续子数组。
// 设计一个算法使得这 m 个子数组各自和的最大值最小。
// 测试链接 : https://leetcode.cn/problems/split-array-largest-sum/

class Solution
{
public:
    int splitArray(vector<int> &nums, int k)
    {
        long long sum = 0;
        for (int num : nums)
        {
            sum += num;
        }
        long long ans = 0;
        // [0,sum]二分
        for (long l = 0, r = sum, m, need; l <= r;)
        {
            // 中点m
            m = l + ((r - l) >> 1);
            // 每个子数组累加和越小，划分的部分越多
            // 必须让数组每一部分的累加和 <= m，请问划分成几个部分才够!
            need = f(nums, m);
            if (need <= k)
            {
                // 达标
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        return (int)ans;
    }

    // 必须让数组arr每一部分的累加和 <= limit，请问划分成几个部分才够!
    // 返回需要的部分数量
    int f(vector<int> &arr, long limit)
    {
        int parts = 1;
        int sum = 0;
        // 连续子数组 : 从头到尾遍历一遍即可
        for (int num : arr)
        {
            if (num > limit)
            {
                return INT_MAX;
            }
            if (sum + num > limit)
            {
                parts++;
                sum = num;
            }
            else
            {
                sum += num;
            }
        }
        return parts;
    }
};