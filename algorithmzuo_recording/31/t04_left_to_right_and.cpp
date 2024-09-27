// 给你两个整数 left 和 right ，表示区间 [left, right]
// 返回此区间内所有数字 & 的结果
// 包含 left 、right 端点
// 测试链接 : https://leetcode.cn/problems/bitwise-and-of-numbers-range/

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        // [5 7]
        // 1001
        // 1010
        // 1011
        //& 1000
        // 7 -= 1 -> 6
        // 6 -= 2 -> 4
        while(left < right){
            right -= (right & (-right));
        }
        return right;
    }
};