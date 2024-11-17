// 戳印序列
// 你想最终得到"abcbc"，认为初始序列为"?????"。印章是"abc"
// 那么可以先用印章盖出"??abc"的状态，
// 然后用印章最左字符和序列的0位置对齐，就盖出了"abcbc"
// 这个过程中，"??abc"中的a字符，被印章中的c字符覆盖了
// 每次盖章的时候，印章必须完全盖在序列内
// 给定一个字符串target是最终的目标，长度为n，认为初始序列为n个'?'
// 给定一个印章字符串stamp，目标是最终盖出target
// 但是印章的使用次数必须在10*n次以内
// 返回一个数组，该数组由每个回合中被印下的最左边字母的索引组成
// 上面的例子返回[2,0]，表示印章最左字符依次和序列2位置、序列0位置对齐盖下去，就得到了target
// 如果不能在10*n次内印出序列，就返回一个空数组
// 测试链接 : https://leetcode.cn/problems/stamping-the-sequence/

class Solution
{
public:
    bool visited[1001] = {false};
    int indegree[1001];
    vector<int> movesToStamp(string s, string t)
    {
        int m = s.size();
        int n = t.size();
        for (int i = 0; i < n; ++i)
            indegree[i] = m;
        vector<vector<int>> graph(n);
        queue<int> qu;
        // O(n*m)
        for (int i = 0; i <= n - m; i++)
        {
            // i开头....(m个)
            // i+0 i+1 i+m-1
            for (int j = 0; j < m; j++)
            {
                if (t[i + j] == s[j])
                {
                    if (!(--indegree[i]))
                    {
                        qu.push(i);
                    }
                }
                else
                {
                    // i + j
                    // from : 错误的位置
                    // to : i开头的下标
                    graph[i + j].push_back(i);
                }
            }
        }
        // 同一个位置取消错误不要重复统计
        vector<int> path;
        while (!qu.empty())
        {
            int cur = qu.front();
            qu.pop();
            path.push_back(cur);
            for (int i = 0; i < m; i++)
            {
                // cur : 开头位置
                // cur + 0 cur + 1 cur + 2 ... cur + m - 1
                if (!visited[cur + i])
                {
                    visited[cur + i] = true;
                    for (int next : graph[cur + i])
                    {
                        if (!(--indegree[next]))
                        {
                            qu.push(next);
                        }
                    }
                }
            }
        }
        if (path.size() != n - m + 1)
        {
            path.clear();
            return path;
        }
        // path逆序调整
        reverse(path.begin(), path.end());
        return path;
    }
};