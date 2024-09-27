// 找到缺失的数字
// 测试链接 : https://leetcode.cn/problems/missing-number/

#include <vector>
using namespace std;

class Solution
{
public:
    int missingNumber(vector<int> &nums)
    {
        int n = nums.size();
        int a = 0, b = 0;
        for (int i = 0; i < n; ++i)
        {
            a ^= i;
            b ^= nums[i];
        }
        a ^= n;
        return a ^ b;
    }
};