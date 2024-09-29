// setAll功能的哈希表
// 测试链接 : https://www.nowcoder.com/practice/7c4559f138e74ceb9ba57d76fd169967

#include <iostream>
#include <unordered_map>
using namespace std;

// key : {value , count}
unordered_map<int, pair<int, int>> mp;
int cnt = 0; // 计时器思想
int allval = 0;
int alltimes = -1;

int main()
{
    int n, op, x, y;
    cin >> n;
    while (n--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> x >> y;
            if (mp.count(x))
            {
                mp[x].first = y;
                mp[x].second = cnt++;
            }
            else
            {
                mp[x] = make_pair(y, cnt++);
            }
        }
        else if (op == 2)
        {
            cin >> x;
            if (mp.count(x))
            {
                if (mp[x].second > alltimes)
                {
                    cout << mp[x].first << endl;
                }
                else
                {
                    cout << allval << endl;
                }
            }
            else
            {
                cout << -1 << endl;
            }
        }
        else
        {
            cin >> y;
            allval = y;
            alltimes = cnt++;
        }
    }
    return 0;
}