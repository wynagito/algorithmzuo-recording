// 送箱子到码头的最少行程数
// 一共有m个码头，编号1 ~ m， 给定长度为n的二维数组boxes
// boxes[i][0]表示i号箱子要送往的码头，boxes[i][1]表示i号箱子重量
// 有一辆马车，一次最多能装a个箱子并且箱子总重量不能超过b
// 马车一开始在仓库，可以在0位置，马车每开动一次，认为行程+1
// 箱子必须按照boxes规定的顺序被放上马车，也必须按照顺序被送往各自的码头
// 马车上相邻的箱子如果去往同一个码头，那么认为共享同一趟行程
// 马车可能经过多次送货，每次装货需要回到仓库，认为行程+1，送完所有的货，最终要回到仓库，行程+1
// 返回至少需要几个行程能把所有的货都送完
// 所有数据的范围 <= 10^5
// 测试链接 : https://leetcode.cn/problems/delivering-boxes-from-storage-to-ports/

#include <vector>
using namespace std;

class Solution
{
public:
    int boxDelivering(vector<vector<int>> &boxes, int m, int a, int b)
    {
        int n = boxes.size();
        // dp[i] : 马车拉完前i个货物并回仓库，需要的最少行程
        vector<int> dp(n + 1, 0);
        dp[1] = 2;

        // 马车最后一趟的货物范围[l...r]
        // 最后一趟货物的总重量weight，最后一趟需要的行程trip
        int weight = boxes[0][1];
        int trip = 2;

        for (int l = 0, r = 1; r < n; r++)
        {
            weight += boxes[r][1];
            if (boxes[r][0] != boxes[r - 1][0])
            {
                trip++;
            }
            // 1) 最后一趟货物的个数超了，最后一趟不得不减少货物
            // 2) 最后一趟货物的总重量超了，最后一趟不得不减少货物
            // 3) 最后一趟最左侧的货，分给之前的过程，如果发现之前过程的dp值没变化，那就分出去
            // 最后一趟最左侧的货，分给之前的过程，如果发现之前过程的dp值增加了，一定不要分出去
            while (r - l + 1 > a || weight > b || dp[l] == dp[l + 1])
            {
                weight -= boxes[l][1];
                if (boxes[l][0] != boxes[l + 1][0])
                {
                    trip--;
                }
                l++;
            }
            dp[r + 1] = dp[l] + trip;
        }
        return dp[n];
    }
};