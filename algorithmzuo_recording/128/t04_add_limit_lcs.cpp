// 增加限制的最长公共子序列问题
// 给定两个字符串s1和s2，s1长度为n，s2长度为m
// 返回s1和s2的最长公共子序列长度
// 注意：
// 两个字符串都只由小写字母组成
// 1 <= n <= 10^6
// 1 <= m <= 10^3
// 状态设计优化的经典题，对数器验证

#include <iostream>
#include <vector>
#include <ctime>
#include <climits>
#include <cstdlib>

using namespace std;

const int MAXN = 1000005;
const int MAXM = 1005;
const int NA = INT_MAX;

int n, m;
vector<int> rightarr(26);
vector<vector<int>> nxt(MAXN, vector<int>(26));
vector<vector<int>> dp(MAXM, vector<int>(MAXM));
vector<char> s1, s2;

// 随机生成长度为n的只含小写字母的字符串
string randomString(int n) {
    string ans(n, ' ');
    for (int i = 0; i < n; ++i) {
        ans[i] = 'a' + rand() % 26;
    }
    return ans;
}

// 经典动态规划版本，时间复杂度O(n*m)
int lcs1(const string& str1, const string& str2) {
    int n = str1.length();
    int m = str2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// 优化版本，时间复杂度O(26*n + m^2)
void build() {
    fill(rightarr.begin(), rightarr.end(), NA);
    for (int i = n; i >= 0; --i) {
        for (int j = 0; j < 26; ++j) {
            nxt[i][j] = rightarr[j];
        }
        if (i > 0) {
            rightarr[s1[i - 1] - 'a'] = i;
        }
    }
    for (int i = 0; i <= m; ++i) {
        fill(dp[i].begin(), dp[i].end(), -1);
    }
}

// 返回长度为j的公共子序列，至少需要多长的s1前缀串才能做到，不能做到返回NA
int f(int i, int j) {
    if (i < j) return NA;
    if (j == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    
    int cha = s2[i - 1] - 'a';
    int ans = f(i - 1, j);
    int pre = f(i - 1, j - 1);
    
    if (pre != NA) {
        ans = min(ans, nxt[pre][cha]);
    }
    
    dp[i][j] = ans;
    return ans;
}

int lcs2(const string& str1, const string& str2) {
    s1 = vector<char>(str1.begin(), str1.end());
    s2 = vector<char>(str2.begin(), str2.end());
    n = s1.size();
    m = s2.size();
    
    build();
    
    int ans = 0;
    for (int j = m; j >= 1; --j) {
        if (f(m, j) != NA) {
            ans = j;
            break;
        }
    }
    return ans;
}

int main() {
    srand(time(nullptr));  // 设置随机种子

    int n = 100, m = 100;
    int testTime = 10000;
    
    cout << "功能测试开始" << endl;
    for (int i = 0; i < testTime; ++i) {
        int size1 = rand() % n + 1;
        int size2 = rand() % m + 1;
        string str1 = randomString(size1);
        string str2 = randomString(size2);
        int ans1 = lcs1(str1, str2);
        int ans2 = lcs2(str1, str2);
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
        }
    }
    cout << "功能测试结束" << endl;
    cout << endl;
    
    cout << "性能测试开始" << endl;
    n = 1000000;
    m = 1000;
    cout << "n = " << n << endl;
    cout << "m = " << m << endl;
    
    string str1 = randomString(n);
    string str2 = randomString(m);
    
    clock_t start, end;
    
    start = clock();
    lcs1(str1, str2);
    end = clock();
    cout << "lcs1方法运行时间: " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " 毫秒" << endl;
    
    start = clock();
    lcs2(str1, str2);
    end = clock();
    cout << "lcs2方法运行时间: " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " 毫秒" << endl;
    
    cout << "性能测试结束" << endl;

    return 0;
}
