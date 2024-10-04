// 最大频率栈
// 测试链接 : https://leetcode.cn/problems/maximum-frequency-stack/

#include <unordered_map>
#include <stack>
#include <algorithm>

using namespace std;

class FreqStack
{
private:
    // 每一个数出现了几次
    unordered_map<int, int> freq;
    // 每层节点
    unordered_map<int, stack<int>> group;
    // 出现的最大次数
    int maxFreq;

public:
    FreqStack()
    {
        maxFreq = 0;
        freq.clear();
        group.clear();
    }

    void push(int val)
    {
        freq[val]++;
        group[freq[val]].push(val);
        maxFreq = max(maxFreq, freq[val]);
    }

    int pop()
    {
        int val = group[maxFreq].top();
        freq[val]--;
        group[maxFreq].pop();
        if (group[maxFreq].empty())
        {
            maxFreq--;
        }
        return val;
    }
};