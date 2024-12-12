// 不同的子序列 II
// 给定一个字符串 s，计算 s 的 不同非空子序列 的个数
// 因为结果可能很大，答案对 1000000007 取模
// 字符串的 子序列 是经由原字符串删除一些（也可能不删除）
// 字符但不改变剩余字符相对位置的一个新字符串
// 例如，"ace" 是 "abcde" 的一个子序列，但 "aec" 不是
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences-ii/

class Solution
{
public:
    // 初始时，所有子序列都是空集，cnt[i] = 0
    // cnt[i] : 有多少的子序列是以'a' + i 结尾的
    int cnt[26];

    // eg aba
    // step1 {} | {a}
    // all = 1
    // newAdd = all - cnt[0]  = 1
    // cnt[0] = 1
    // all = 2
    // step2 {} | {a} | {b} {ab}
    // newAdd = all - cnt[1] = 2
    // cnt[1] = 2
    // all = 4
    // step3 {} | {a} | {b} {ab} | {a} {ba} {aba} {aa} --> {} | {a} | {b} {ab} | {ba} {aba} {aa}
    // newAdd = all - cnt[0] = 4 - 1 = 3
    // cnt[0] = 1 + 3 = 4
    // all = 7

    int distinctSubseqII(string s)
    {
        int mod = 1000000007;
        int all = 1, newAdd;
        // newAdd 新增子序列的个数
        // all 最终子序列的个数，1是算上空集
        for (char x : s)
        {
            // all - 当前字符上次记录 --> 新增子序列的个数
            newAdd = (all - cnt[x - 'a'] + mod) % mod;
            // 更新 cnt[x]
            cnt[x - 'a'] = (cnt[x - 'a'] + newAdd) % mod;
            // 更新 all
            all = (all + newAdd) % mod;
        }
        // 去掉空集
        return (all - 1 + mod) % mod;
    }
};