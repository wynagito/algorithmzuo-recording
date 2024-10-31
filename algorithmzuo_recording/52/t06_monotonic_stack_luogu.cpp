// 给定一个长度为n的数组，打印每个位置的右侧，大于该位置数字的最近位置
// 测试链接 : https://www.luogu.com.cn/problem/P5788

#include <iostream>

using namespace std;

const int MAXN = 3e6 + 5;

int stack[MAXN];
int a[MAXN];
int top = 0;

int main()
{
    int n, cur;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        while (top > 0 && a[i] > a[stack[top - 1]])
        {
            top--;
            cur = stack[top];
            a[cur] = i;
        }
        stack[top++] = i;
    }
    while (top > 0)
    {
        top--;
        cur = stack[top];
        a[cur] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}