// 一个正整数如果能被 a 或 b 整除，那么它是神奇的。
// 给定三个整数 n , a , b ，返回第 n 个神奇的数字。
// 因为答案可能很大，所以返回答案 对 10^9 + 7 取模 后的值。
// 测试链接 : https://leetcode.cn/problems/nth-magical-number/

class Solution
{
public:
	// 同余原理
	// 1) 加法、乘法每一步计算完后直接取模，减法则为(a-b+m)%m
	// 2) 要确保过程中不溢出，所以往往乘法运算的用long类型做中间变量
	// 3) 除法的同余需要求逆元

	int nthMagicalNumber(int n, int a, int b)
	{
		long long ans;
		int gc = gcd(a, b);					  // gcd
		long long lc = (long long)a * b / gc; // lcm
		// 二分答案法
		// 1...n * min(a , b) 内的个数
		for (long long l = 0, r = (long long)n * min(a, b), m = 0; l <= r;)
		{
			m = (l + r) / 2;
			// 1....m
			// 容斥原理
			// a=2, b=3, lc=6
			// 2 3 4 6 8 9 10 12
			// 12/2 + 12/3 - 12/6 = 8
			if (m / a + m / b - m / lc >= n)
			{
				ans = m;
				r = m - 1;
			}
			else
			{
				l = m + 1;
			}
		}
		return (int)(ans % 1000000007);
	}

	// 证明辗转相除法就是证明如下关系：
	// gcd(a, b) = gcd(b, a % b)
	// 假设a % b = r，即需要证明的关系为：gcd(a, b) = gcd(b, r)
	// 证明过程：
	// 因为a % b = r，所以如下两个等式必然成立
	// 1) a = b * q + r，q为0、1、2、3....中的一个整数
	// 2) r = a − b * q，q为0、1、2、3....中的一个整数
	// 假设u是a和b的公因子，则有: a = s * u, b = t * u
	// 把a和b带入2)得到，r = s * u - t * u * q = (s - t * q) * u
	// 这说明 : u如果是a和b的公因子，那么u也是r的因子
	// 假设v是b和r的公因子，则有: b = x * v, r = y * v
	// 把b和r带入1)得到，a = x * v * q + y * v = (x * q + y) * v
	// 这说明 : v如果是b和r的公因子，那么v也是a的公因子
	// 综上，a和b的每一个公因子 也是 b和r的一个公因子，反之亦然
	// 所以，a和b的全体公因子集合 = b和r的全体公因子集合
	// 即gcd(a, b) = gcd(b, r)
	// 证明结束
	int gcd(int a, int b)
	{
		return b ? gcd(b, a % b) : a;
	}
	long long lcm(long long a, long long b)
	{
		return (long long)a / gcd(a, b) * b;
	}
};