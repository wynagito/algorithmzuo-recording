// 子数组的最小值之和
// 给定一个整数数组 arr，找到 min(b) 的总和，其中 b 的范围为 arr 的每个（连续）子数组。
// 由于答案可能很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/sum-of-subarray-minimums/

class Solution
{
public:
    int MOD = 1000000007;
    int stack[30010];

    int sumSubarrayMins(vector<int> &arr)
    {
        long long ans = 0;
        int r = 0;
        // 注意课上讲的相等情况的修正
        for (int i = 0; i < arr.size(); i++)
        {
            while (r > 0 && arr[stack[r - 1]] >= arr[i])
            {
                int cur = stack[--r];
                int left = r == 0 ? -1 : stack[r - 1];
                // 位置 1 ... 4 ... 8
                //  值  2 ... 5 ... 4
                //  2...7 范围上的最小值是5
                //  那么要包含5的子数组的个数则是 (4-1)*(8-4)=12
                ans = (ans + (long long)(cur - left) * (i - cur) * arr[cur]) % MOD;
            }
            stack[r++] = i;
        }
        while (r > 0)
        {
            int cur = stack[--r];
            int left = r == 0 ? -1 : stack[r - 1];
            ans = (ans + (long long)(cur - left) * (arr.size() - cur) * arr[cur]) % MOD;
        }
        return (int)ans;
    }
};