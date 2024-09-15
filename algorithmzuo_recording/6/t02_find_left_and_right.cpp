#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

// 随机生成数组
vector<int> randomArray(int n, int v)
{
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % v + 1; // 生成 1 到 v 的随机数
    }
    return arr;
}

// 保证arr有序，才能用这个方法
int left(const vector<int> &arr, int num)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] >= num)
        {
            return i;
        }
    }
    return -1; // 如果没有找到
}

int right(const vector<int> &arr, int num)
{
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        if (arr[i] <= num)
        {
            return i;
        }
    }
    return -1; // 如果没有找到
}

// 保证arr有序，才能用这个方法
// 有序数组中找 >= num 的最左位置
int findLeft(const vector<int> &arr, int num)
{
    int l = 0, r = arr.size() - 1, m = 0;
    int ans = -1;
    while (l <= r)
    {
        m = l + ((r - l) >> 1);
        if (arr[m] >= num)
        {
            ans = m;
            r = m - 1; // 找到更左边的
        }
        else
        {
            l = m + 1;
        }
    }
    return ans;
}

// 保证arr有序，才能用这个方法
// 有序数组中找 <= num 的最右位置
int findRight(const vector<int> &arr, int num)
{
    int l = 0, r = arr.size() - 1, m = 0;
    int ans = -1;
    while (l <= r)
    {
        m = l + ((r - l) >> 1);
        if (arr[m] <= num)
        {
            ans = m;
            l = m + 1; // 找到更右边的
        }
        else
        {
            r = m - 1;
        }
    }
    return ans;
}

int main()
{
    const int N = 100;
    const int V = 1000;
    const int testTime = 500000;
    cout << "测试开始" << endl;

    for (int i = 0; i < testTime; i++)
    {
        int n = rand() % N; // 随机生成数组大小
        vector<int> arr = randomArray(n, V);
        sort(arr.begin(), arr.end()); // 排序
        int num = rand() % V;         // 随机生成一个数

        if (left(arr, num) != findLeft(arr, num))
        {
            cout << "出错了!" << endl; // 测试出错
        }
        if (right(arr, num) != findRight(arr, num))
        {
            cout << "出错了!" << endl; // 测试出错
        }
    }

    cout << "测试结束" << endl;
    return 0;
}
