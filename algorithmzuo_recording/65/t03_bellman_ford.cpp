// Bellman-Ford算法，解决可以有负权边但是不能有负环（保证最短路存在）的图，单源最短路算法

// 松弛操作
// 假设源点为A，从A到任意点F的最短距离为distance[F]
// 假设从点P出发某条边，去往点S，边权为W
// 如果发现，distance[P] + W < distance[S]，也就是通过该边可以让distance[S]变小
// 那么就说，P出发的这条边对点S进行了松弛操作

// Bellman-Ford过程
// 1，每一轮考察每条边，每条边都尝试进行松弛操作，那么若干点的distance会变小
// 2，当某一轮发现不再有松弛操作出现时，算法停止

// Bellman-Ford算法时间复杂度
// 假设点的数量为N，边的数量为M，每一轮时间复杂度O(M)
// 最短路存在的情况下，因为1次松弛操作会使1个点的最短路的边数+1
// 而从源点出发到任何点的最短路最多走过全部的n个点，所以松弛的轮数必然 <= n - 1
// 所以Bellman-Ford算法时间复杂度O(M*N)

// 重要推广：判断从某个点出发能不能到达负环
// 上面已经说了，如果从A出发存在最短路（没有负环），那么松弛的轮数必然 <= n - 1
// 而如果从A点出发到达一个负环，那么松弛操作显然会无休止地进行下去
// 所以，如果发现从A点出发，在第n轮时松弛操作依然存在，说明从A点出发能够到达一个负环

// Bellman-Ford算法应用（不是模版）
// k站中转内最便宜的航班
// 有 n 个城市通过一些航班连接。给你一个数组 flights
// 其中 flights[i] = [fromi, toi, pricei]
// 表示该航班都从城市 fromi 开始，以价格 pricei 抵达 toi。
// 现在给定所有的城市和航班，以及出发城市 src 和目的地 dst，你的任务是找到出一条最多经过 k 站中转的路线
// 使得从 src 到 dst 的 价格最便宜 ，并返回该价格。 如果不存在这样的路线，则输出 -1。
// 测试链接 : https://leetcode.cn/problems/cheapest-flights-within-k-stops/

class Solution
{
public:
    int cur[110], next[110];
    // 每一轮松弛操作从cur里拿数据
    // 保证每一轮松弛操作只会发生一次中转操作
    // 否则可能会发生一轮松弛有多个中转点，导致结果错误
    int findCheapestPrice(int n, vector<vector<int>> &flights, int start, int target, int k)
    {
        for (int i = 0; i < n; ++i)
            cur[i] = INT_MAX;
        cur[start] = 0;
        // 松弛操作轮数
        for (int i = 0; i <= k; i++)
        {
            memcpy(next, cur, sizeof(cur));
            for (auto edge : flights)
            {
                // a -> b , w
                if (cur[edge[0]] != INT_MAX)
                {
                    next[edge[1]] = min(next[edge[1]], cur[edge[0]] + edge[2]);
                }
            }
            memcpy(cur, next, sizeof(next));
        }
        return cur[target] == INT_MAX ? -1 : cur[target];
    }
};