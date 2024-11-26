// 约瑟夫环问题加强
// 一共有1~n这些点，组成首尾相接的环，游戏一共有n-1轮，每轮给定一个数字arr[i]
// 第一轮游戏中，1号点从数字1开始报数，哪个节点报到数字arr[1]，就删除该节点
// 然后下一个节点从数字1开始重新报数，游戏进入第二轮
// 第i轮游戏中，哪个节点报到数字arr[i]，就删除该节点
// 然后下一个节点从数字1开始重新报数，游戏进入第i+1轮
// 最终环上会剩下一个节点, 返回该节点的编号
// 1 <= n, arr[i] <= 10^6
// 来自真实大厂笔试，对数器验证

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int joseph1(int n, vector<int> &arr)
{
    if (n == 1)
    {
        return 1;
    }
    vector<int> next(n + 1);
    for (int i = 1; i < n; i++)
    {
        next[i] = i + 1;
    }
    next[n] = 1;
    int pre = n, cur = 1;
    for (int i = 1; i < n; i++)
    {
        for (int cnt = 1; cnt < arr[i]; cnt++)
        {
            pre = cur;
            cur = next[cur];
        }
        next[pre] = next[cur];
        cur = next[cur];
    }
    return cur;
}

// 正式方法
// 时间复杂度O(n)
int joseph2(int n, vector<int> &arr)
{
    if (n == 1)
    {
        return 1;
    }
    int ans = 1;
    for (int c = 2, i = n - 1; c <= n; c++, i--)
    {
        ans = (ans + arr[i] - 1) % c + 1;
    }
    return ans;
}

// 随机生成每轮报数
// 为了测试
vector<int> randomArray(int n, int v)
{
    vector<int> arr(n);
    for (int i = 1; i < n; i++)
    {
        arr[i] = rand() % v + 1;
    }
    return arr;
}

// 对数器
// 为了测试
int main()
{
    srand(static_cast<unsigned int>(time(0))); // 初始化随机种子
    int N = 100;
    int V = 500;
    int test = 10000;
    cout << "测试开始" << endl;
    for (int i = 1; i <= test; i++)
    {
        int n = rand() % N + 1; // 随机生成1到N的n
        vector<int> arr = randomArray(n, V);
        int ans1 = joseph1(n, arr);
        int ans2 = joseph2(n, arr);
        if (ans1 != ans2)
        {
            cout << "出错了!" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}