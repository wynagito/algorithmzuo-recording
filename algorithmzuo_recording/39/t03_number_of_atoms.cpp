// 含有嵌套的分子式求原子数量
// 测试链接 : https://leetcode.cn/problems/number-of-atoms/

#include <map>
#include <string>
#include <cctype>

using namespace std;

class Solution
{
public:
    string countOfAtoms(string formula)
    {
        map<string, int> atomCount = f(formula, 0);
        string result;

        for (const auto &entry : atomCount)
        {
            result += entry.first;
            if (entry.second > 1)
            {
                result += to_string(entry.second);
            }
        }
        return result;
    }

    int where = 0;

    // s[i....]开始计算，遇到字符串终止 或者 遇到 ) 停止
    // 返回 : 自己负责的这一段字符串的结果，有序表！
    // 返回之间，更新全局变量where，为了上游函数知道从哪继续！
    map<string, int> f(const string &s, int i)
    {
        // ans是总表
        map<string, int> ans;
        // 之前收集到的名字，历史一部分
        string name;
        // 之前收集到的有序表，历史一部分
        map<string, int> pre;
        // 历史翻几倍
        int cnt = 0;

        while (i < s.size() && s[i] != ')')
        {
            if (isupper(s[i]) || s[i] == '(')
            {
                fill(ans, name, pre, cnt);
                name.clear();
                pre.clear();
                cnt = 0;
                if (isupper(s[i]))
                {
                    name += s[i++];
                }
                else
                {
                    // 遇到左括号
                    pre = f(s, i + 1);
                    i = where + 1;
                }
            }
            else if (islower(s[i]))
            {
                name += s[i++];
            }
            else
            {
                cnt = cnt * 10 + (s[i++] - '0');
            }
        }
        fill(ans, name, pre, cnt);
        where = i;
        return ans;
    }

    void fill(map<string, int> &ans, string &name, const map<string, int> &pre, int cnt)
    {
        if (!name.empty() || !pre.empty())
        {
            cnt = (cnt == 0) ? 1 : cnt;
            if (!name.empty())
            {
                ans[name] += cnt;
            }
            else
            {
                for (const auto &entry : pre)
                {
                    ans[entry.first] += entry.second * cnt;
                }
            }
        }
    }
};
