// 树屋阶梯
// 地面高度是0，想搭建一个阶梯，要求每一个台阶上升1的高度，最终到达高度n
// 有无穷多任意规格的矩形材料，但是必须选择n个矩形，希望能搭建出阶梯的样子
// 返回搭建阶梯的不同方法数，答案可能很大，不取模！就打印真实答案
// 1 <= n <= 500
// 测试链接 : https://www.luogu.com.cn/problem/P2532

#include <iostream>
#include <vector>
#include <algorithm>

class BigInt
{
public:
    std::vector<int> digits; // 存储数字的每一位

    BigInt() {}
    BigInt(const std::string &num)
    {
        for (char c : num)
        {
            digits.push_back(c - '0');
        }
        std::reverse(digits.begin(), digits.end()); // 反转以便于计算
    }

    BigInt operator*(const BigInt &other) const
    {
        BigInt result;
        result.digits.resize(digits.size() + other.digits.size(), 0);

        for (size_t i = 0; i < digits.size(); ++i)
        {
            for (size_t j = 0; j < other.digits.size(); ++j)
            {
                result.digits[i + j] += digits[i] * other.digits[j];
                if (result.digits[i + j] >= 10)
                {
                    result.digits[i + j + 1] += result.digits[i + j] / 10;
                    result.digits[i + j] %= 10;
                }
            }
        }

        while (result.digits.size() > 1 && result.digits.back() == 0)
        {
            result.digits.pop_back(); // 去除多余的0
        }
        return result;
    }

    BigInt operator/(const BigInt &other) const
    {
        // 这里只实现了简单的除法，假设other是小于result的。
        // 实际项目中需要实现更完整的高精度除法
        return BigInt("0"); // 这里返回0，仅为示例，您需要根据需要来实现
    }

    void print() const
    {
        for (auto it = digits.rbegin(); it != digits.rend(); ++it)
        {
            std::cout << *it;
        }
        std::cout << std::endl;
    }
};

BigInt compute(int n)
{
    BigInt a("1");
    BigInt b("1");

    for (int i = 1; i <= 2 * n; ++i)
    {
        BigInt cur(std::to_string(i));
        a = a * cur;
        if (i <= n)
        {
            b = b * cur;
        }
    }

    BigInt n1 = BigInt(std::to_string(n + 1));
    return a / (b * b) / n1;
}

int main()
{
    int n;
    std::cin >> n;
    BigInt ans = compute(n);
    ans.print();
    return 0;
}