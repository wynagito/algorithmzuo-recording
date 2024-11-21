// 正整数倍的最小数位和
// 给定一个整数k，求一个k的正整数倍s，使得在十进制下，s的数位累加和最小
// 2 <= k <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/AT_arc084_b
// 测试链接 : https://atcoder.jp/contests/abc077/tasks/arc084_b

#include <iostream>
#include <deque>
#include <vector>
#include <cstring>

using namespace std;

const int MAXK = 100001; // 最大值
int k;                   // 输入的 k
bool visit[MAXK];        // 访问记录

// 01 BFS 算法
int bfs()
{
    deque<pair<int, int>> dq; // 双端队列
    dq.clear();
    dq.push_back({1, 1}); // 从 (1, 1) 开始
    int mod, cost;

    while (!dq.empty())
    {
        auto cur = dq.front();
        dq.pop_front();
        mod = cur.first;
        cost = cur.second;

        if (!visit[mod])
        {
            visit[mod] = true;
            if (mod == 0)
            {
                return cost;
            }
            dq.push_front({(mod * 10) % k, cost});   // 乘以 10
            dq.push_back({(mod + 1) % k, cost + 1}); // 加 1
        }
    }
    return -1; // 如果没有找到返回 -1
}

int main()
{
    cin >> k;                            // 输入 k
    memset(visit, false, sizeof(visit)); // 初始化访问记录
    cout << bfs() << endl;               // 调用 BFS 函数并输出结果
    return 0;
}
