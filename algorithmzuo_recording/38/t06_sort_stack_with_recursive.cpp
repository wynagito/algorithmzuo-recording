#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

// 用递归函数排序栈
// 栈只提供push、pop、empty三个方法
// 请完成无序栈的排序，要求排完序之后，从栈顶到栈底从小到大
// 只能使用栈提供的push、pop、empty三个方法、以及递归函数
// 除此之外不能使用任何的容器，数组也不行
// 就是排序过程中只能用：
// 1) 栈提供的push、pop、empty三个方法
// 2) 递归函数，并且返回值最多为单个整数

// 从栈当前的顶部开始，往下数deep层，已知最大值是maxval，出现了k次
// 请把这k个最大值沉底，剩下的数据状况不变
void down(stack<int> &s, int deep, int maxval, int k)
{
    if (deep == 0)
    {
        for (int i = 0; i < k; i++)
        {
            s.push(maxval);
        }
    }
    else
    {
        int num = s.top();
        s.pop();
        down(s, deep - 1, maxval, k);
        if (num != maxval)
        {
            s.push(num);
        }
    }
}

// 从栈当前的顶部开始，往下数deep层，已知最大值是maxval了
// 返回，maxval出现了几次，不改变栈的数据状况
int times(stack<int> &s, int deep, int maxval)
{
    if (deep == 0)
    {
        return 0;
    }
    int num = s.top();
    s.pop();
    int restTimes = times(s, deep - 1, maxval);
    int count = restTimes + (num == maxval ? 1 : 0);
    s.push(num);
    return count;
}

// 从栈当前的顶部开始，往下数deep层
// 返回这deep层里的最大值
int maxf(stack<int> &s, int deep)
{
    if (deep == 0)
    {
        return INT_MIN;
    }
    int num = s.top();
    s.pop();
    int restMax = maxf(s, deep - 1);
    int maxVal = max(num, restMax);
    s.push(num);
    return maxVal;
}

// 返回栈的深度
// 不改变栈的数据状况
int deep(stack<int> &s)
{
    if (s.empty())
    {
        return 0;
    }
    int num = s.top();
    s.pop();
    int d = deep(s) + 1;
    s.push(num);
    return d;
}

// 排序栈的函数
void sort(stack<int> &s)
{
    int d = deep(s);
    while (d > 0)
    {
        int maxVal = maxf(s, d);
        int k = times(s, d, maxVal);
        down(s, d, maxVal, k);
        d -= k;
    }
}

// 生成随机栈
stack<int> randomStack(int n, int v)
{
    stack<int> ans;
    for (int i = 0; i < n; i++)
    {
        ans.push(rand() % v);
    }
    return ans;
}

// 检测栈是否有序
bool isSorted(stack<int> s)
{
    int step = INT_MIN;
    while (!s.empty())
    {
        if (step > s.top())
        {
            return false;
        }
        step = s.top();
        s.pop();
    }
    return true;
}

// 测试程序
int main()
{
    stack<int> test;
    test.push(1);
    test.push(5);
    test.push(4);
    test.push(5);
    test.push(3);
    test.push(2);
    test.push(3);
    test.push(1);
    test.push(4);
    test.push(2);

    sort(test);
    while (!test.empty())
    {
        cout << test.top() << endl;
        test.pop();
    }

    // 随机测试
    int N = 20;
    int V = 20;
    int testTimes = 20000;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTimes; i++)
    {
        int n = rand() % N;
        stack<int> stack = randomStack(n, V);
        sort(stack);
        if (!isSorted(stack))
        {
            cout << "出错了!" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;

    return 0;
}