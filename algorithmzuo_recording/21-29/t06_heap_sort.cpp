// 堆结构和堆排序，acm练习风格
// 堆结构
// 完全二叉树和数组前缀范围来对应，大小，单独的变量size来控制
// i的父亲节点：(i-1)/2，i的左孩子：i*2 + 1，i的右孩子：i*2 + 2
// 堆的定义（大根堆、小根堆）
// 堆的调整：heapInsert（向上调整）、heapify（向下调整）
// heapInsert、heapify方法的单次调用，时间复杂度O(log n)，完全二叉树的结构决定的

// 堆排序
//    A. 从顶到底建堆，时间复杂度O(n * log n)，log1 + log2 + log3 + … + logn -> O(n*logn)
//       或者用增倍分析法：建堆的复杂度分析+子矩阵数量的复杂度分析
//    B. 从底到顶建堆，时间复杂度O(n)，总代价就是简单的等比数列关系，n/2 + n/4 * 2 + n/8 * 3 + … + 1 * n -> O(n)
//    C. 建好堆之后的调整阶段，从最大值到最小值依次归位，时间复杂度O(n * log n)
// 时间复杂度O(n * log n)，不管以什么方式建堆，调整阶段的时间复杂度都是这个，所以整体复杂度也是这个
// 额外空间复杂度是O(1)，因为堆直接建立在了要排序的数组上，所以没有什么额外空间
// 测试链接 : https://www.luogu.com.cn/problem/P1177

#include <iostream>

using namespace std;

const int MAXN = 100001;
int arr[MAXN];
int n;

// i位置的数，向上调整大根堆
void heapInsert(int i)
{
    while (i > 0 && arr[i] > arr[(i - 1) / 2])
    {
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// i位置的数，向下调整大根堆
// 当前堆的大小为size
void heapify(int i, int size)
{
    int l = i * 2 + 1;
    while (l < size)
    {
        int best = l + 1 < size && arr[l + 1] > arr[l] ? l + 1 : l;
        best = arr[best] > arr[i] ? best : i;
        if (best == i)
        {
            break;
        }
        swap(arr[best], arr[i]);
        i = best;
        l = i * 2 + 1;
    }
}

// 从顶到底建立大根堆，O(n * logn)
// 依次弹出堆内最大值并排好序，O(n * logn)
// 整体时间复杂度O(n * logn)
void heapSort1()
{
    for (int i = 0; i < n; i++)
    {
        heapInsert(i);
    }
    int size = n;
    while (size > 1)
    {
        swap(arr[0], arr[--size]);
        heapify(0, size);
    }
}

// 从底到顶建立大根堆，O(n)
// 依次弹出堆内最大值并排好序，O(n * logn)
// 整体时间复杂度O(n * logn)
void heapSort2()
{
    for (int i = n - 1; i >= 0; i--)
    {
        heapify(i, n);
    }
    int size = n;
    while (size > 1)
    {
        swap(arr[0], arr[--size]);
        heapify(0, size);
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    heapSort1();
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
