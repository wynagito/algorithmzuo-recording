// 你可以安排的最多任务数目
// 给你 n 个任务和 m 个工人。每个任务需要一定的力量值才能完成
// 需要的力量值保存在下标从 0 开始的整数数组 tasks 中，
// 第i个任务需要 tasks[i] 的力量才能完成
// 每个工人的力量值保存在下标从 0 开始的整数数组workers中，
// 第j个工人的力量值为 workers[j]
// 每个工人只能完成一个任务，且力量值需要大于等于该任务的力量要求值，即workers[j]>=tasks[i]
// 除此以外，你还有 pills 个神奇药丸，可以给 一个工人的力量值 增加 strength
// 你可以决定给哪些工人使用药丸，但每个工人 最多 只能使用 一片 药丸
// 给你下标从 0 开始的整数数组tasks 和 workers 以及两个整数 pills 和 strength
// 请你返回 最多 有多少个任务可以被完成。
// 测试链接 : https://leetcode.cn/problems/maximum-number-of-tasks-you-can-assign/

class Solution
{
public:
    int deque[50010];
    int h, t;

    // 两个数组排序 : O(n * logn) + O(m * logm)
    // 二分答案的过程，每次二分都用一下双端队列 : O((n和m最小值)*log(n和m最小值))
    // 最复杂的反而是排序的过程了，所以时间复杂度O(n * logn) + O(m * logm)
    int maxTaskAssign(vector<int> &tasks, vector<int> &workers, int pills,
                      int strength)
    {
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());
        int tsize = tasks.size();
        int wsize = workers.size();
        int ans = 0;
        // 每个工人最多只能干一份任务
        // [0, min(tsize, wsize)]
        for (int l = 0, r = min(tsize, wsize), m; l <= r;)
        {
            // m中点，一定要完成的任务数量
            m = (l + r) / 2;
            if (f(0, m - 1, wsize - m, wsize - 1, strength, pills, tasks,
                  workers))
            {
                ans = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        return ans;
    }

    // 贪心思考，每次都选择力量最小的任务，并且力量值最大的工人
    // tasks[tl....tr]需要力量最小的几个任务
    // workers[wl....wr]力量值最大的几个工人
    // 药效是s，一共有的药pills个
    // 在药的数量不超情况下，能不能每个工人都做一个任务
    bool f(int tl, int tr, int wl, int wr, int s, int pills, vector<int> &tasks,
           vector<int> &workers)
    {
        h = t = 0;
        // 已经使用的药的数量
        int cnt = 0;
        // 双端队列，存放任务的编号 任务大小从小到大
        // 工人不吃药的情况下 先解决最小任务，这样保证后面的工人都有任务可以解锁
        // 因为工人力量从小到大，所以先解锁力量最小的任务
        // 吃药之后，先解决最大任务，这样保证后面的工人都有任务可以解锁
        // 因为后面的工人未必吃药，所以需要判断一下
        for (int i = wl, j = tl; i <= wr; i++)
        {
            // i : 工人的编号
            // j : 任务的编号
            for (; j <= tr && tasks[j] <= workers[i]; j++)
            {
                // 工人不吃药的情况下，去解锁任务
                deque[t++] = j;
            }
            // 不吃药的情况下，先解决最小任务，这样最优
            if (h < t && tasks[deque[h]] <= workers[i])
            {
                h++;
            }
            else
            {
                // 吃药之后的逻辑
                for (; j <= tr && tasks[j] <= workers[i] + s; j++)
                {
                    deque[t++] = j;
                }
                // 吃药之后，先解决最大任务，这样最优
                // 因为后面的工人未必吃药，所以需要判断一下
                if (h < t)
                {
                    cnt++;
                    t--;
                }
                else
                {
                    // 吃不吃药都不行，返回false
                    return false;
                }
            }
        }
        return cnt <= pills;
    }
};
