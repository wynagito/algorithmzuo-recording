// 已知n是非负数
// 返回大于等于n的最小的2某次方
// 如果int范围内不存在这样的数，返回整数最小值
#include <iostream>

using namespace std;

void printBits(int n)
{
    for (int i = 31; i >= 0; i--)
    {
        cout << ((n >> i) & 1);
    }   
    cout << endl;    
}

int near2power(int n)
{
    if (n <= 0)
    {
        return 1;
    }
    // 将最左侧1的右边全刷为1
    n--;
    printBits(n);
    n |= n >> 1;
    printBits(n);
    n |= n >> 2;
    printBits(n);
    n |= n >> 4;
    printBits(n);
    n |= n >> 8;
    printBits(n);
    n |= n >> 16;
    printBits(n);
    return n + 1;
}

int main()
{
    int n = (1 << 30) + 1;
    cout << "The bits of " << n << " are: ";
    printBits(n);
    int ans = near2power(n);
    cout << "The nearest 2 power of " << n << " is " << ans << endl;
    cout << "The bits of " << ans << " are: ";
    printBits(ans);
    return 0;
}