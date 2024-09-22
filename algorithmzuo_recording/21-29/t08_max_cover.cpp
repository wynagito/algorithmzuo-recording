// 最多线段重合问题
// 测试链接 : https://www.nowcoder.com/practice/1ae8d0b6bb4e4bcdbf64ec491f63fc37

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 10010;

vector<vector<int>> line;

int n , a , b;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        line.push_back({a, b});
    }
    // 按起始位置升序排序
    sort(line.begin(), line.end(), [](const vector<int> &a, const vector<int> &b)
         { return a[0] < b[0]; });
    // 小根堆 存结束位置
    priority_queue<int, vector<int>, greater<int>> pq;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        while (!pq.empty() && pq.top() <= line[i][0])
        {
            pq.pop();
        }
        pq.push(line[i][1]);
        ans = max(ans, (int)pq.size());
    }
    cout << ans << endl;
    return 0;
}
