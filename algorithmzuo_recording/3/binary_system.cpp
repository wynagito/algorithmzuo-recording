// 本文件的实现是用int来举例的
// 对于long类型完全同理
// 不过要注意，如果是long类型的数字num，有64位
// num & (1 << 48)，这种写法不对
// 因为1是一个int类型，只有32位，所以(1 << 48)早就溢出了，所以无意义
// 应该写成 : num & (1L << 48)

#include <iostream>
#include <climits>

using namespace std;

// 打印一个int类型的数字，32位进制的状态
// 左侧是高位，右侧是低位
void printBinary(int num)
{
    for (int i = 31; i >= 0; i--)
    {
        // 用位操作判断当前位是0还是1
        cout << ((num & (1 << i)) == 0 ? '0' : '1');
    }
    cout << endl;
}

bool returnTrue()
{
    cout << "进入了returnTrue函数" << endl;
    return true;
}

bool returnFalse()
{
    cout << "进入了returnFalse函数" << endl;
    return false;
}

int main()
{
    // 非负数
    int a = 78;
    cout << a << endl;
    printBinary(a);
    cout << "===a===" << endl;

    // 负数
    int b = -6;
    cout << b << endl;
    printBinary(b);
    cout << "===b===" << endl;

    // 直接写二进制形式定义变量
    int c = 0b1001110;
    cout << c << endl;
    printBinary(c);
    cout << "===c===" << endl;

    // 直接写十六进制形式定义变量
    int d = 0x4e;
    cout << d << endl;
    printBinary(d);
    cout << "===d===" << endl;

    // ~、相反数
    cout << a << endl;
    printBinary(a);
    printBinary(~a);
    int e = ~a + 1;
    cout << e << endl;
    printBinary(e);
    cout << "===e===" << endl;

    // int的最小值，取相反数、绝对值，都是自己
    int f = INT_MIN;
    cout << f << endl;
    printBinary(f);
    cout << -f << endl;
    printBinary(-f);
    cout << (~f + 1) << endl;
    printBinary(~f + 1);
    cout << "===f===" << endl;

    // | & ^
    int g = 0b0001010;
    int h = 0b0001100;
    printBinary(g | h);
    printBinary(g & h);
    printBinary(g ^ h);
    cout << "===g、h===" << endl;

    // 测试|、&、||、&&
    cout << "test1测试开始" << endl;
    bool test1 = returnTrue() | returnFalse();
    cout << "test1结果: " << test1 << endl;

    cout << "test2测试开始" << endl;
    bool test2 = returnTrue() || returnFalse();
    cout << "test2结果: " << test2 << endl;

    cout << "test3测试开始" << endl;
    bool test3 = returnFalse() & returnTrue();
    cout << "test3结果: " << test3 << endl;

    cout << "test4测试开始" << endl;
    bool test4 = returnFalse() && returnTrue();
    cout << "test4结果: " << test4 << endl;

    cout << "===|、&、||、&&===" << endl;

    // << 位移操作
    int i = 0b0011010;
    printBinary(i);
    printBinary(i << 1);
    printBinary(i << 2);
    printBinary(i << 3);
    cout << "===i << ===" << endl;

    // 非负数 >> 和 >>> 效果一样
    printBinary(i);
    printBinary(i >> 2);
    printBinary((unsigned)i >> 2); // >>> 使用无符号右移
    cout << "===i >> >>>===" << endl;

    // 负数 >> 和 >>> 效果不一样
    int j = 0b11110000000000000000000000000000;
    printBinary(j);
    printBinary(j >> 2);
    printBinary((unsigned)j >> 2); // >>> 使用无符号右移
    cout << "===j >> >>>===" << endl;

    // 非负数 << 操作
    int k = 10;
    cout << k << endl;
    cout << (k << 1) << endl;
    cout << (k << 2) << endl;
    cout << (k << 3) << endl;
    cout << (k >> 1) << endl;
    cout << (k >> 2) << endl;
    cout << (k >> 3) << endl;
    cout << "===k===" << endl;

    return 0;
}
