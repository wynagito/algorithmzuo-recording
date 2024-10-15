// 返回无序数组中累加和为给定值的最长子数组长度
// 给定一个无序数组arr, 其中元素可正、可负、可0
// 给定一个整数aim
// 求arr所有子数组中累加和为aim的最长子数组长度
// 测试链接 : https://www.nowcoder.com/practice/36fb0fd3c656480c92b569258a1223d5

#include <iostream>
#include <unordered_map>

using namespace std;

const int MAXN = 100001;

int arr[MAXN];

int n, aim;

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
        if (map.count(sum - aim))
        {
            ans = max(ans, i - map[sum - aim]);
        }
        if (!map.count(sum))
        {
            map[sum] = i;
        }
    }
    return ans;
}

int main()
{
    cin >> n >> aim;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << compute() << endl;
    return 0;
}