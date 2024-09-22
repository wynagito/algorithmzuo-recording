// 基数排序，acm练习风格
// 测试链接 : https://www.luogu.com.cn/problem/P1177

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int BASE = 10;
const int MAXN = 100001;
int arr[MAXN];
int help[MAXN];
int cnts[BASE];
int n;

// 返回number在BASE进制下有几位
int bits(int number)
{
    int ans = 0;
    while (number > 0)
    {
        ans++;
        number /= BASE;
    }
    return ans;
}
// 基数排序核心代码
// arr内要保证没有负数
// m是arr中最大值在BASE进制下有几位
void radixSort(int bits)
{
    for (int offset = 1; bits > 0; offset *= BASE, bits--)
    {
        fill(cnts, cnts + BASE, 0);
        for (int i = 0; i < n; i++)
        {
            // 数字提取某一位的技巧
            // arr[i] / offset 表示取整，arr[i] % offset 表示取余
            // (arr[i] / offset) % BASE 表示取arr[i] / offset的最后一位，并在BASE进制下取余
            cnts[(arr[i] / offset) % BASE]++;
        }
        for (int i = 1; i < BASE; i++)
        {
            cnts[i] += cnts[i - 1];
        }
        // 后缀数量分区的技巧
        // 从后往前遍历，将每个数字放到正确的位置 保证相对性
        for (int i = n - 1; i >= 0; i--)
        {
            // 前缀数量分区的技巧
            // 数字提取某一位的技巧
            help[--cnts[(arr[i] / offset) % BASE]] = arr[i];
        }
        for (int i = 0; i < n; i++)
        {
            arr[i] = help[i];
        }
    }
}

void sort()
{
    // 如果会溢出，那么要改用long类型数组来排序
    // 找到数组中的最小值
    int min_value = arr[0];
    for (int i = 1; i < n; i++)
    {
        min_value = min(min_value, arr[i]);
    }
    int max_value = 0;
    for (int i = 0; i < n; i++)
    {
        // 数组中的每个数字，减去数组中的最小值，就把arr转成了非负数组
        arr[i] -= min_value;
        max_value = max(max_value, arr[i]);
    }
    // 根据最大值在BASE进制下的位数，决定基数排序做多少轮
    radixSort(bits(max_value));
    // 数组中所有数都减去了最小值，所以最后不要忘了还原
    for (int i = 0; i < n; i++)
    {
        arr[i] += min_value;
    }
}

int main()
{

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    sort();

    for (int i = 0; i < n - 1; i++)
    {
        cout << arr[i] << " ";
    }
    cout << arr[n - 1] << endl;

    return 0;
}
