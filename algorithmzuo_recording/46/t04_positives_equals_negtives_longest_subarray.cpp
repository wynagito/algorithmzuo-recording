// 返回无序数组中正数和负数个数相等的最长子数组长度
// 给定一个无序数组arr，其中元素可正、可负、可0
// 求arr所有子数组中正数与负数个数相等的最长子数组的长度
// 测试链接 : https://www.nowcoder.com/practice/545544c060804eceaed0bb84fcd992fb

#include <iostream>
#include <unordered_map>

using namespace std;

const int MAXN = 100001;

int arr[MAXN];

int n, v;

// key : 某个前缀和
// value : 这个前缀和最早出现的位置
unordered_map<int, int> map;

int compute()
{
    map.clear();
    // 重要 : 0这个前缀和，一个数字也没有的时候，就存在了
    map[0] = -1;
    int ans = 0;
    for (int i = 0, sum = 0; i < n; i++)
    {
        sum += arr[i];
        if (map.count(sum))
        {
            ans = max(ans, i - map[sum]);
        }
        else
        {
            map[sum] = i;
        }
    }
    return ans;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> v;
        arr[i] = v != 0 ? (v > 0 ? 1 : -1) : 0;
    }
    cout << compute() << endl;
    return 0;
}