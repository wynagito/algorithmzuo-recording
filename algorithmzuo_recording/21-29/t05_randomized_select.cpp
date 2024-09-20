// 无序数组中寻找第K大的数
// 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
// 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
// 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。
// 测试链接 : https://leetcode.cn/problems/kth-largest-element-in-an-array/

#include <vector>
#include <ctime>

using namespace std;

class Solution
{
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        // 升序排列
        return randomizedSelect(nums, nums.size() - k);
    }

    int randomizedSelect(vector<int> &arr, int i)
    {
        int ans = 0;
        for (int l = 0, r = arr.size() - 1; l <= r;)
        {
            // 随机这一下，常数时间比较大
            // 但只有这一下随机，才能在概率上把时间复杂度收敛到O(n)
            partition(arr, l, r, arr[l + (int)(rand() % (r - l + 1))]);
            // 因为左右两侧只需要走一侧
            // 所以不需要临时变量记录全局的first、last
            // 直接用即可
            if (i < first)
            {
                r = first - 1;
            }
            else if (i > last)
            {
                l = last + 1;
            }
            else
            {
                ans = arr[i];
                break;
            }
        }
        return ans;
    }
    // 荷兰国旗问题
    int first, last;

    // 已知arr[l....r]范围上一定有x这个值
    // 划分数组 <x放左边，==x放中间，>x放右边
    // 把全局变量first, last，更新成==x区域的左右边界

    void swap(vector<int> &arr, int i, int j)
    {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    void partition(vector<int> &arr, int l, int r, int x)
    {
        first = l;
        last = r;
        int i = l;
        // i 从左到右开始扫描
        while (i <= last)
        {
            if (arr[i] == x)
            {
                i++;
            }
            else if (arr[i] < x)
            {
                // first 是已扫描过的
                // 都++
                swap(arr, first++, i++);
            }
            else
            {
                // last 是未扫描的
                // i 需要再次检验
                swap(arr, i, last--);
            }
        }
    }
};
