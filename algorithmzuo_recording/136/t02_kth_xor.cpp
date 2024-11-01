// 第k小的异或和
// 给定一个长度为n的数组arr，arr中都是long类型的非负数，可能有重复值
// 在这些数中选取任意个，至少要选一个数字
// 可以得到很多异或和，假设异或和的结果去重
// 返回第k小的异或和
// 1 <= n <= 10^5
// 0 <= arr[i] <= 2^50
// 1 <= k <= 2^50
// 测试链接 : https://loj.ac/p/114

#include <iostream>

using namespace std;

const int MAXN = 100001, BIT = 50;

long arr[MAXN];

int len, n, m;

bool zero;

// 高斯消元
void compute()
{
    len = 1;
    for (long i = BIT; i >= 0; i--)
    {
        for (int j = len; j <= n; j++)
        {
            if ((arr[j] & (1L << i)) != 0)
            {
                swap(arr[j], arr[len]);
                break;
            }
        }
        if ((arr[len] & (1L << i)) != 0)
        {
            for (int j = 1; j <= n; j++)
            {
                if (j != len && (arr[j] & (1L << i)) != 0)
                {
                    arr[j] ^= arr[len];
                }
            }
            len++;
        }
    }
    len--;
    zero = len != n;
}

// 返回第k小的异或和
long query(long k)
{
    if (zero && k == 1)
    {
        return 0;
    }
    if (zero)
    {
        k--;
    }
    if (k >= 1L << len)
    {
        return -1;
    }
    long ans = 0;
    for (int i = len, j = 0; i >= 1; i--, j++)
    {
        if ((k & (1L << j)) != 0)
        {
            ans ^= arr[i];
        }
    }
    return ans;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    compute();
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        long x;
        cin >> x;
        cout << query(x) << endl;
    }
    return 0;
}