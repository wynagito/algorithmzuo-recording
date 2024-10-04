// 快速获得数据流的中位数的结构
// 测试链接 : https://leetcode.cn/problems/find-median-from-data-stream/

#include <queue>
#include <vector>

using namespace std;

class MedianFinder
{
public:
    // 用两个优先队列 queMax 和 queMin 分别记录大于中位数的数和小于等于中位数的数
    // 保证queMax 和 queMin 的之间的大小不超过2
    priority_queue<int> queMin;                            // 大根堆 较小的一半
    priority_queue<int, vector<int>, greater<int>> queMax; // 小根堆 较大的一半

    MedianFinder()
    {
        queMax.clear();
        queMin.clear();
    }

    void addNum(int num)
    {
        if (queMin.empty() || num <= queMin.top())
        {
            queMin.push(num);
            if (queMax.size() + 1 < queMin.size())
            {
                queMax.push(queMin.top());
                queMin.pop();
            }
        }
        else
        {
            queMax.push(num);
            if (queMax.size() > queMin.size())
            {
                queMin.push(queMax.top());
                queMax.pop();
            }
        }
    }

    double findMedian()
    {
        if (queMin.size() > queMax.size())
        {
            return queMin.top();
        }
        return (queMin.top() + queMax.top()) / 2.0;
    }
};