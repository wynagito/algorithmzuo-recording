// 巫师力量和
// 题目可以简化为如下的描述
// 给定一个长度为n的数组arr，下标从0开始
// 任何一个子数组的指标为，子数组累加和 * 子数组中最小值
// 返回arr中所有子数组指标的累加和，答案对1000000007取余
// 1 <= n <= 10^5
// 1 <= arr[i] <= 10^9
// 测试链接 : https://leetcode.cn/problems/sum-of-total-strength-of-wizards/

#include <vector>
using namespace std;

class Solution
{
public:
    static const int MOD = 1000000007;
    //l=2 m=4 r=6
    // 3-4 3-5 4-4 4-5  
    int sum(const vector<int> &arr, const vector<int> &sumsum, int l, int m, int r)
    {
        long long left = sumsum[r - 1];
        if (m - 1 >= 0)
        {
            left = (left - sumsum[m - 1] + MOD) % MOD;
        }
        //(0-4 0-5) * 2
        left = (left * (m - l)) % MOD;

        long long right = 0;
        if (m - 1 >= 0)
        {
            right = (right + sumsum[m - 1]) % MOD;
        }
        if (l - 1 >= 0)
        {
            right = (right - sumsum[l - 1] + MOD) % MOD;
        }
        // (0-2 0-3) * 2
        right = (right * (r - m)) % MOD;
        // 0-4 - 0-2 --> 3-4
        // 0-4 - 0-3 --> 4-4
        // 0-5 - 0-2 --> 3-5
        // 0-5 - 0-3 --> 4-5
        return (int)(((left - right + MOD) % MOD * arr[m]) % MOD);
    }

    int totalStrength(vector<int> &arr)
    {
        int n = arr.size();
        long long pre = arr[0] % MOD;
        // sumsum[i]表示0-0 0-1 0-2 ... 0-i的子数组的累加和
        vector<int> sumsum(n);
        sumsum[0] = pre;

        for (int i = 1; i < n; i++)
        {
            pre = (pre + arr[i]) % MOD;
            sumsum[i] = (sumsum[i - 1] + pre) % MOD;
        }

        vector<int> stack(n);
        int size = 0;
        long long ans = 0;

        for (int i = 0; i < n; i++)
        {
            // 大压小
            while (size > 0 && arr[stack[size - 1]] >= arr[i])
            {
                int m = stack[--size];
                int l = size > 0 ? stack[size - 1] : -1;
                ans = (ans + sum(arr, sumsum, l, m, i)) % MOD;
            }
            stack[size++] = i;
        }

        while (size > 0)
        {
            int m = stack[--size];
            int l = size > 0 ? stack[size - 1] : -1;
            ans = (ans + sum(arr, sumsum, l, m, n)) % MOD;
        }

        return (int)ans;
    }
};
