// 并查集的小扩展
// 可以定制信息：并查集目前有多少个集合，以及给每个集合打上标签信息

// 移除最多的同行或同列石头
// n 块石头放置在二维平面中的一些整数坐标点上。每个坐标点上最多只能有一块石头
// 如果一块石头的 同行或者同列 上有其他石头存在，那么就可以移除这块石头
// 给你一个长度为 n 的数组 stones ，其中 stones[i] = [xi, yi] 表示第 i 块石头的位置
// 返回 可以移除的石子 的最大数量。
// 测试链接 : https://leetcode.cn/problems/most-stones-removed-with-same-row-or-column/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    int f[1010];
    int sets;
    void init()
    {
        for (int i = 0; i < 1010; ++i)
            f[i] = i;
    }

    int find(int x) { return f[x] == x ? x : find(f[x]); }

    void mege(int x, int y)
    {
        int fx = find(x), fy = find(y);
        if (fx != fy)
        {
            f[fx] = fy;
            sets--;
        }
    }
    int removeStones(vector<vector<int>> &stones)
    {
        init();
        int n = stones.size();
        sets = n;
        // key : 某行或某列
        // value : 第一次遇到的石头编号
        unordered_map<int, int> rr, ll;
        for (int i = 0; i < n; ++i)
        {
            int r = stones[i][0], l = stones[i][1];
            // 同行的石头在一个集合
            if (rr.find(r) != rr.end())
            {
                mege(i, rr[r]);
            }
            else
            {
                rr[r] = i;
            }
            // 同列的石头也在一个集合
            if (ll.find(l) != ll.end())
            {
                mege(i, ll[l]);
            }
            else
            {
                ll[l] = i;
            }
        }
        return n - sets;
    }
};