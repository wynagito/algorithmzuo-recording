// 数位dp的尝试方式并不特殊，绝大多数都是线性展开，类似从左往右的尝试
// 之前的课已经讲过 大量在数组上进行线性展开的题目，数位dp是在数字的每一位上进行线性展开而已
// 不同的题目有不同的限制，解题核心在于：可能性的整理、排列组合的相关知识

// 解决数位dp的问题 推荐使用记忆化搜索的方式，可能性的展开会很好写，不必刻意追求进一步改写
// 递归写出来问题就解决了，位数多就挂缓存，位数不多甚至不挂缓存也能通过

// 统计各位数字都不同的数字个数
// 给你一个整数n，代表十进制数字最多有n位
// 如果某个数字，每一位都不同，那么这个数字叫做有效数字
// 返回有效数字的个数，不统计负数范围
// 测试链接 : https://leetcode.cn/problems/count-numbers-with-unique-digits/

class Solution
{
public:
    int countNumbersWithUniqueDigits(int n)
    {
        if (n == 0)
        {
            return 1;
        }
        int ans = 10;
        // 1 : 10
        // 2 : 9 * 9
        // 3 : 9 * 9 * 8
        // 4 : 9 * 9 * 8 * 7
        // ...都累加起来...
        for (int s = 9, i = 9, k = 2; k <= n; i--, k++)
        {
            s *= i;
            ans += s;
        }
        return ans;
    }
};