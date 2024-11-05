// 去除重复字母保证剩余字符串的字典序最小
// 给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次
// 需保证 返回结果的字典序最小
// 要求不能打乱其他字符的相对位置
// 测试链接 : https://leetcode.cn/problems/remove-duplicate-letters/

class Solution
{
public:
    char stack[30];           // 字符值从小到大
    int cnts[26] = {0};       // 每种字符词频
    bool enter[26] = {false}; // 每种字符目前有没有进栈
    string removeDuplicateLetters(string s)
    {
        int r = 0;
        for (char cha : s)
        {
            cnts[cha - 'a']++;
        }
        for (char cur : s)
        {
            // 从左往右依次遍历字符，a -> 0 b -> 1 ... z -> 25
            // cur -> cur - 'a'
            if (!enter[cur - 'a'])
            {
                // 保证栈顶字符后面还有才弹出，不然不满足题意(每个字母只出现一次)
                while (r > 0 && stack[r - 1] > cur && cnts[stack[r - 1] - 'a'] > 0)
                {
                    enter[stack[r - 1] - 'a'] = false; // 使得后面字符能进来
                    r--;
                }
                stack[r++] = cur;
                enter[cur - 'a'] = true;
            }
            cnts[cur - 'a']--;
        }
        // 最终的单调栈内的字符就是所求的解，满足字典序最小
        stack[r] = '\0';
        return stack;
    }
};