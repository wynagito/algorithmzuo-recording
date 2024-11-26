// 有趣的数列(重要! 因子计数法)
// 求第n项卡特兰数，要求答案对p取模
// 1 <= n <= 10^6
// 1 <= p <= 10^9
// p可能不为质数
// 测试链接 : https://www.luogu.com.cn/problem/P3200

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2000001;
vector<int> minpf(MAXN, 0);  // Smallest prime factor for each number
vector<int> prime(MAXN, 0);  // List of primes
vector<int> counts(MAXN, 0); // Factor counts
int cnt = 0;

// Euler's sieve to calculate smallest prime factor for each number
void euler(int n)
{
    fill(minpf.begin() + 2, minpf.begin() + n + 1, 0);
    cnt = 0;
    for (int i = 2; i <= n; i++)
    {
        if (minpf[i] == 0)
        {
            prime[cnt++] = i;
        }
        for (int j = 0; j < cnt; j++)
        {
            if (i * prime[j] > n)
                break;
            minpf[i * prime[j]] = prime[j];
            if (i % prime[j] == 0)
                break;
        }
    }
}

// Modular exponentiation to calculate (x^p) % mod
long long power(long long x, long long p, int mod)
{
    long long ans = 1;
    while (p > 0)
    {
        if (p & 1)
        {
            ans = (ans * x) % mod;
        }
        x = (x * x) % mod;
        p >>= 1;
    }
    return ans;
}

// Calculate the result using Euler's sieve and prime factor counting
int compute(int n, int mod)
{
    euler(2 * n);

    // Initialize the counts array
    fill(counts.begin() + 2, counts.begin() + n + 1, -1);        // Denominators
    fill(counts.begin() + n + 2, counts.begin() + 2 * n + 1, 1); // Numerators

    // Count prime factors from large to small
    for (int i = 2 * n; i >= 2; i--)
    {
        if (minpf[i] != 0)
        {
            counts[minpf[i]] += counts[i];
            counts[i / minpf[i]] += counts[i];
            counts[i] = 0;
        }
    }

    // Calculate the final answer
    long long ans = 1;
    for (int i = 2; i <= 2 * n; i++)
    {
        if (counts[i] != 0)
        {
            ans = (ans * power(i, counts[i], mod)) % mod;
        }
    }
    return static_cast<int>(ans);
}

int main()
{
    int n, mod;
    cin >> n >> mod;
    cout << compute(n, mod) << endl;
    return 0;
}
