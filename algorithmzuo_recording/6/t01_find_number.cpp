#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// 随机数组生成函数
vector<int> randomArray(int n, int v) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % v + 1;
    }
    return arr;
}

// 验证方法，线性查找
bool right(const vector<int>& sortedArr, int num) {
    for (int cur : sortedArr) {
        if (cur == num) {
            return true;
        }
    }
    return false;
}

// 验证方法，二分查找
bool exist(const vector<int>& arr, int num) {
    if (arr.empty()) {
        return false;
    }
    int l = 0, r = arr.size() - 1, m = 0;
    while (l <= r) {
        m = (l + r) / 2;
        if (arr[m] == num) {
            return true;
        } else if (arr[m] > num) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return false;
}

int main() {
    srand((unsigned)(time(0))); // 设置随机数种子
    int N = 100;
    int V = 1000;
    int testTime = 500000;
    cout << "测试开始" << endl;

    for (int i = 0; i < testTime; i++) {
        int n = rand() % N;
        vector<int> arr = randomArray(n, V);
        sort(arr.begin(), arr.end());
        int num = rand() % V;
        if (right(arr, num) != exist(arr, num)) {
            cout << "出错了!" << endl;
        }
    }

    cout << "测试结束" << endl;
    return 0;
}