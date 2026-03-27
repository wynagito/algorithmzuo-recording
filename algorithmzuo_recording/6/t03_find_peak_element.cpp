// 峰值元素是指其值严格大于左右相邻值的元素
// 给你一个整数数组 nums，已知任何两个相邻的值都不相等
// 找到峰值元素并返回其索引
// 数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。
// 你可以假设 nums[-1] = nums[n] = 无穷小
// 你必须实现时间复杂度为 O(log n) 的算法来解决此问题。
// 测试链接 : https://leetcode.cn/problems/find-peak-element/

#include <vector>
#include <iostream>
#include <string>
#include <climits>

using namespace std;

const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string CYAN = "\033[36m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string YELLOW = "\033[33m";

int findPeakElement(vector<int> &arr)
{
    int n = arr.size();
    if (n == 0)
        return -1;
    if (n == 1)
        return 0; // 单元素直接返回索引0
    int left = 0, right = n - 1;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] > arr[mid + 1])
        {
            // 峰值在左侧（包括mid）
            right = mid;
        }
        else
        {
            // 峰值在右侧
            left = mid + 1;
        }
    }
    return left;
}

bool isPeak(const vector<int> &arr, int idx)
{
    if (idx < 0 || idx >= (int)arr.size())
    {
        return false;
    }
    int left = (idx - 1 >= 0) ? arr[idx - 1] : INT_MIN;
    int right = (idx + 1 < (int)arr.size()) ? arr[idx + 1] : INT_MIN;
    return arr[idx] > left && arr[idx] > right;
}

void printArray(const vector<int> &arr)
{
    cout << "[";
    for (int i = 0; i < (int)arr.size(); i++)
    {
        cout << arr[i] << (i + 1 == (int)arr.size() ? "" : ", ");
    }
    cout << "]";
}

bool runCase(const string &name, vector<int> arr)
{
    int idx = findPeakElement(arr);
    bool ok = isPeak(arr, idx);
    int leftValue = (idx - 1 >= 0 && idx - 1 < (int)arr.size()) ? arr[idx - 1] : INT_MIN;
    int rightValue = (idx + 1 >= 0 && idx + 1 < (int)arr.size()) ? arr[idx + 1] : INT_MIN;

    cout << "\n"
         << CYAN << BOLD << "---------------- " << name << " ----------------" << RESET << "\n";
    cout << "数组: ";
    printArray(arr);
    cout << "\n返回索引: " << idx;
    if (idx >= 0 && idx < (int)arr.size())
    {
        cout << "，对应值: " << arr[idx];
    }
    cout << "\n左邻值: " << (leftValue == INT_MIN ? -2147483648 : leftValue)
         << "，右邻值: " << (rightValue == INT_MIN ? -2147483648 : rightValue) << "\n";
    cout << "判定条件: arr[idx] > left && arr[idx] > right\n";
    cout << "结果: " << (ok ? (GREEN + string("PASS") + RESET) : (RED + string("FAIL") + RESET)) << "\n";

    return ok;
}

int main()
{
    int total = 0;
    int pass = 0;

    cout << BOLD << YELLOW << "===== findPeakElement 测试开始 =====" << RESET << "\n";

    total++;
    pass += runCase("用例1: 单元素", {5}) ? 1 : 0;
    total++;
    pass += runCase("用例2: 峰值在左边界", {9, 7, 3, 1}) ? 1 : 0;
    total++;
    pass += runCase("用例3: 峰值在右边界", {1, 3, 7, 9}) ? 1 : 0;
    total++;
    pass += runCase("用例4: 峰值在中间", {1, 3, 2, 1}) ? 1 : 0;
    total++;
    pass += runCase("用例5: 多个峰值", {1, 4, 2, 6, 3, 5, 1}) ? 1 : 0;
    total++;
    pass += runCase("用例6: 常见样例", {1, 2, 1, 3, 5, 6, 4}) ? 1 : 0;

    int fail = total - pass;

    cout << "\n"
         << BOLD << YELLOW << "===== 测试汇总 =====" << RESET << "\n";
    cout << "总用例数: " << total << "\n";
    cout << GREEN << "通过数: " << pass << RESET << "\n";
    cout << (fail == 0 ? GREEN : RED) << "失败数: " << fail << RESET << "\n";
    cout << "通过率: " << (pass * 100 / total) << "%\n";

    cout << "\n"
         << BOLD << YELLOW << "===== 测试结束 =====" << RESET << "\n";

    return fail == 0 ? 0 : 1;
}
