// 数组中有2种数出现了奇数次，其他的数都出现了偶数次
// 返回这2种出现了奇数次的数
// 测试链接 : https://leetcode.cn/problems/single-number-iii/

#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> singleNumber(vector<int> &nums)
    {
        int eor1 = 0;
        for (int num : nums)
        {
            // nums中有2种数a、b出现了奇数次，其他的数都出现了偶数次
            eor1 ^= num;
        }
        // eor1 : a ^ b
        // Brian Kernighan算法
        // 提取出二进制里最右侧的1
        int rightOne = eor1 & (-eor1);
        int eor2 = 0;
        // eg. 1 2 1 3
        // a : 0001
        //     0010
        //     0001
        //     0011
        // a = 0001
        // r = 0001;
        // 一个数末尾有1 ， 而另一个数末尾无1
        for (int num : nums)
        {
            // 数末尾有1 全XOR ， 偶数次会消掉，所以得到其中一个数
            if ((num & rightOne) == 0)
            {
                eor2 ^= num;
            }
        }
        return {eor2, eor1 ^ eor2};
    }
};