// 字符串的全部子序列
// 子序列本身是可以有重复的，只是这个题目要求去重
// 测试链接 : https://www.nowcoder.com/practice/92e6247998294f2c933906fdedbc6e6a

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution
{
public:
    void f1(const vector<char> &s, int i, string path, unordered_set<string> &set)
    {
        if (i == s.size())
        {
            set.insert(path); // 添加路径到集合中以去重
        }
        else
        {
            // 将当前字符加到路径中
            path.push_back(s[i]);
            f1(s, i + 1, path, set); // 选择当前字符
            path.pop_back();         // 从路径中移除当前字符
            f1(s, i + 1, path, set); // 不选择当前字符
        }
    }

    vector<string> generatePermutation1(const string &str)
    {
        vector<char> s(str.begin(), str.end());
        unordered_set<string> set;
        f1(s, 0, "", set);

        vector<string> ans(set.begin(), set.end());
        return ans;
    }

    void f2(const vector<char> &s, int i, vector<char> &path, int size, unordered_set<string> &set)
    {
        if (i == s.size())
        {
            set.insert(string(path.begin(), path.begin() + size)); // 将路径转换成字符串并插入
        }
        else
        {
            path[size] = s[i];
            f2(s, i + 1, path, size + 1, set); // 选择当前字符
            f2(s, i + 1, path, size, set);     // 不选择当前字符
        }
    }

    vector<string> generatePermutation2(const string &str)
    {
        vector<char> s(str.begin(), str.end());
        unordered_set<string> set;
        vector<char> path(s.size());
        f2(s, 0, path, 0, set);

        vector<string> ans(set.begin(), set.end());
        return ans;
    }
};
