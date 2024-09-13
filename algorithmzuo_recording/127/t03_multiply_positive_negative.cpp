// 相乘为正或负的子数组数量
// 给定一个长度为n的数组arr，其中所有值都不是0
// 返回有多少个子数组相乘的结果是正
// 返回有多少个子数组相乘的结果是负
// 1 <= n <= 10^6
// -10^9 <= arr[i] <= +10^9，arr[i]一定不是0
// 来自真实大厂笔试，对数器验证

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// 正式方法
vector<int> num(const vector<int> &arr)
{
	// 0 : 正状态
	// 1 : 负状态
	vector<int> cnt(2, 0);
	cnt[0] = 1;
	int ans1 = 0;
	int ans2 = 0;
	int cur = 0;

	for (int i = 0; i < arr.size(); i++)
	{
		cur ^= (arr[i] > 0) ? 0 : 1;
		ans1 += cnt[cur];
		ans2 += cnt[cur ^ 1];
		cnt[cur]++;
	}

	return {ans1, ans2};
}

// 暴力方法
// 为了验证
vector<int> right(const vector<int> &arr)
{
	int n = arr.size();
	int ans1 = 0;
	int ans2 = 0;

	for (int i = 0; i < n; i++)
	{
		long long cur = 1;
		for (int j = i; j < n; j++)
		{
			cur *= arr[j];
			if (cur > 0)
			{
				ans1++;
			}
			else
			{
				ans2++;
			}
		}
	}

	return {ans1, ans2};
}

// 为了验证
vector<int> randomArray(int n, int v)
{
	vector<int> ans(n);
	for (int i = 0; i < n; i++)
	{
		do
		{
			ans[i] = rand() % (2 * v + 1) - v;
		} while (ans[i] == 0);
	}
	return ans;
}

int main()
{
	// 正式方法无所谓，怎么都正确
	// 但是对数器方法是暴力乘起来，所以n和v不要太大，防止溢出
	int n = 20;
	int v = 10;
	int testTime = 10000;
	srand(time(0));

	cout << "测试开始" << endl;
	for (int i = 0; i < testTime; i++)
	{
		int size = rand() % n;
		vector<int> arr = randomArray(size, v);
		vector<int> ans1 = num(arr);
		vector<int> ans2 = right(arr);
		if (ans1[0] != ans2[0] || ans1[1] != ans2[1])
		{
			cout << "出错了!" << endl;
		}
	}
	cout << "测试结束" << endl;
	return 0;
}
