// 翻转对数量
// 给定一个数组 nums ，
// 如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个翻转对
// 你需要返回给定数组中的翻转对的数量
// 测试链接 : https://leetcode.cn/problems/reverse-pairs/
#include <vector>

using namespace std;

class Solution
{
public:
    int help[50001]; // 归并排序数组

    int reversePairs(vector<int> &arr)
    {
        return counts(arr, 0, arr.size() - 1);
    }
    // 结果比较大，用int会溢出的，所以返回long类型
    // 特别注意溢出这个点，笔试常见坑
    // 返回arr[l...r]范围上的翻转对数量，同时请把arr[l..r]变有序
    // 时间复杂度O(n * logn)
    int counts(vector<int> &arr, int l, int r)
    {
        if (l == r)
        {
            return 0;
        }
        int m = (l + r) / 2;
        // 左 + 右 + 跨越左右
        return counts(arr, l, m) + counts(arr, m + 1, r) + merge(arr, l, m, r);
    }

    // 返回跨左右产生的反转对数量，左侧有序、右侧有序，让左右两侧整体有序
    // arr[l...m] arr[m+1...r]
    int merge(vector<int> &arr, int l, int m, int r)
    {
        int ans = 0;
        for (int i = l, j = m + 1; i <= m; i++)
        {
            while (j <= r && (long long)(arr[i]) > (long long)(arr[j]) * 2)
            {
                j++;
            }
            ans += (j - m - 1);
        }

        // 归并排序
        int i = l;
        int a = l;
        int b = m + 1;
        while (a <= m && b <= r)
        {
            help[i++] = arr[a] > arr[b] ? arr[b++] : arr[a++];
        }
        while (a <= m)
        {
            help[i++] = arr[a++];
        }
        while (b <= r)
        {
            help[i++] = arr[b++];
        }
        for (i = l; i <= r; i++)
        {
            arr[i] = help[i];
        }
        return ans;
    }
};