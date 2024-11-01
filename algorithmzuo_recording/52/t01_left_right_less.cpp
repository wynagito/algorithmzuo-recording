// 单调栈最经典的用法是解决如下问题：
// 每个位置都求：
// 0）当前位置的 左侧比当前位置的数字小，且距离最近的位置 在哪
// 1）当前位置的 右侧比当前位置的数字小，且距离最近的位置 在哪
// 或者
// 每个位置都求：
// 0）当前位置的 左侧比当前位置的数字大，且距离最近的位置 在哪
// 1）当前位置的 右侧比当前位置的数字大，且距离最近的位置 在哪
// 用单调栈的方式可以做到：求解过程中，单调栈所有调整的总代价为O(n)，单次操作的均摊代价为O(1)

// 单调栈求每个位置左右两侧，离当前位置最近、且值严格小于的位置
// 给定一个可能含有重复值的数组 arr
// 找到每一个 i 位置左边和右边离 i 位置最近且值比 arr[i] 小的位置
// 返回所有位置相应的信息。
// 输入描述：
// 第一行输入一个数字 n，表示数组 arr 的长度。
// 以下一行输入 n 个数字，表示数组的值
// 输出描述：
// 输出n行，每行两个数字 L 和 R，如果不存在，则值为 -1，下标从 0 开始。
// 测试链接 : https://www.nowcoder.com/practice/2a2c00e7a88a498693568cef63a4b7bb

#include <iostream>

using namespace std;

const int MAXN = 1000001;

int arr[MAXN], stack[MAXN], ans[MAXN][2];

int n, r;

// arr[0...n-1]
void compute()
{
    r = 0;
    int cur;
    // 遍历阶段
    // 2 3 4 3 2
    // final ans:
    // -1 0 -1
    // 0 1 4
    // 1 2 3
    // 0 3 4
    // -1 4 -1

    for (int i = 0; i < n; i++)
    {
        // i -> arr[i]
        // 严格大压小 确保左侧一定比当前位置小
        while (r > 0 && arr[stack[r - 1]] >= arr[i])
        {
            cur = stack[--r];
            // cur当前弹出的位置，左边最近且小
            ans[cur][0] = r > 0 ? stack[r - 1] : -1;
            ans[cur][1] = i;
        }
        stack[r++] = i;
    }
    // 左侧正确 右侧要修改
    // -1 0 4
    // 0 1 3
    // 1 2 3
    // 0 3 4
    // -1 4 -1

    // 清算阶段
    while (r > 0)
    {
        cur = stack[--r];
        ans[cur][0] = r > 0 ? stack[r - 1] : -1;
        ans[cur][1] = -1;
    }

    // 修正阶段
    // 左侧的答案不需要修正一定是正确的，只有右侧答案需要修正
    // 从右往左修正，n-1位置的右侧答案一定是-1，不需要修正
    for (int i = n - 2; i >= 0; i--)
    {
        if (ans[i][1] != -1 && arr[ans[i][1]] == arr[i])
        {
            ans[i][1] = ans[ans[i][1]][1];
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    compute();
    for (int i = 0; i < n; i++)
    {
        cout << ans[i][0] << " " << ans[i][1] << endl;
    }
    return 0;
}