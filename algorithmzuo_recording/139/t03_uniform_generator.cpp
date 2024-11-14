// 均匀生成器
// 如果有两个数字step和mod，那么可以由以下方式生成很多数字
// seed(1) = 0，seed(i+1) = (seed(i) + step) % mod
// 比如，step = 3、mod = 5
// seed(1) = 0，seed(2) = 3，seed(3) = 1，seed(4) = 4，seed(5) = 2
// 如果能产生0 ~ mod-1所有数字，step和mod的组合叫  "Good Choice"
// 如果无法产生0 ~ mod-1所有数字，step和mod的组合叫 "Bad Choice"
// 根据step和mod，打印结果
// 1 <= step、mod <= 10^5
// 测试链接 : http://poj.org/problem?id=1597

#include <cstdio>

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    int step, mod;
    while (scanf("%d%d", &step, &mod) == 2)
    {
        printf("%10d%10d    ", step, mod);
        if (gcd(step, mod) == 1)
            printf("Good Choice\n");
        else
            printf("Bad Choice\n");
        printf(" \n");
    }
    return 0;
}