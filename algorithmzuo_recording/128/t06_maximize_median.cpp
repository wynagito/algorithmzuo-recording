// 相邻必选的子序列最大中位数
// 给定一个长度为n的数组arr
// 合法子序列定义为，任意相邻的两个数至少要有一个被挑选所组成的子序列
// 求所有合法子序列中，最大中位数是多少
// 中位数的定义为上中位数
// [1, 2, 3, 4]的上中位数是2
// [1, 2, 3, 4, 5]的上中位数是3
// 2 <=  n <= 10^5
// 1 <= arr[i] <= 10^9
// 来自真实大厂笔试，对数器验证

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

bool check(vector<int> &arr, vector<int> &help, vector<vector<int>> &dp, int x, int n);
int dpFunc(vector<int> &arr, vector<vector<int>> &dp, int n);
int right(vector<int> &arr);
int dfs(vector<int> &arr, int i, bool pre, vector<int> &path, int size);

// 正式方法
// 时间复杂度O(n * log n)
int maximizeMedian(vector<int> &arr)
{
	int n = arr.size();
	vector<int> sortarr(arr);
	sort(sortarr.begin(), sortarr.end());
	int l = 0, r = n - 1, m = 0, ans = -1;
	vector<int> help(n);
	vector<vector<int>> dp(n + 1, vector<int>(2, 0));

	while (l <= r)
	{
		m = (l + r) / 2;
		if (check(arr, help, dp, sortarr[m], n))
		{
			ans = sortarr[m];
			l = m + 1;
		}
		else
		{
			r = m - 1;
		}
	}
	return ans;
}

// 任意相邻的两数至少选一个来生成子序列
// 到底有没有一个合法子序列，能让其中>=x的数达到一半以上
bool check(vector<int> &arr, vector<int> &help, vector<vector<int>> &dp, int x, int n)
{
	for (int i = 0; i < n; i++)
	{
		help[i] = arr[i] >= x ? 1 : -1;
	}
	return dpFunc(help, dp, n) > 0;
}

// 任意相邻的两数至少选一个来生成子序列
// 返回合法子序列的最大累加和
int dpFunc(vector<int> &arr, vector<vector<int>> &dp, int n)
{
	for (int i = n - 1; i >= 0; i--)
	{
		// dp[i][0] : i位置的数字，选和不选皆可，i...范围上形成合法子序列的最大累加和
		// dp[i][1] : i位置的数字，一定要选，i...范围上形成合法子序列的最大累加和
		dp[i][0] = max(arr[i] + dp[i + 1][0], dp[i + 1][1]);
		dp[i][1] = arr[i] + dp[i + 1][0];
	}
	return dp[0][0];
}

// 暴力方法
// 为了验证
int right(vector<int> &arr) {
    vector<int> path(arr.size());
    return dfs(arr, 0, true, path, 0);
}

// 暴力方法
// 递归实现
int dfs(vector<int> &arr, int i, bool pre, vector<int> &path, int size) {
    if (i == arr.size()) {
        // 如果没有选择任何元素，返回 0
        if (size == 0) {
            return 0;
        }
        // 创建选择的子序列
        vector<int> sortarr(path.begin(), path.begin() + size);
        // 对选择的子序列进行排序
        sort(sortarr.begin(), sortarr.end());
        // 返回中位数
        return sortarr[(sortarr.size() - 1) / 2];
    } else {
        // 选择当前元素
        path[size] = arr[i];
        int ans = dfs(arr, i + 1, true, path, size + 1);
        
        // 如果前一个元素被选中，可以选择不选当前元素
        if (pre) {
            ans = max(ans, dfs(arr, i + 1, false, path, size));
        }
        return ans;
    }
}


// 为了测试
vector<int> randomArray(int n, int v)
{
	vector<int> ans(n);
	for (int i = 0; i < n; i++)
	{
		ans[i] = rand() % v;
	}
	return ans;
}

// 为了测试
int main()
{
	int n = 20;
	int v = 1000;
	int testTime = 10000;
	cout << "功能测试开始" << endl;
	for (int i = 0; i < testTime; i++)
	{
		int size = rand() % n + 1;
		vector<int> arr = randomArray(size, v);
		int ans1 = right(arr);
		int ans2 = maximizeMedian(arr);
		if (ans1 != ans2)
		{
			cout << "出错了!" << endl;
		}
	}
	cout << "功能测试结束" << endl;
	cout << endl;

	cout << "性能测试开始" << endl;
	n = 1000;
	v = 50000;
	cout << "数组长度 : " << n << endl;
	cout << "数值范围 : " << v << endl;
	vector<int> arr = randomArray(n, v);
	clock_t start = clock();
	maximizeMedian(arr);
	clock_t end = clock();
	cout << "正式方法的运行时间 : " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " 毫秒" << endl;
	cout << "性能测试结束" << endl;
	return 0;
}
