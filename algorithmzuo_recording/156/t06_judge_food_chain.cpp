// 甄别食物链
// 一共有n只动物，编号1 ~ n，每只动物都是A、B、C中的一种，A吃B、B吃C、C吃A
// 一共有k句话，希望你判断哪些话是假话，每句话是如下两类句子中的一类
// 1 X Y : 第X只动物和第Y只动物是同类
// 2 X Y : 第X只动物吃第Y只动物
// 当前的话与前面的某些真话冲突，视为假话
// 当前的话提到的X和Y，有任何一个大于n，视为假话
// 当前的话如果关于吃，又有X==Y，视为假话
// 返回k句话中，假话的数量
// 1 <= n <= 5 * 10^4    1 <= k <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P2024

#include <iostream>

using namespace std;

const int MAXN = 50001;

int n, k, ans;

// dist[i] = 0，代表i和头是同类
// dist[i] = 1，代表i吃头
// dist[i] = 2，代表i被头吃
int father[MAXN], dist[MAXN];

void prepare()
{
    ans = 0;
    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
        dist[i] = 0;
    }
}

int find(int i)
{
    if (i != father[i])
    {
        int tmp = father[i];
        father[i] = find(tmp);
        dist[i] = (dist[i] + dist[tmp]) % 3;
    }
    return father[i];
}

// op == 1, 1 l r，l和r是同类
// op == 2, 2 l r，l吃r
void unionSets(int op, int l, int r)
{
    int lf = find(l), rf = find(r), v = op == 1 ? 0 : 1;
    if (lf != rf)
    {
        father[lf] = rf;
        dist[lf] = (dist[r] - dist[l] + v + 3) % 3;
    }
}

bool check(int op, int l, int r)
{
    if (l > n || r > n || (op == 2 && l == r))
    {
        return false;
    }
    if (find(l) == find(r))
    {
        if (op == 1)
        {
            if (dist[l] != dist[r])
            {
                return false;
            }
        }
        else
        {
            if ((dist[l] - dist[r] + 3) % 3 != 1)
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    cin >> n >> k;
    prepare();
    for (int i = 0; i < k; i++)
    {
        int op, l, r;
        cin >> op >> l >> r;
        if (check(op, l, r))
        {
            unionSets(op, l, r);
        }
        else
        {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
