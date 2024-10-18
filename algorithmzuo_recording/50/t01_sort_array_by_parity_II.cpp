// 设置两个指针的技巧，其实这种说法很宽泛，似乎 没什么可总结的
// 1）有时候所谓的双指针技巧，就单纯是代码过程用双指针的形式表达出来而已。
//    没有单调性（贪心）方面的考虑
// 2）有时候的双指针技巧包含单调性（贪心）方面的考虑，牵扯到可能性的取舍。
//    对分析能力的要求会变高。其实是先有的思考和优化，然后代码变成了 双指针的形式。
// 3）所以，双指针这个“皮”不重要，分析题目单调性（贪心）方面的特征，这个能力才重要。

// 常见的双指针类型：
// 1）同向双指针
// 2）快慢双指针
// 3）从两头往中间的双指针
// 4）其他

// 按奇偶排序数组II
// 给定一个非负整数数组 nums。nums 中一半整数是奇数 ，一半整数是偶数
// 对数组进行排序，以便当 nums[i] 为奇数时，i也是奇数
// 当 nums[i] 为偶数时， i 也是 偶数
// 你可以返回 任何满足上述条件的数组作为答案
// 测试链接 : https://leetcode.cn/problems/sort-array-by-parity-ii/

class Solution
{
public:
    vector<int> sortArrayByParityII(vector<int> &nums)
    {
        int n = nums.size();
        for (int odd = 1, even = 0; odd < n && even < n;)
        {
            if ((nums[n - 1] & 1) == 1)
            {
                swap(nums[odd], nums[n - 1]);
                odd += 2;
            }
            else
            {
                swap(nums[even], nums[n - 1]);
                even += 2;
            }
        }
        return nums;
    }
};