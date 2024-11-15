// 拓扑排序
// 每个节点的前置节点都在这个节点之前
// 要求：有向图、没有环
// 拓扑排序的顺序可能不只一种。拓扑排序也可以用来判断有没有环。
// 1）在图中找到所有入度为0的点
// 2）把所有入度为0的点在图中删掉，重点是删掉影响！继续找到入度为0的点并删掉影响
// 3）直到所有点都被删掉，依次删除的顺序就是正确的拓扑排序结果
// 4）如果无法把所有的点都删掉，说明有向图里有环

// 拓扑排序模版（Leetcode）
// 邻接表建图（动态方式）
// 课程表II
// 现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1
// 给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi]
// 表示在选修课程 ai 前 必须 先选修 bi
// 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1]
// 返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序
// 你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组
// 测试链接 : https://leetcode.cn/problems/course-schedule-ii/

class Solution
{
public:
    int queue[2010];
    int l, r;
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> graph(numCourses, vector<int>());
        vector<int> indegree(numCourses, 0);
        vector<int> ans;
        l = 0, r = 0;
        // 建图
        for (auto &p : prerequisites)
        {
            graph[p[1]].push_back(p[0]);
            indegree[p[0]]++;
        }
        // 入度为0的点入队
        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] == 0)
            {
                queue[r++] = i;
            }
        }
        // 拓扑排序
        while (l < r)
        {
            int node = queue[l++];
            ans.push_back(node);
            for (int i : graph[node])
            {
                indegree[i]--;
                if (indegree[i] == 0)
                {
                    queue[r++] = i;
                }
            }
        }
        // 判断是否有环
        if (ans.size() == numCourses)
        {
            return ans;
        }
        else
        {
            return vector<int>();
        }
    }
};