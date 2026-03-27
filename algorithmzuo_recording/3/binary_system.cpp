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

void printSection(const string &title)
{
    cout << "\n========================================" << endl;
    cout << "[" << title << "]" << endl;
    cout << "========================================" << endl;
}

void printValueAndBinary(const string &name, int num)
{
    cout << name << " (十进制): " << num << endl;
    cout << name << " (二进制): ";
    printBinary(num);
}

int main()
{
    printSection("1) 基本数值与二进制表示");
    // 非负数
    int a = 78;
    printValueAndBinary("a", a);

    // 负数
    int b = -6;
    printValueAndBinary("b", b);

    // 直接写二进制形式定义变量
    int c = 0b1001110;
    printValueAndBinary("c(0b1001110)", c);

    // 直接写十六进制形式定义变量
    int d = 0x4e;
    printValueAndBinary("d(0x4e)", d);

    printSection("2) 按位取反与相反数(补码)");
    cout << "以 a 为例:" << endl;
    printValueAndBinary("a", a);
    cout << "~a (按位取反) 二进制: ";
    printBinary(~a);
    int e = ~a + 1;
    printValueAndBinary("e = ~a + 1", e);

    printSection("3) INT_MIN 的特殊性");
    // int的最小值，取相反数、绝对值，都是自己
    int f = INT_MIN;
    printValueAndBinary("f = INT_MIN", f);
    printValueAndBinary("-f", -f);
    printValueAndBinary("~f + 1", ~f + 1);
    cout << "说明: 在 int 范围内，INT_MIN 的相反数仍是自己。" << endl;

    printSection("4) 按位或/与/异或");
    int g = 0b0001010;
    int h = 0b0001100;
    printValueAndBinary("g", g);
    printValueAndBinary("h", h);
    cout << "g | h : ";
    printBinary(g | h);
    cout << "g & h : ";
    printBinary(g & h);
    cout << "g ^ h : ";
    printBinary(g ^ h);

    printSection("5) | & 与 || && 的短路差异");
    cout << "test1: returnTrue() | returnFalse()" << endl;
    bool test1 = returnTrue() | returnFalse();
    cout << "test1 结果: " << test1 << endl;

    cout << "\ntest2: returnTrue() || returnFalse()" << endl;
    bool test2 = returnTrue() || returnFalse();
    cout << "test2 结果: " << test2 << endl;

    cout << "\ntest3: returnFalse() & returnTrue()" << endl;
    bool test3 = returnFalse() & returnTrue();
    cout << "test3 结果: " << test3 << endl;

    cout << "\ntest4: returnFalse() && returnTrue()" << endl;
    bool test4 = returnFalse() && returnTrue();
    cout << "test4 结果: " << test4 << endl;

    printSection("6) 左移 << 演示");
    int i = 0b0011010;
    printValueAndBinary("i", i);
    cout << "i << 1: ";
    printBinary(i << 1);
    cout << "i << 2: ";
    printBinary(i << 2);
    cout << "i << 3: ";
    printBinary(i << 3);

    printSection("7) 右移 >> 与无符号右移 >>>(C++通过unsigned模拟)");
    // 非负数 >> 和 >>> 效果一样
    cout << "非负数 i:" << endl;
    cout << "i >> 2            : ";
    printBinary(i >> 2);
    cout << "(unsigned)i >> 2  : ";
    printBinary((unsigned)i >> 2);

    // 负数 >> 和 >>> 效果不一样
    int j = 0b11110000000000000000000000000000;
    cout << "\n负数 j:" << endl;
    printValueAndBinary("j", j);
    cout << "j >> 2            : ";
    printBinary(j >> 2);
    cout << "(unsigned)j >> 2  : ";
    printBinary((unsigned)j >> 2);

    printSection("8) 移位与乘除2幂(非负数示例)");
    int k = 10;
    cout << "k      = " << k << endl;
    cout << "k << 1 = " << (k << 1) << endl;
    cout << "k << 2 = " << (k << 2) << endl;
    cout << "k << 3 = " << (k << 3) << endl;
    cout << "k >> 1 = " << (k >> 1) << endl;
    cout << "k >> 2 = " << (k >> 2) << endl;
    cout << "k >> 3 = " << (k >> 3) << endl;

    cout << "\n演示结束。" << endl;

    return 0;
}
