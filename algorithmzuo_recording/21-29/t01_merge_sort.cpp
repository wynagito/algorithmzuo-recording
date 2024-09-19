// 测试链接 : https://www.luogu.com.cn/problem/P1177

#include <iostream>

using namespace std;

const int MAXN = 100001;
int arr[MAXN],help[MAXN];
int n;

// l....r 一共有n个数
// O(n)
void merge(int l, int m, int r)
{
    int i = l;
    int a = l;
    int b = m + 1;
    while (a <= m && b <= r)
    {
        help[i++] = arr[a] <= arr[b] ? arr[a++] : arr[b++];
    }
    // 左侧指针、右侧指针，必有一个越界、另一个不越界
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
}

// 归并排序递归版
// 假设l...r一共n个数
// T(n) = 2 * T(n/2) + O(n)
// a = 2, b = 2, c = 1
// 根据master公式，时间复杂度O(n * logn)
// master公式
//     a. 所有子问题规模相同的递归才能用master公式，T(n) = a * T(n/b) + O(n^c)，a、b、c都是常数
//     b. 如果log(b,a)  < c，复杂度为：O(n^c)
//     c. 如果log(b,a)  > c，复杂度为：O(n^log(b,a))
//     d. 如果log(b,a) == c，复杂度为：O(n^c * logn)
// 一个补充
//     T(n) = 2*T(n/2) + O(n*logn)，时间复杂度是O(n * ((logn)的平方))，证明过程比较复杂，记住即可
// 空间复杂度O(n)
void mergeSort1(int l, int r)
{
    if (l == r)
    {
        return;
    }
    int m = (l + r) / 2;
    mergeSort1(l, m);
    mergeSort1(m + 1, r);
    merge(l, m, r);
}

// 归并排序非递归版
// 时间复杂度O(n * logn)
// 空间复杂度O(n)
void mergeSort2()
{
    // 一共发生O(logn)次
    for (int l, m, r, step = 1; step < n; step <<= 1)
    {
        // 内部分组merge，时间复杂度O(n)
        l = 0;
        while (l < n)
        {
            m = l + step - 1;
            if (m + 1 >= n)
            {
                break;
            }
            r = min(l + (step << 1) - 1, n - 1);
            merge(l, m, r);
            l = r + 1;
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
    mergeSort1(0, n - 1);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
