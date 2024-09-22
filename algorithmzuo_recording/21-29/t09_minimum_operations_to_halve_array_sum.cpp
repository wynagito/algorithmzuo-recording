// 将数组和减半的最少操作次数
// 测试链接 : https://leetcode.cn/problems/minimum-operations-to-halve-array-sum/
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int halveArray(vector<int>& nums) {
        // 每次只减少最大的数，直到数组和减半
        priority_queue<double> qu; // 大根堆 贪心思想
        double s = 0;
        for(int a : nums){
            s += a;
            qu.push(a * 1.0);
        }
        s /= 2;
        double r = 0;
        int cnt = 0;
        while( r < s){
            double b = qu.top();
            qu.pop();
            b /= 2;
            r += b;
            qu.push(b);
            cnt ++;
        }
        return cnt;
    }
};