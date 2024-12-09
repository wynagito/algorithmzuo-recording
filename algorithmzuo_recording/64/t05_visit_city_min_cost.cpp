// 电动车游城市
// 小明的电动车电量充满时可行驶距离为 cnt，每行驶 1 单位距离消耗 1 单位电量，且花费 1 单位时间
// 小明想选择电动车作为代步工具。地图上共有 N 个景点，景点编号为 0 ~ N-1
// 他将地图信息以 [城市 A 编号,城市 B 编号,两城市间距离] 格式整理在在二维数组 paths，
// 表示城市 A、B 间存在双向通路。
// 初始状态，电动车电量为 0。每个城市都设有充电桩，
// charge[i] 表示第 i 个城市每充 1 单位电量需要花费的单位时间。
// 请返回小明最少需要花费多少单位时间从起点城市 start 抵达终点城市 end
// 测试链接 : https://leetcode.cn/problems/DFPeFJ/

struct cmp
{
    bool operator()(const vector<int> &a, const vector<int> &b)
    {
        return a[2] > b[2];
    }
};

class Solution
{
public:
    int distance[210][110];
    bool visited[210][110];
    int electricCarPlan(vector<vector<int>> &paths, int cnt, int start, int end, vector<int> &charge)
    {
        int n = charge.size();
        vector<vector<pair<int, int>>> graph(n);
        for (auto path : paths)
        {
            graph[path[0]].push_back({path[1], path[2]});
            graph[path[1]].push_back({path[0], path[2]});
        }
        // n : 0 ~ n-1，不代表图上的点
        // (点，到达这个点的电量)图上的点！
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= cnt; j++)
            {
                distance[i][j] = INT_MAX;
                visited[i][j] = false;
            }
        }
        distance[start][0] = 0;
        // 0 : 当前点
        // 1 : 来到当前点的电量
        // 2 : 花费时间
        priority_queue<vector<int>, vector<vector<int>>, cmp> heap;
        heap.push({start, 0, 0});
        while (!heap.empty())
        {
            auto record = heap.top();
            heap.pop();
            int cur = record[0];
            int power = record[1];
            int cost = record[2];
            if (visited[cur][power])
            {
                continue;
            }
            if (cur == end)
            {
                // 常见剪枝
                // 发现终点直接返回
                // 不用等都结束
                return cost;
            }
            visited[cur][power] = true;
            if (power < cnt)
            {
                // 充一格电
                // cur, power+1
                if (!visited[cur][power + 1] && cost + charge[cur] < distance[cur][power + 1])
                {
                    distance[cur][power + 1] = cost + charge[cur];
                    heap.push({cur, power + 1, cost + charge[cur]});
                }
            }
            for (auto edge : graph[cur])
            {
                // 不充电去别的城市
                int nextCity = edge.first;
                int restPower = power - edge.second;
                int nextCost = cost + edge.second;
                if (restPower >= 0 && !visited[nextCity][restPower] && nextCost < distance[nextCity][restPower])
                {
                    distance[nextCity][restPower] = nextCost;
                    heap.push({nextCity, restPower, nextCost});
                }
            }
        }
        return -1;
    }
};