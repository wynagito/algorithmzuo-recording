// 逆序二进制的状态
// 测试链接 : https://leetcode.cn/problems/reverse-bits/

#include <cstdint>
#include <iostream>
using namespace std;

class Solution
{
public:
    uint32_t reverseBits(uint32_t n)
    {
        // 32
        // 16 16
        // 8 8  8 8
        // 4 4  4 4  4 4  4 4
        // 2 2  2 2  2 2  2 2  2 2  2 2  2 2  2 2  2 2
        // 划分成小组进行交换，在依次向上返回，最后整体交换
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = (n >> 16) | (n << 16);
        return n;
    }
};

class Test
{
public:
    void printBits(uint32_t n)
    {
        cout << n << " : " << endl;
        for (int i = 31; i >= 0; i--)
        {
            if ((i + 1) % 4 == 0)
                cout << " ";
            cout << ((n >> i) & 1);
        }
        cout << endl;
    }
    void test()
    {
        uint32_t n = 43261596;
        printBits(n);
        cout << "n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);" << endl;
        printBits(2863311530);
        printBits(1431655765);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        printBits(n);
        cout << "n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);" << endl;
        printBits(3435973836);
        printBits(858993459);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        printBits(n);
        cout << "n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);" << endl;
        printBits(4042322160);
        printBits(252645135);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        printBits(n);
        cout << "n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);" << endl;
        printBits(4278255360);
        printBits(16711935);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        printBits(n);
        cout << "n = (n >> 16) | (n << 16);" << endl;
        n = (n >> 16) | (n << 16);
        printBits(n);
    }
};

int main()
{
    Test *t = new Test();
    t->test();
    delete t;
    return 0;
}