#include <vector>
#include <string>

using namespace std;

// 位图原理
// 其实就是用bit组成的数组来存放值，用bit状态1、0代表存在、不存在，取值和存值操作都用位运算
// 限制是必须为连续范围且不能过大。好处是极大的节省空间，因为1个数字只占用1个bit的空间。
// 位图的实现
// Bitset是一种能以紧凑形式存储位的数据结构
// Bitset(int n) : 初始化n个位，所有位都是0
// void fix(int i) : 将下标i的位上的值更新为1
// void unfix(int i) : 将下标i的位上的值更新为0
// void flip() : 翻转所有位的值
// boolean all() : 是否所有位都是1
// boolean one() : 是否至少有一位是1
// int count() : 返回所有位中1的数量
// String toString() : 返回所有位的状态
// 测试链接 : https://leetcode-cn.com/problems/design-bitset/

class Bitset
{
public:
	vector<int> set;
	int size, zeros, ones;
	bool reverse;
	Bitset(int n)
	{
		// a/b如果结果想向上取整，可以写成 : (a+b-1)/b
		// 前提是a和b都是非负数
		set = vector<int>((n + 31) / 32, 0);
		size = n;
		zeros = n;
		ones = 0;
		reverse = false;
	}

	void fix(int i)
	{
		int index = i / 32;
		int bit = i % 32;
		if (!reverse)
		{
			// 位图所有位的状态，维持原始含义
			// 0 : 不存在
			// 1 : 存在
			if ((set[index] & (1 << bit)) == 0)
			{
				zeros--;
				ones++;
				set[index] |= (1 << bit);
			}
		}
		else
		{
			// 位图所有位的状态，翻转了
			// 0 : 存在
			// 1 : 不存在
			if ((set[index] & (1 << bit)) != 0)
			{
				zeros--;
				ones++;
				set[index] ^= (1 << bit);
			}
		}
	}

	void unfix(int i)
	{
		int index = i / 32;
		int bit = i % 32;
		if (!reverse)
		{
			if ((set[index] & (1 << bit)) != 0)
			{
				ones--;
				zeros++;
				set[index] ^= (1 << bit);
			}
		}
		else
		{
			if ((set[index] & (1 << bit)) == 0)
			{
				ones--;
				zeros++;
				set[index] |= (1 << bit);
			}
		}
	}

	void flip()
	{
		reverse = !reverse;
		swap(ones, zeros);
	}

	bool all() { return ones == size; }

	bool one() { return ones > 0; }

	int count() { return ones; }

	string toString()
	{
		string builder = "";
		for (int i = 0, k = 0, number, status; i < size; k++)
		{
			number = set[k];
			for (int j = 0; j < 32 && i < size; j++, i++)
			{
				status = ((number >> j) & 1);
				status ^= (reverse ? 1 : 0);
				builder += (status + '0');
			}
		}
		return builder;
	}
};