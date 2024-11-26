// 完美洗牌算法
// 给定数组arr，给定某个范围arr[l..r]，该范围长度为n，n是偶数
// 因为n是偶数，所以给定的范围可以分成左右两个部分，arr[l1, l2, ...lk, r1, r2, ...rk]
// 请把arr[l..r]范围上的数字调整成arr[r1, l1, r2, l2, ... rk, lk]，其他位置的数字不变
// 要求时间复杂度O(n)，额外空间复杂度O(1)，对数器验证

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class PerfectShuffle
{
public:
    static const int MAXN = 20;
    static int start[MAXN];
    static int split[MAXN];
    static int size;

    // 生成随机数组
    static vector<int> randomArray(int n, int v)
    {
        vector<int> ans(n);
        for (int i = 0; i < n; i++)
        {
            ans[i] = rand() % v;
        }
        return ans;
    }

    // 拷贝数组
    static vector<int> copyArray(const vector<int> &arr)
    {
        return arr; // 直接返回拷贝
    }

    // 申请额外空间的做法
    static void shuffle1(vector<int> &arr, int l, int r)
    {
        int n = r - l + 1;
        vector<int> help(n);
        for (int l1 = l, r1 = (l + r) / 2 + 1, j = 0; j < n; l1++, r1++)
        {
            help[j++] = arr[r1];
            help[j++] = arr[l1];
        }
        for (int i = l, j = 0; j < n; i++, j++)
        {
            arr[i] = help[j];
        }
    }

    // 建构方法
    static void build(int n)
    {
        size = 0;
        for (int s = 1, p = 2; p <= n; s *= 3, p = s * 3 - 1)
        {
            start[++size] = s;
            split[size] = p;
        }
    }

    // 完美洗牌算法
    static void shuffle2(vector<int> &arr, int l, int r)
    {
        int n = r - l + 1;
        build(n);
        for (int i = size, m; n > 0;)
        {
            if (split[i] <= n)
            {
                m = (l + r) / 2;
                rotate(arr, l + split[i] / 2, m, m + split[i] / 2);
                circle(arr, l, l + split[i] - 1, i);
                l += split[i];
                n -= split[i];
            }
            else
            {
                i--;
            }
        }
    }

    static void rotate(vector<int> &arr, int l, int m, int r)
    {
        reverse(arr, l, m);
        reverse(arr, m + 1, r);
        reverse(arr, l, r);
    }

    static void reverse(vector<int> &arr, int l, int r)
    {
        while (l < r)
        {
            swap(arr[l++], arr[r--]);
        }
    }

    static void swap(int &a, int &b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }

    static void circle(vector<int> &arr, int l, int r, int i)
    {
        for (int j = 1, init, cur, next, curv, nextv; j <= i; j++)
        {
            init = cur = l + start[j] - 1;
            next = to(cur, l, r);
            curv = arr[cur];
            while (next != init)
            {
                nextv = arr[next];
                arr[next] = curv;
                curv = nextv;
                cur = next;
                next = to(cur, l, r);
            }
            arr[init] = curv;
        }
    }

    static int to(int i, int l, int r)
    {
        if (i <= (l + r) / 2)
        {
            return i + (i - l + 1);
        }
        else
        {
            return i - (r - i + 1);
        }
    }

    static void test()
    {
        int n = 10000;
        int v = 100000;
        vector<int> arr1 = randomArray(n, v);
        vector<int> arr2 = copyArray(arr1);
        int test = 50000;

        cout << "测试开始" << endl;
        for (int i = 1, a, b, l, r; i <= test; i++)
        {
            a = rand() % n;
            b = rand() % n;
            l = min(a, b);
            r = max(a, b);
            if (((r - l + 1) & 1) == 0)
            {
                shuffle1(arr1, l, r);
                shuffle2(arr2, l, r);
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (arr1[i] != arr2[i])
            {
                cout << "出错了!" << endl;
                break;
            }
        }
        cout << "测试结束" << endl;
    }
};

// 静态变量初始化
int PerfectShuffle::start[MAXN];
int PerfectShuffle::split[MAXN];
int PerfectShuffle::size;

int main()
{
    srand(static_cast<unsigned int>(time(0))); // 初始化随机数种子
    PerfectShuffle::test();
    return 0;
}