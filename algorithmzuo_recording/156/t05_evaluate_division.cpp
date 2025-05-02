// 除法求值
// 所有变量都用字符串表示，并且给定若干组等式
// 比如等式
// ["ab", "ef"] = 8，代表ab / ef = 8
// ["ct", "ef"] = 2，代表ct / ef = 2
// 所有等式都是正确的并且可以进行推断，给定所有等式之后，会给你若干条查询
// 比如查询，["ab", "ct"]，根据上面的等式推断，ab / ct = 4
// 如果某条查询中的变量，从来没在等式中出现过，认为答案是-1.0
// 如果某条查询的答案根本推断不出来，认为答案是-1.0
// 返回所有查询的答案
// 测试链接 : https://leetcode.cn/problems/evaluate-division/

class Solution
{
public:
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        prepare(equations);
        for (size_t i = 0; i < values.size(); ++i)
        {
            unionSet(equations[i][0], equations[i][1], values[i]);
        }
        std::vector<double> ans(queries.size());
        for (size_t i = 0; i < queries.size(); ++i)
        {
            ans[i] = query(queries[i][0], queries[i][1]);
        }
        return ans;
    }

    // 定义全局变量
    std::unordered_map<std::string, std::string> father;
    std::unordered_map<std::string, double> dist;

    // 初始化操作
    void prepare(const std::vector<std::vector<std::string>> &equations)
    {
        father.clear();
        dist.clear();
        for (const auto &list : equations)
        {
            for (const auto &key : list)
            {
                father[key] = key;
                dist[key] = 1.0;
            }
        }
    }

    // 查找操作
    std::string find(const std::string &x)
    {
        if (father.find(x) == father.end())
        {
            return "";
        }
        std::string tmp, fa = x;
        if (x != father[x])
        {
            tmp = father[x];
            fa = find(tmp);
            dist[x] = dist[x] * dist[tmp];
            father[x] = fa;
        }
        return fa;
    }

    // 合并操作
    void unionSet(const std::string &l, const std::string &r, double v)
    {
        std::string lf = find(l), rf = find(r);
        if (lf != rf)
        {
            father[lf] = rf;
            dist[lf] = dist[r] / dist[l] * v;
        }
    }

    // 查询操作
    double query(const std::string &l, const std::string &r)
    {
        std::string lf = find(l), rf = find(r);
        if (lf.empty() || rf.empty() || lf != rf)
        {
            return -1.0;
        }
        return dist[l] / dist[r];
    }
};