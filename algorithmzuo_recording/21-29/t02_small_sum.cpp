// 归并分治原理：
// 1）思考一个问题在大范围上的答案，是否等于，左部分的答案 + 右部分的答案 + 跨越左右产生的答案
// 2）计算“跨越左右产生的答案”时，如果加上左、右各自有序这个设定，会不会获得计算的便利性
// 3）如果以上两点都成立，那么该问题很可能被归并分治解决（话不说满，因为总有很毒的出题人）
// 4）求解答案的过程中只需要加入归并排序的过程即可，因为要让左、右各自有序，来获得计算的便利性

// 小和问题
// 假设数组 s = [ 1, 3, 5, 2, 4, 6]
// 在s[0]的左边所有 <= s[0]的数的总和为0
// 在s[1]的左边所有 <= s[1]的数的总和为1
// 在s[2]的左边所有 <= s[2]的数的总和为4
// 在s[3]的左边所有 <= s[3]的数的总和为1
// 在s[4]的左边所有 <= s[4]的数的总和为6
// 在s[5]的左边所有 <= s[5]的数的总和为15
// 所以s数组的“小和”为 : 0 + 1 + 4 + 1 + 6 + 15 = 27
// 给定一个数组arr，实现函数返回arr的“小和”
// 测试链接 : https://www.nowcoder.com/practice/edfe05a1d45c4ea89101d936cac32469
#include <iostream>

using namespace std;

const int MAXN = 100001;

int arr[MAXN], help[MAXN], n;

// 返回跨左右产生的小和累加和，左侧有序、右侧有序，让左右两侧整体有序
// arr[l...m] arr[m+1...r]
long long merge(int l, int m, int r)
{
    // 统计部分
    long long ans = 0;
    for (int j = m + 1, i = l, sum = 0; j <= r; j++)
    {
        while (i <= m && arr[i] <= arr[j])
        {
            sum += arr[i++];
        }
        ans += sum;
    }
    // 正常merge
    int i = l;
    int a = l;
    int b = m + 1;
    while (a <= m && b <= r)
    {
        help[i++] = arr[a] <= arr[b] ? arr[a++] : arr[b++];
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

// 结果比较大，用int会溢出的，所以返回long类型
// 特别注意溢出这个点，笔试常见坑
// 返回arr[l...r]范围上，小和的累加和，同时请把arr[l..r]变有序
// 时间复杂度O(n * logn)
long long smallSum(int l, int r)
{
    if (l == r)
    {
        return 0;
    }
    int m = (l + r) / 2;
    return smallSum(l, m) + smallSum(m + 1, r) + merge(l, m, r);
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    cout << smallSum(1, n) << endl;
    return 0;
}
