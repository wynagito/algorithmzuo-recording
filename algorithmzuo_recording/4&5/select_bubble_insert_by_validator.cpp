#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// 随机数组最大长度
const int N = 200;
// 随机数组每个值，在1~V之间等概率随机
const int V = 1000;
// 测试次数
const int testTimes = 50000;

// 函数声明
vector<int> randomArray(int n, int v);
vector<int> copyArray(const vector<int> &arr);
bool sameArray(const vector<int> &arr1, const vector<int> &arr2);
void selectionSort(vector<int> &arr);
void bubbleSort(vector<int> &arr);
void insertionSort(vector<int> &arr);

int main()
{
    cout << "测试开始" << endl;

    srand((unsigned)time(0)); // 设置随机种子

    for (int i = 0; i < testTimes; i++)
    {
        // 随机得到一个长度，长度在[0~N-1]
        int n = rand() % N;
        // 得到随机数组
        vector<int> arr = randomArray(n, V);
        vector<int> arr1 = copyArray(arr);
        vector<int> arr2 = copyArray(arr);
        vector<int> arr3 = copyArray(arr);

        selectionSort(arr1);
        bubbleSort(arr2);
        insertionSort(arr3);

        if (!sameArray(arr1, arr2) || !sameArray(arr1, arr3))
        {
            cout << "出错了!" << endl;
            // 可以在这里增加错误处理代码，例如打印错误的数组
            break; // 发现错误后退出测试
        }
    }

    cout << "测试结束" << endl;

    return 0;
}

// 随机数组，长度为n，每个数都在1~v之间
vector<int> randomArray(int n, int v)
{
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % v + 1; // [1, v]之间的数
    }
    return arr;
}

// 复制数组
vector<int> copyArray(const vector<int> &arr)
{
    return vector<int>(arr); // 直接使用拷贝构造函数
}

// 判断两个数组是否相等
bool sameArray(const vector<int> &arr1, const vector<int> &arr2)
{
    if (arr1.size() != arr2.size())
        return false;
    for (size_t i = 0; i < arr1.size(); i++)
    {
        if (arr1[i] != arr2[i])
        {
            return false;
        }
    }
    return true;
}

// 选择排序
void selectionSort(vector<int> &arr)
{
    // 选择排序的实现
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// 冒泡排序
void bubbleSort(vector<int> &arr)
{
    // 冒泡排序的实现
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 插入排序
void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--)
        {
            swap(arr[j], arr[j + 1]);
        }
    }
}