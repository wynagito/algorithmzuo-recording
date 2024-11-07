// 大鱼吃小鱼问题
// 给定一个数组arr，每个值代表鱼的体重
// 每一轮每条鱼都会吃掉右边离自己最近比自己体重小的鱼，每条鱼向右找只吃一条
// 但是吃鱼这件事是同时发生的，也就是同一轮在A吃掉B的同时，A也可能被别的鱼吃掉
// 如果有多条鱼在当前轮找到的是同一条小鱼，那么在这一轮，这条小鱼同时被这些大鱼吃
// 请问多少轮后，鱼的数量就固定了
// 比如 : 8 3 1 5 6 7 2 4
// 第一轮 : 8吃3；3吃1；5、6、7吃2；4没有被吃。数组剩下 8 5 6 7 4
// 第二轮 : 8吃5；5、6、7吃4。数组剩下 8 6 7
// 第三轮 : 8吃6。数组剩下 8 7
// 第四轮 : 8吃7。数组剩下 8。
// 过程结束，返回4
// 测试链接 : https://www.nowcoder.com/practice/77199defc4b74b24b8ebf6244e1793de
// 测试链接 : https://leetcode.cn/problems/steps-to-make-array-non-decreasing/
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100001;
int arr[MAXN];
int n;
int stack[MAXN][2];
int r;

// arr[0...n-1]鱼的体重
// stack[...]随便用
// stack[i][1] : 从stack[i][0] 开始，最多吃多少几轮
// stack[i][0] : 第i+1条鱼的体重
// r : 栈顶指针
// 小压大
int turns()
{
    r = 0;
    int ans = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        // i号鱼，arr[i]
        // 0轮是初始
        int curTurns = 0;
        while (r > 0 && stack[r - 1][0] < arr[i])
        {
            curTurns = max(curTurns + 1, stack[--r][1]);
        }
        stack[r][0] = arr[i];
        stack[r++][1] = curTurns;
        ans = max(ans, curTurns);
    }
    return ans;
}

int main()
{

    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        cout << turns() << endl;
    }

    return 0;
}

// 测试链接 : https://leetcode.cn/problems/steps-to-make-array-non-decreasing/
class Solution
{
public:
    static const int MAXM = 100001;

    int s[MAXM][2];
    int r = 0;
    int totalSteps(vector<int> &arr)
    {
        int ans = 0;
        int n = arr.size();
        for (int i = n - 1; i >= 0; i--)
        {
            int curTurns = 0;
            while (r > 0 && s[r - 1][0] < arr[i])
            {
                curTurns = max(curTurns + 1, s[--r][1]);
            }
            s[r][0] = arr[i];
            s[r++][1] = curTurns;
            ans = max(ans, curTurns);
        }
        return ans;
    }
};