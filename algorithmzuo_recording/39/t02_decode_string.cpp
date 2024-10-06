// 含有嵌套的字符串解码
// 测试链接 : https://leetcode.cn/problems/decode-string/

class Solution
{
public:
    string decodeString(string s)
    {
        return f(s.c_str(), 0);
    }
    int where = 0;

    // s[i....]开始计算，遇到字符串终止 或者 遇到 ] 停止
    // 返回 : 自己负责的这一段字符串的结果
    // 返回之间，更新全局变量where，为了上游函数知道从哪继续！
    string f(const char *s, int i)
    {
        string path = "";
        int cnt = 0;
        while (i < strlen(s) && s[i] != ']')
        {
            if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            {
                path.push_back(s[i++]);
            }
            else if (s[i] >= '0' && s[i] <= '9')
            {
                cnt = cnt * 10 + s[i++] - '0';
            }
            else
            {
                // 遇到 [
                // cnt = 7 * ?
                path += get(cnt, f(s, i + 1));
                i = where + 1;
                cnt = 0;
            }
        }
        where = i;
        return path;
    }

    string get(int cnt, string str)
    {
        string builder = "";
        for (int i = 0; i < cnt; i++)
        {
            builder += str;
        }
        return builder;
    }
};