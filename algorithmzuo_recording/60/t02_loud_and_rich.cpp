// 喧闹和富有
// 从 0 到 n - 1 编号，其中每个人都有不同数目的钱，以及不同程度的安静值
// 给你一个数组richer，其中richer[i] = [ai, bi] 表示
// person ai 比 person bi 更有钱
// 还有一个整数数组 quiet ，其中 quiet[i] 是 person i 的安静值
// richer 中所给出的数据 逻辑自洽
// 也就是说，在 person x 比 person y 更有钱的同时，不会出现
// person y 比 person x 更有钱的情况
// 现在，返回一个整数数组 answer 作为答案，其中 answer[x] = y 的前提是,
// 在所有拥有的钱肯定不少于 person x 的人中，
// person y 是最安静的人（也就是安静值 quiet[y] 最小的人）。
// 测试链接 : https://leetcode.cn/problems/loud-and-rich/

class Solution
{
public:
    int in[510] = {0};
    vector<int> loudAndRich(vector<vector<int>> &richer, vector<int> &quiet)
    {
        int n = quiet.size();
        vector<int> ans(n);
        vector<vector<int>> gh(n);
        for (auto rr : richer)
        {
            gh[rr[0]].push_back(rr[1]);
            in[rr[1]]++;
        }
        queue<int> qu;
        for (int i = 0; i < n; ++i)
        {
            ans[i] = i;
            if (in[i] == 0)
            {
                qu.push(i);
            }
        }
        while (!qu.empty())
        {
            int f = qu.front();
            qu.pop();
            for (int nt : gh[f])
            {
                if (quiet[ans[f]] < quiet[ans[nt]])
                {
                    ans[nt] = ans[f];
                }
                if (!(--in[nt]))
                {
                    qu.push(nt);
                }
            }
        }
        return ans;
    }
};