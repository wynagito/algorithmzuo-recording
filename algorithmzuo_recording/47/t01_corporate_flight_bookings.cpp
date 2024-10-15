// 等差数列差分问题描述：
// 一开始1~n范围上的数字都是0。接下来一共有m个操作。
// 每次操作：l~r范围上依次加上首项s、末项e、公差d的数列
// 最终1~n范围上的每个数字都要正确得到

// 等差数列差分的过程：
// 每个操作调用set方法
// 所有操作完成后在arr上生成两遍前缀和，即调用build方法
// arr里就是最终1~n范围上的每个数字

// void set(int l, int r, int s, int e, int d)
// {
//     arr[l] += s;
//     arr[l + 1] += d - s;
//     arr[r + 1] -= d + e;
//     arr[r + 2] += e;
// }

// void build()
// {
//     for (int i = 1; i <= n; i++)
//     {
//         arr[i] += arr[i - 1];
//     }
//     for (int i = 1; i <= n; i++)
//     {
//         arr[i] += arr[i - 1];
//     }
// }

// 航班预订统计
// 这里有 n 个航班，它们分别从 1 到 n 进行编号。
// 有一份航班预订表 bookings ，
// 表中第 i 条预订记录 bookings[i] = [firsti, lasti, seatsi]
// 意味着在从 firsti 到 lasti
// （包含 firsti 和 lasti ）的 每个航班 上预订了 seatsi 个座位。
// 请你返回一个长度为 n 的数组 answer，里面的元素是每个航班预定的座位总数。
// 测试链接 : https://leetcode.cn/problems/corporate-flight-bookings/

class Solution
{
public:
    vector<int> corpFlightBookings(vector<vector<int>> &bookings, int n)
    {
        int cnt[20010] = {0};
        // 设置差分数组，每一个操作对应两个设置
        // [L...R] +v
        // 1. [L] +v
        // 2. [R+1] -v
        // 3. 一遍前缀和
        for (auto a : bookings)
        {
            cnt[a[0]] += a[2];
            cnt[a[1] + 1] -= a[2];
        }
        // 1   2   3   4   5   6
        // 10     -10
        //     20     -20
        //     25             -25
        // 10  45 -10 -20     -25
        // 一遍前缀和
        // 10  55  45  25  25  0
        vector<int> res;
        // 加工前缀和
        for (int i = 1; i <= n; ++i)
        {
            cnt[i] += cnt[i - 1];
            res.push_back(cnt[i]);
        }
        return res;
    }
};