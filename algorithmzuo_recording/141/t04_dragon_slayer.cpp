// 屠龙勇士
// 一共n只巨龙，每只巨龙都有初始血量hp[i]，每只巨龙都有恢复能力recovery[i]
// 每只巨龙都会在攻击结束后开始恢复，初始一共m把剑，每把剑攻击力init[i]
// 每只巨龙只有当血量恰好为0时，才能被杀死。面对某只具体的龙，只能用固定的剑来攻击，规定如下：
// 攻击力不高于当前巨龙的血量，并且攻击力最大的一把剑，如果没有这样的剑，就选择攻击力最低的一把剑
// 需要按1~n的顺序依次讨伐巨龙，i号巨龙被杀后，那把攻击的剑会消失，同时奖励攻击力reward[i]的剑
// 勇士制定的策略如下，不管面对什么巨龙，攻击过程只打击ans下，让当前巨龙的血量<=0
// 然后在当前巨龙恢复的过程中，如果血量恰好为0，那么当前巨龙被杀死，勇士继续讨伐下一只
// 你的任务是算出最小的ans，让勇士可以在该策略下杀死所有巨龙
// 如果在固定打击次数的策略下，就是无法杀死所有巨龙，返回-1
// 查看数据范围可以打开测试链接 : https://www.luogu.com.cn/problem/P4774

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

const int MAXN = 100001;

long long hp[MAXN];
long long recovery[MAXN];
long long reward[MAXN];
long long init[MAXN];
long long attack[MAXN];
map<long long, int> sorted;

long long d, x, y, px, py;

// 扩展欧几里得算法
void exgcd(long long a, long long b)
{
    if (b == 0)
    {
        d = a;
        x = 1;
        y = 0;
    }
    else
    {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

// 龟速乘法
long long multiply(long long a, long long b, long long mod)
{
    a = (a % mod + mod) % mod;
    b = (b % mod + mod) % mod;
    long long ans = 0;
    while (b != 0)
    {
        if ((b & 1) != 0)
        {
            ans = (ans + a) % mod;
        }
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}

// 分配攻击
long long allocate(int n, int m)
{
    sorted.clear();
    for (int i = 1; i <= m; i++)
    {
        sorted[init[i]]++;
    }
    long long max = 0;
    for (int i = 1; i <= n; i++)
    {
        auto it = sorted.lower_bound(hp[i]);
        long long sword;
        if (it == sorted.begin())
        {
            sword = it->first;
        }
        else
        {
            --it;
            sword = it->first;
        }
        attack[i] = sword;
        sorted[sword]--;
        if (sorted[sword] == 0)
        {
            sorted.erase(sword);
        }
        sorted[reward[i]]++;
        max = std::max(max, (hp[i] + attack[i] - 1) / attack[i]);
        hp[i] %= recovery[i];
    }
    return max;
}

// 计算答案
long long compute(int n, int m)
{
    long long max = allocate(n, m);
    long long tail = 0, lcm = 1, tmp, a, b, c, x0;

    for (int i = 1; i <= n; i++)
    {
        a = multiply(attack[i], lcm, recovery[i]);
        b = recovery[i];
        c = ((hp[i] - attack[i] * tail) % b + b) % b;
        exgcd(a, b);
        if (c % d != 0)
        {
            return -1;
        }
        x0 = multiply(x, c / d, b / d);
        tmp = lcm * (b / d);
        tail = (tail + multiply(x0, lcm, tmp)) % tmp;
        lcm = tmp;
    }

    long long ans;
    if (tail >= max)
    {
        ans = tail;
    }
    else
    {
        ans = (max - tail + lcm - 1) / lcm * lcm + tail;
    }
    return ans;
}

int main()
{

    int cases;
    cin >> cases;
    for (int t = 1; t <= cases; t++)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            cin >> hp[i];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> recovery[i];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> reward[i];
        }
        for (int i = 1; i <= m; i++)
        {
            cin >> init[i];
        }
        cout << compute(n, m) << '\n';
    }
    return 0;
}