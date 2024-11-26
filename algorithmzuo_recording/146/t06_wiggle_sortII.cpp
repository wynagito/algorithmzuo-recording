// 摇摆排序ii(满足全部进阶要求)
// 给定一个数组arr，重新排列数组，确保满足：arr[0] < arr[1] > arr[2] < arr[3] > ...
// 题目保证输入的数组一定有解，要求时间复杂度O(n)，额外空间复杂度O(1)
// 测试链接 : https://leetcode.cn/problems/wiggle-sort-ii/

class Solution
{
public:
    void wiggleSort(vector<int> &arr)
    {
        int n = arr.size();
        randomizedSelect(arr, n, n / 2);
        if ((n & 1) == 0)
        {
            shuffle(arr, 0, n - 1);
            reverse(arr, 0, n - 1);
        }
        else
        {
            shuffle(arr, 1, n - 1);
        }
    }

    // 无序数组中找到，如果排序之后，在i位置的数x，顺便把数组调整为
    // 左边是小于x的部分    中间是等于x的部分    右边是大于x的部分
    // 时间复杂度O(n)，额外空间复杂度O(1)
    int randomizedSelect(vector<int> &arr, int n, int i)
    {
        int ans = 0;
        for (int l = 0, r = n - 1; l <= r;)
        {
            partition(arr, l, r, arr[l + (int)(rand() % (r - l + 1))]);
            if (i < first)
            {
                r = first - 1;
            }
            else if (i > last)
            {
                l = last + 1;
            }
            else
            {
                ans = arr[i];
                break;
            }
        }
        return ans;
    }

    int first, last;

    void partition(vector<int> &arr, int l, int r, int x)
    {
        first = l;
        last = r;
        int i = l;
        while (i <= last)
        {
            if (arr[i] == x)
            {
                i++;
            }
            else if (arr[i] < x)
            {
                swap(arr[i++], arr[first++]);
            }
            else
            {
                swap(arr[i], arr[last--]);
            }
        }
    }

    // 完美洗牌算法
    // 时间复杂度O(n)，额外空间复杂度O(1)
    static const int MAXN = 20;

    int start[MAXN], split[MAXN];

    int size;

    void shuffle(vector<int> &arr, int l, int r)
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

    void build(int n)
    {
        size = 0;
        for (int s = 1, p = 2; p <= n; s *= 3, p = s * 3 - 1)
        {
            start[++size] = s;
            split[size] = p;
        }
    }

    void rotate(vector<int> &arr, int l, int m, int r)
    {
        reverse(arr, l, m);
        reverse(arr, m + 1, r);
        reverse(arr, l, r);
    }

    void reverse(vector<int> &arr, int l, int r)
    {
        while (l < r)
        {
            swap(arr[l++], arr[r--]);
        }
    }

    void circle(vector<int> &arr, int l, int r, int i)
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

    int to(int i, int l, int r)
    {
        if (i <= (l + r) >> 1)
        {
            return i + (i - l + 1);
        }
        else
        {
            return i - (r - i + 1);
        }
    }
};