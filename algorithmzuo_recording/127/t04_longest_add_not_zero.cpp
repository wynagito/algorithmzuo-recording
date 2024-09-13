// 相邻与结果不为0的最长子序列
// 给定一个长度为n的数组arr，你可以随意选择数字组成子序列
// 但是要求任意相邻的两个数&的结果不能是0，这样的子序列才是合法的
// 返回最长合法子序列的长度
// 1 <= n <= 10^5
// 0 <= arr[i] <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P4310

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100001;

int arr[MAXN];
int pre[32];

int compute(const vector<int> &arr)
{
    fill(pre, pre + 32, 0);
    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
        int num = arr[i];
        int cur = 1;
        for (int j = 0; j < 31; j++)
        {
            if (((num >> j) & 1) == 1)
            {
                cur = max(cur, pre[j] + 1);
            }
        }
        for (int j = 0; j < 31; j++)
        {
            if (((num >> j) & 1) == 1)
            {
                pre[j] = max(pre[j], cur);
            }
        }
    }

    int ans = 0;
    for (int j = 0; j < 31; j++)
    {
        ans = max(ans, pre[j]);
    }
    return ans;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << compute(arr) << endl;
    return 0;
}
