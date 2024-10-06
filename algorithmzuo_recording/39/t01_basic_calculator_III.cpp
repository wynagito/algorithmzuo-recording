// 嵌套类问题的解题套路
// 大概过程:
// 定义全局变量 int where
// 递归函数f(i) : s[i..]，从i位置出发开始解析，遇到 字符串终止 或 嵌套条件终止 就返回
// 返回值是f(i)负责这一段的结果
// f(i)在返回前更新全局变量where，让上级函数通过where知道解析到了什么位置，进而继续
// 执行细节:
// 如果f(i)遇到 嵌套条件开始，就调用下级递归去处理嵌套，下级会负责嵌套部分的计算结果
// f(i)下级处理完成后，f(i)可以根据下级更新的全局变量where，知道该从什么位置继续解析

// 含有嵌套的表达式求值
// 表达式字符串只包含非负整数，算符 + - * /，以及括号 ( ) 整数除法向下截断
// 表达式中可能包含嵌套的括号，如 (2+3) * 4
// 给定一个表达式字符串，求其计算结果
// 示例:
// 输入: "1 + 1"
// 输出: 2
// 输入: " 2-1 + 2 "
// 输出: 3
// 输入: "(1+(4+5+2)-3)+(6+8)"
// 输出: 23
// 输入: "2*(5+5*2)/3+(6/2+8)"
// 输出: 22
// 测试链接 : https://leetcode.cn/problems/basic-calculator-iii/
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int where = 0;

    int calculate(string str)
    {
        where = 0;
        return f(str.c_str(), 0);
    }

    // s[i....]开始计算，遇到字符串终止 或者 遇到)停止
    // 返回 : 自己负责的这一段，计算的结果
    // 返回之间，更新全局变量where，为了上游函数知道从哪继续！
    int f(const char *s, int i)
    {
        int cur = 0;
        vector<int> numbers;
        vector<char> ops;

        while (i < strlen(s) && s[i] != ')')
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                cur = cur * 10 + (s[i++] - '0');
            }
            else if (s[i] != '(')
            {
                // 遇到了运算符 + - * /
                push(numbers, ops, cur, s[i++]);
                cur = 0;
            }
            else
            {
                // 遇到了左括号！
                cur = f(s, i + 1);
                i = where + 1;
            }
        }
        push(numbers, ops, cur, '+');
        where = i;
        return compute(numbers, ops);
    }

    void push(vector<int> &numbers, vector<char> &ops, int cur, char op)
    {
        int n = numbers.size();
        if (n == 0 || ops[n - 1] == '+' || ops[n - 1] == '-')
        {
            numbers.push_back(cur);
            ops.push_back(op);
        }
        else
        {
            int topNumber = numbers[n - 1];
            char topOp = ops[n - 1];
            if (topOp == '*')
            {
                numbers[n - 1] = topNumber * cur;
            }
            else
            {
                numbers[n - 1] = topNumber / cur;
            }
            ops[n - 1] = op;
        }
    }

    int compute(const vector<int> &numbers, const vector<char> &ops)
    {
        int n = numbers.size();
        int ans = numbers[0];
        for (int i = 1; i < n; i++)
        {
            ans += ops[i - 1] == '+' ? numbers[i] : -numbers[i];
        }
        return ans;
    }
};
