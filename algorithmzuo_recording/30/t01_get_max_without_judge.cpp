// 异或运算性质
// 1）异或运算就是无进位相加
// 2）异或运算满足交换律、结合律，也就是同一批数字，不管异或顺序是什么，最终的结果都是一个
// 3）0^n=n，n^n=0
// 4）整体异或和如果是x，整体中某个部分的异或和如果是y，那么剩下部分的异或和是x^y
// 注意：数组a[i]和a[j]交换 i != j
// 否则：a[i] = a[i]^a[i] --> a[i] = 0
// 不用任何判断语句和比较操作，返回两个数的最大值
// 测试链接 : https://www.nowcoder.com/practice/d2707eaf98124f1e8f1d9c18ad487f76

class Solution
{
public:
    // 必须保证n一定是0或者1
    // 0变1，1变0
    int flip(int n)
    {
        return n ^ 1;
    }

    // 非负数返回1
    // 负数返回0
    int sign(int n)
    {
        return flip(n >> 31 & 1);
    }

    // 有溢出风险的实现
    int getMax1(int a, int b)
    {
        // A和B异号，会发生溢出
        int c = a - b;
        // c非负，returnA -> 1
        // c非负，returnB -> 0
        // c负数，returnA -> 0
        // c负数，returnB -> 1
        int returnA = sign(c);
        int returnB = flip(returnA);
        return a * returnA + b * returnB;
    }

    // 没有任何问题的实现
    int getMax2(int a, int b)
    {
        // c可能是溢出的
        int c = a - b;
        // a的符号
        int sa = sign(a);
        // b的符号
        int sb = sign(b);
        // c的符号
        int sc = sign(c);
        // 判断A和B，符号是不是不一样，如果不一样diffAB=1，如果一样diffAB=0
        int diffAB = sa ^ sb;
        // 判断A和B，符号是不是一样，如果一样sameAB=1，如果不一样sameAB=0
        int sameAB = flip(diffAB);
        // A和B的符号不一样且A的符号是正数，返回A，否则返回B
        // A和B的符号一样且C的符号是正数，返回A，否则返回B
        int returnA = diffAB * sa + sameAB * sc;
        int returnB = flip(returnA);
        return a * returnA + b * returnB;
    }
};