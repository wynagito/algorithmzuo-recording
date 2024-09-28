// 加法：利用每一步无进位相加的结果 + 进位的结果不停计算，直到进位消失
// 减法：利用加法，和一个数字x相反数就是(~x)+1
// 乘法：回想小学时候怎么学的乘法，除此之外没别的了
// 除法：为了防止溢出，让被除数右移，而不是除数左移。从高位尝试到低位。
// 不用任何算术运算，只用位运算实现加减乘除
// 代码实现中你找不到任何一个算术运算符
// 测试链接 : https://leetcode.cn/problems/divide-two-integers/

#include <climits>

class Solution
{
public:
	int divide(int a, int b)
	{
		if (a == INT_MIN && b == INT_MIN)
		{
			// a和b都是整数最小
			return 1;
		}
		if (a != INT_MIN && b != INT_MIN)
		{
			// a和b都不是整数最小，那么正常去除
			return div(a, b);
		}
		if (b == INT_MIN)
		{
			// a不是整数最小，b是整数最小
			return 0;
		}
		// a是整数最小，b是-1，返回整数最大，因为题目里明确这么说了
		if (b == neg(1))
		{
			return INT_MAX;
		}
		// a是整数最小，b不是整数最小，b也不是-1
		// a=INT_MIN,无法转非负
		// b > 0
		// div(a + b, b) = div(a , b) + 1
		// div(a, b) = div(a + b, b) - 1
		// b < 0
		// div(a - b, b) = div(a , b) - 1
		// div(a, b) = div(a - b, b) + 1
		a = add(a, b > 0 ? b : neg(b));
		int ans = div(a, b);
		int offset = b > 0 ? neg(1) : 1;
		return add(ans, offset);
	}

	// 保证非负 整除
	// 280/25 = 11
	// 280 = 25*2^3 + 25*2^1 + 25*2^0
	// 1011 = 11
	int div(int a, int b)
	{
		int x = a < 0 ? neg(a) : a;
		int y = b < 0 ? neg(b) : b;
		int ans = 0;
		for (int i = 30; i >= 0; i = minus(i, 1))
		{
			if ((x >> i) >= y)
			{ // 若y左移可能会发生溢出
				ans |= (1 << i);
				x = minus(x, y << i);
			}
		}
		return a < 0 ^ b < 0 ? neg(ans) : ans;
	}

	// a = 0011
	// b = 0001
	// a + b = 0100
	// a^b = 0010
	// a&b = 0001
	// (a&b)<<1 = 0010
	// 继续计算
	int add(int a, int b)
	{
		int ans = a;
		while (b != 0)
		{ // 直至无进位信息即可
			// ans : a和b无进位相加的结果
			ans = a ^ b;
			// b : a和b相加时的进位信息
			b = (a & b) << 1;
			a = ans;
		}
		return ans;
	}

	int minus(int a, int b)
	{
		return add(a, neg(b));
	}

	// 补码
	int neg(int n)
	{
		return add(~n, 1);
	}

	// 乘法
	// 不断左移 , 遇到乘数是1就累加
	int multiply(int a, unsigned int b)
	{
		int ans = 0;
		while (b != 0)
		{
			if ((b & 1) != 0)
			{
				// 考察b当前最右的状态！
				ans = add(ans, a);
			}
			a <<= 1;
			b >>= 1; // 无符号右移
		}
		return ans;
	}
};