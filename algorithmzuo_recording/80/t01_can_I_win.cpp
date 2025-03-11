// 状压dp
// 设计一个整型可变参数status，利用status的位信息，来表示：
// 某个样本是否还能使用，然后利用这个信息进行尝试
// 写出尝试的递归函数 -> 记忆化搜索 -> 严格位置依赖的动态规划 -> 空间压缩等优化

// 如果有k个样本，那么表示这些样本的状态，数量是2^k
// 所以可变参数status的范围： 0 ~ (2^k)-1

// 样本每增加一个，状态的数量是指数级增长的，所以状压dp能解决的问题往往样本数据量都不大
// 一般样本数量在20个以内(10^6)，如果超过这个数量，计算量(指令条数)会超过 10^7 ~ 10^8

// 如果样本数量大到状压dp解决不了，或者任何动态规划都不可行，那么双向广搜是一个备选思路

// 我能赢吗
// 给定两个整数n和m
// 两个玩家可以轮流从公共整数池中抽取从1到n的整数（不放回）
// 抽取的整数会累加起来（两个玩家都算）
// 谁在自己的回合让累加和 >= m，谁获胜
// 若先出手的玩家能稳赢则返回true，否则返回false
// 假设两位玩家游戏时都绝顶聪明，可以全盘为自己打算
// 测试链接 : https://leetcode.cn/problems/can-i-win/

class Solution
{
public:
    bool canIWin(int n, int m)
    {
        if (m == 0)
        {
            // 来自题目规定
            return true;
        }
        if (n * (n + 1) / 2 < m)
        {
            // 如果1~n数字全加起来
            // 累加和和是n * (n+1) / 2，都小于m
            // 那么不会有赢家，也就意味着先手不会获胜
            return false;
        }
        // dp[status] == 0 代表没算过
        // dp[status] == 1 算过，答案是true
        // dp[status] == -1 算过，答案是false
        vector<int> dp(1 << (n + 1));
        return f(n, (1 << (n + 1)) - 1, m, dp);
    }
    // 如果1~7范围的数字都能选，那么status的状态为：
    // 1 1 1 1 1 1 1 1
    // 7 6 5 4 3 2 1 0
    // 0位弃而不用
    // 如果1~7范围的数字，4、2已经选了不能再选，那么status的状态为：
    // 1 1 1 0 1 0 1 1
    // 7 6 5 4 3 2 1 0
    // 0位弃而不用
    // f的含义 :
    // 数字范围1~n，当前的先手，面对status给定的数字状态
    // 在累加和还剩rest的情况下
    // status 决定 rest , 反之不成立 , 所以用一维dp存status !!! (被决定不用管)
    // 返回当前的先手能不能赢，能赢返回true，不能赢返回false
    bool f(int n, int status, int rest, vector<int> &dp)
    {
        if (rest <= 0)
        {
            return false;
        }
        if (dp[status] != 0)
        {
            return dp[status] == 1;
        }
        // rest > 0
        bool ans = false;
        for (int i = 1; i <= n; i++)
        {
            // 考察所有数字，但是不能选择之前选了的数字
            // 对手必须F
            if ((status & (1 << i)) != 0 &&
                !f(n, (status ^ (1 << i)), rest - i, dp))
            {
                ans = true;
                break;
            }
        }
        dp[status] = ans ? 1 : -1;
        return ans;
    }
};