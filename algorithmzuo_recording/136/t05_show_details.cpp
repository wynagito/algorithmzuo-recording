// 线性基原理，只对非负数进行讨论

// 线性基常指的是异或空间线性基

// 一堆数字能得到的非0异或和的结果，能被元素个数尽量少的集合，不多不少的全部得到

// 那么就说，这个元素个数尽量少的集合，是这一堆数字的异或空间线性基

// 注意，只关心去重的非0异或和能否全部得到，并不关心每种异或和的个数

// 如下几个结论是构建异或空间线性基的基础
// 1，一堆数字中，任意的a和b，用a^b的结果替代a、b中的一个数字，不会影响非0异或和的组成
// 2，一堆数字中，任意的a和b，如果有a^b=0，那么舍弃掉a、b其中一个数字，不会影响非0异或和的组成
// 3，一堆数字能否异或出0，在求出异或空间线性基之后，需要被单独标记

// 一堆数字的异或空间线性基，可能不只一组，求解方式为 普通消元 或者 高斯消元

// 普通消元：得到某一组线性基，进而知道：线性基大小、异或和个数、异或和是否有0、最大异或和等信息

// 高斯消元：得到标准形式的异或空间线性基，既能知道普通消元得到的信息，还能知道第k小的异或和

// 一般题目只需要普通消元得到的一组线性基，足够解题，除非需要知道第k小的异或和，才会用到高斯消元

// 两种方法的时间复杂度都为O(n * m)，n是数字个数，m是最大数字的位数

// 异或空间线性基大小为O(m)，m是最大数字的位数

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 101;
// 最高位从哪开始
const int BIT = 60;

long arr[MAXN];
int n;

// 普通消元
long basis1[BIT + 1];
bool zero1;

bool insert(long num);
void compute1();
void printXor(long nums[], int n);
void dfs(long nums[], int n, int i, bool pick, long path, unordered_set<long> &set);

void compute1()
{
    zero1 = false;
    for (int i = 1; i <= n; i++)
    {
        if (!insert(arr[i]))
        {
            zero1 = true;
        }
    }
}

// 线性基里插入num，如果线性基增加了返回true，否则返回false
bool insert(long num)
{
    for (int i = BIT; i >= 0; i--)
    {
        if ((num >> i) & 1)
        {
            if (basis1[i] == 0)
            {
                basis1[i] = num;
                return true;
            }
            num ^= basis1[i];
        }
    }
    return false;
}

// 高斯消元
// 因为不需要维护主元和自由元的依赖关系
// 所以高斯消元的写法可以得到简化
long basis2[MAXN];
int len;
bool zero2;

void compute2()
{
    len = 1;
    for (long i = BIT; i >= 0; i--)
    {
        for (int j = len; j <= n; j++)
        {
            if ((basis2[j] & (1LL << i)) != 0)
            {
                swap(basis2[j], basis2[len]);
                break;
            }
        }
        if ((basis2[len] & (1LL << i)) != 0)
        {
            for (int j = 1; j <= n; j++)
            {
                if (j != len && (basis2[j] & (1LL << i)) != 0)
                {
                    basis2[j] ^= basis2[len];
                }
            }
            len++;
        }
    }
    len--;
    zero2 = len != n;
}

// nums中1~n的范围
// 所有可能的异或和打印出来
// 要求去重并且至少选择一个数字
void printXor(long nums[], int n)
{
    unordered_set<long> set;
    vector<long> current;
    dfs(nums, n, 1, false, 0, set);
    cout << "至少选择一个数字所有可能的异或和: ";
    for (const auto &s : set)
    {
        cout << s << ", ";
    }
    cout << endl;
}

// 当前来到i位置
// 之前是否选择过数字用pick表示
// 之前做的决定形成的异或和是path
// 当前i位置的数字要或者不要全决策
// 收集所有可能的异或和
void dfs(long nums[], int n, int i, bool pick, long path, unordered_set<long> &set)
{
    if (i > n)
    {
        if (pick)
        {
            set.insert(path);
        }
    }
    else
    {
        dfs(nums, n, i + 1, pick, path, set);
        dfs(nums, n, i + 1, true, path ^ nums[i], set);
    }
}

int main()
{
    // 例子1
    cout << "例子1" << endl;
    fill(basis1, basis1 + BIT + 1, 0);
    arr[1] = 12;
    arr[2] = 9;
    arr[3] = 14;
    arr[4] = 11;
    n = 4;

    cout << "原始数组得到的异或结果如下" << endl;
    printXor(arr, n);
    cout << "普通消元得到的线性基 : " << endl;
    compute1();
    long b1[MAXN];
    int s1 = 0;
    for (int i = BIT; i >= 0; i--)
    {
        if (basis1[i] != 0)
        {
            cout << basis1[i] << " ";
            b1[++s1] = basis1[i];
        }
    }
    cout << endl;
    cout << "是否能异或出0 : " << (zero1 ? "true" : "false") << endl;
    cout << "普通消元得到的异或结果如下" << endl;
    printXor(b1, s1);

    cout << endl;
    cout << endl;

    // 课上讲的普通消元，例子2
    // 2, 5, 11, 6
    cout << "例子2" << endl;
    fill(basis1, basis1 + BIT + 1, 0);
    arr[1] = 2;
    arr[2] = 5;
    arr[3] = 11;
    arr[4] = 6;
    n = 4;
    cout << "原始数组得到的异或结果如下" << endl;
    printXor(arr, n);
    cout << "===========================" << endl;
    cout << "普通消元得到的线性基 : " << endl;
    compute1();
    long b2[MAXN];
    int s2 = 0;
    for (int i = BIT; i >= 0; i--)
    {
        if (basis1[i] != 0)
        {
            cout << basis1[i] << " ";
            b2[++s2] = basis1[i];
        }
    }
    cout << endl;
    cout << "是否能异或出0 : " << (zero1 ? "true" : "false") << endl;
    cout << "普通消元得到的异或结果如下" << endl;
    printXor(b2, s2);
    cout << "===========================" << endl;

    cout << endl;
    cout << endl;

    // 课上讲的高斯消元的例子，例子3
    // 6, 37, 35, 33
    cout << "例子3" << endl;
    memset(basis2, 0, sizeof(basis2));
    arr[1] = basis2[1] = 6;
    arr[2] = basis2[2] = 37;
    arr[3] = basis2[3] = 35;
    arr[4] = basis2[4] = 33;
    n = 4;
    cout << "原始数组得到的异或结果如下" << endl;
    printXor(arr, n);
    cout << "===========================" << endl;
    cout << "高斯消元得到的线性基 : " << endl;
    compute2();
    for (int i = 1; i <= len; i++)
    {
        cout << basis2[i] << " ";
    }
    cout << endl;
    cout << "是否能异或出0 : " << (zero2 ? "true" : "false") << endl;
    cout << "高斯消元得到的异或结果如下" << endl;
    printXor(basis2, len);
    cout << "===========================" << endl;

    cout << endl;
    cout << endl;

    // 课上讲的高斯消元的例子，例子4
    // 如果想得到第k小的非0异或和
    // 将线性基排序 将k写成二进制数 按1的位序异或
    // 必须用高斯消元，不能用普通消元，比如
    // arr = { 7, 10, 4 }
    // 普通消元得到的异或空间线性基是 : 10 7 3
    // 第三小异或和是4，第四小异或和是10，这是错误的
    // 高斯消元可以得到正确结果
    // 高斯消元得到的异或空间线性基是 : 9 4 3
    // 第三小异或和是7，第四小异或和是9，这是正确的
    // eg. k = 3 = 0011
    // 3 ^ 4 = 0011 ^ 0100 = 0111 = 7 对的
    // 3 ^ 7 = 0011 ^ 0111 = 0100 = 4 错的
    cout << "例子4" << endl;
    memset(basis1, 0, sizeof(basis1));
    memset(basis2, 0, sizeof(basis2));
    arr[1] = basis2[1] = 7;
    arr[2] = basis2[2] = 10;
    arr[3] = basis2[3] = 4;
    n = 3;
    cout << "原始数组得到的异或结果如下" << endl;
    printXor(arr, n);
    cout << "===========================" << endl;
    cout << "普通消元" << endl;
    compute1();
    for (int i = BIT; i >= 0; i--)
    {
        if (basis1[i] != 0)
        {
            cout << basis1[i] << " ";
        }
    }
    cout << endl;
    cout << "是否能异或出0 : " << (zero1 ? "true" : "false") << endl;

    cout << "===========================" << endl;

    cout << "高斯消元" << endl;
    compute2();
    for (int i = 1; i <= len; i++)
    {
        cout << basis2[i] << " ";
    }
    cout << endl;
    cout << "是否能异或出0 : " << (zero2 ? "true" : "false") << endl;

    return 0;
}