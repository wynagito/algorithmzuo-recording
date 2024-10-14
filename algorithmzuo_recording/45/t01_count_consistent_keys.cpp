// 牛牛和他的朋友们约定了一套接头密匙系统，用于确认彼此身份
// 密匙由一组数字序列表示，两个密匙被认为是一致的，如果满足以下条件：
// 密匙 b 的长度不超过密匙 a 的长度。
// 对于任意 0 <= i < length(b)，有b[i+1] - b[i] == a[i+1] - a[i]
// 现在给定了m个密匙 b 的数组，以及n个密匙 a 的数组
// 请你返回一个长度为 m 的结果数组 ans，表示每个密匙b都有多少一致的密匙
// 数组 a 和数组 b 中的元素个数均不超过 10^5
// 1 <= m, n <= 1000
// 测试链接 : https://www.nowcoder.com/practice/c552d3b4dfda49ccb883a6371d9a6932

// 如果将来增加了数据量，就改大这个值
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

const int MAXN = 2000001;

int tree[MAXN][12];

int pass[MAXN];

int cnt = 1;

class Solution
{
public:
    vector<int> countConsistentKeys(vector<vector<int>> &b, vector<vector<int>> &a)
    {
        string builder = "";
        // [3,6,50,10] -> "3#44#-40#"
        for (auto nums : a)
        {
            builder.clear();
            for (int i = 1; i < nums.size(); i++)
            {
                builder += to_string(nums[i] - nums[i - 1]) + "#";
            }
            insert(builder);
        }
        vector<int> ans(b.size());
        for (int i = 0; i < b.size(); i++)
        {
            string builder = "";
            for (int j = 1; j < b[i].size(); j++)
            {
                builder += to_string(b[i][j] - b[i][j - 1]) + "#";
            }
            ans[i] = count(builder);
        }
        return ans;
    }

    // '0' ~ '9' 10个 0~9
    // '#' 10
    // '-' 11
    int pathfunc(char cha)
    {
        if (cha == '#')
        {
            return 10;
        }
        else if (cha == '-')
        {
            return 11;
        }
        else
        {
            return cha - '0';
        }
    }

    void insert(string word)
    {
        int cur = 1;
        pass[cur]++;
        for (int i = 0, path; i < word.size(); i++)
        {
            path = pathfunc(word[i]);
            if (tree[cur][path] == 0)
            {
                tree[cur][path] = ++cnt;
            }
            cur = tree[cur][path];
            pass[cur]++;
        }
    }

    int count(string pre)
    {
        int cur = 1;
        for (int i = 0, path; i < pre.size(); i++)
        {
            path = pathfunc(pre[i]);
            if (tree[cur][path] == 0)
            {
                return 0;
            }
            cur = tree[cur][path];
        }
        return pass[cur];
    }
};