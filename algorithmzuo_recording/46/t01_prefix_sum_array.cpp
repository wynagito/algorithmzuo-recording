// 利用前缀和快速得到区域累加和
// 测试链接 : https://leetcode.cn/problems/range-sum-query-immutable/

class NumArray
{
public:
    int *sum;
    NumArray(vector<int> &nums)
    {
        // sum[i]表示前i个元素的累加和 0...i-1
        // sum[0]=0
        sum = new int[nums.size() + 1];
        for (int i = 1; i <= nums.size(); i++)
        {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
    }

    int sumRange(int left, int right)
    {
        return sum[right + 1] - sum[left];
    }
};