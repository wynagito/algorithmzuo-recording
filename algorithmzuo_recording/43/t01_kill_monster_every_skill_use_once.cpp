// 一个基本事实
// C/C++运行时间1s，java/python/go等其他语言运行时间1s~2s，
// 对应的常数指令操作量是 10^7 ~ 10^8，不管什么测试平台，不管什么cpu，都是这个数量级
// 所以可以根据这个基本事实，来猜测自己设计的算法最终有没有可能在规定时间内通过

// 问题规模和可用算法
//                  logn      n      n*logn      n*根号n      n^2      2^n      n!
// n <= 11          Yes      Yes      Yes         Yes        Yes      Yes      Yes
// n <= 25          Yes      Yes      Yes         Yes        Yes      Yes      No
// n <= 5000        Yes      Yes      Yes         Yes        Yes      No       No
// n <= 10^5        Yes      Yes      Yes         Yes        No       No       No
// n <= 10^6        Yes      Yes      Yes         No         No       No       No
// n <= 10^7        Yes      Yes      No          No         No       No       No
// n >= 10^8        Yes      No       No          No         No       No       No

// 现在有一个打怪类型的游戏，这个游戏是这样的，你有n个技能
// 每一个技能会有一个伤害，
// 同时若怪物小于等于一定的血量，则该技能可能造成双倍伤害
// 每一个技能最多只能释放一次，已知怪物有m点血量
// 现在想问你最少用几个技能能消灭掉他(血量小于等于0)
// 技能的数量是n，怪物的血量是m
// i号技能的伤害是x[i]，i号技能触发双倍伤害的血量最小值是y[i]
// 1 <= n <= 10
// 1 <= m、x[i]、y[i] <= 10^6
// 测试链接 : https://www.nowcoder.com/practice/d88ef50f8dab4850be8cd4b95514bbbd

#include <iostream>
#include <climits>

using namespace std;

const int MAXN = 11;

int kill[MAXN];
int blood[MAXN];

// kill[i]、blood[i]
// n : 一共几个技能
// i : 当前来到了第几号技能
// r : 怪兽目前的剩余血量
int f(int n, int i, int r)
{
    if (r <= 0)
    {
        // 之前的决策已经让怪兽挂了！返回使用了多少个技能
        return i;
    }
    // r > 0
    if (i == n)
    {
        // 无效，之前的决策无效
        return INT_MAX;
    }
    // 返回至少需要几个技能可以将怪兽杀死
    int ans = INT_MAX;
    for (int j = i; j < n; j++)
    {
        swap(kill[i], kill[j]);
        swap(blood[i], blood[j]);
        ans = min(ans, f(n, i + 1, r - (r > blood[i] ? kill[i] : kill[i] * 2)));
        swap(kill[i], kill[j]);
        swap(blood[i], blood[j]);
    }
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        for (int j = 0; j < n; j++)
        {
            cin >> kill[j];
            cin >> blood[j];
        }
        int ans = f(n, 0, m);
        cout << (ans == INT_MAX ? -1 : ans) << endl;
    }
    return 0;
}