// 前缀树又叫字典树，英文名trie：
// 每个样本 都从头节点开始 根据 前缀字符或者前缀数字 建出来的一棵大树，就是前缀树
// 没有路就新建节点；已经有路了，就复用节点

// 前缀树的使用场景：需要根据前缀信息来查询的场景
// 前缀树的优点：根据前缀信息选择树上的分支，可以节省大量的时间
// 前缀树的缺点：比较浪费空间，和总字符数量有关，字符的种类有关
// 前缀树的定制：pass、end等信息

// 实现前缀树 Trie 类：
// 1. Trie() 初始化前缀树对象。
// 2. void insert(String word) 将字符串 word 插入前缀树中。
// 3. int search(String word) 返回前缀树中字符串 word 的实例个数。
// 4. int prefixNumber(String prefix) 返回前缀树中以 prefix 为前缀的字符串个数
// 5. void delete(String word) 从前缀树中移除字符串 word 。

// 用类描述实现前缀树。不推荐！
// 测试链接 : https://leetcode.cn/problems/implement-trie-ii-prefix-tree/
// 用固定数组实现前缀树，空间使用是静态的。推荐！
// 测试链接 : https://www.nowcoder.com/practice/7f8a8553ddbf4eaab749ec988726702b

#include <iostream>
#include <unordered_map>
#include <string>

using std ::cin;
using std ::cout;
using std ::endl;
using std ::string;
using std ::unordered_map;

// 路是数组实现的
// 提交时把类名、构造方法改为Trie
class Trie1
{
private:
    class TrieNode
    {
    public:
        int pass;
        int end;
        TrieNode *nexts[26]; // 数组

        TrieNode()
        {
            pass = 0; // 经过当前节点的字符串个数 即可以求前缀的个数
            end = 0;  // 以当前节点为结尾的字符串个数 即可以求单词的个数
            for (int i = 0; i < 26; i++)
            {
                nexts[i] = nullptr;
            }
        }
    };

    TrieNode *root;

public:
    Trie1()
    {
        // 代表空字符串
        root = new TrieNode();
    }

    void insert(const string &word)
    {
        TrieNode *node = root;
        node->pass++;
        for (char c : word)
        {
            // 从左往右遍历字符
            int path = c - 'a'; // 由字符，对应成走向哪条路
            if (node->nexts[path] == nullptr)
            {
                node->nexts[path] = new TrieNode();
            }
            node = node->nexts[path];
            node->pass++;
        }
        node->end++;
    }

    // 如果之前word插入过前缀树，那么此时删掉一次
    // 如果之前word没有插入过前缀树，那么什么也不做
    void erase(const string &word)
    {
        if (countWordsEqualTo(word) > 0)
        {
            TrieNode *node = root;
            node->pass--;
            for (char c : word)
            {
                int path = c - 'a';
                if (--node->nexts[path]->pass == 0)
                {
                    node->nexts[path] = nullptr;
                    return;
                }
                node = node->nexts[path];
            }
            node->end--;
        }
    }

    // 查询前缀树里，word单词出现了几次
    int countWordsEqualTo(const string &word)
    {
        TrieNode *node = root;
        for (char c : word)
        {
            int path = c - 'a';
            if (node->nexts[path] == nullptr)
            {
                return 0;
            }
            node = node->nexts[path];
        }
        return node->end;
    }

    // 查询前缀树里，有多少单词以pre做前缀
    int countWordsStartingWith(const string &pre)
    {
        TrieNode *node = root;
        for (char c : pre)
        {
            int path = c - 'a';
            if (node->nexts[path] == nullptr)
            {
                return 0;
            }
            node = node->nexts[path];
        }
        return node->pass;
    }
};

// 路是哈希表实现的
// 提交时把类名、构造方法改为Trie
class Trie2
{
private:
    class TrieNode
    {
    public:
        int pass;
        int end;
        unordered_map<char, TrieNode *> nexts;

        TrieNode()
        {
            pass = 0;
            end = 0;
        }
    };

    TrieNode *root;

public:
    Trie2()
    {
        root = new TrieNode();
    }

    void insert(const string &word)
    {
        TrieNode *node = root;
        node->pass++;
        for (char c : word)
        {
            // 从左往右遍历字符
            if (node->nexts.find(c) == node->nexts.end())
            {
                node->nexts[c] = new TrieNode();
            }
            node = node->nexts[c];
            node->pass++;
        }
        node->end++;
    }

    void erase(const string &word)
    {
        if (countWordsEqualTo(word) > 0)
        {
            TrieNode *node = root;
            node->pass--;
            for (char c : word)
            {
                TrieNode *next = node->nexts[c];
                if (--next->pass == 0)
                {
                    node->nexts.erase(c);
                    return;
                }
                node = next;
            }
            node->end--;
        }
    }

    int countWordsEqualTo(const string &word)
    {
        TrieNode *node = root;
        for (char c : word)
        {
            if (node->nexts.find(c) == node->nexts.end())
            {
                return 0;
            }
            node = node->nexts[c];
        }
        return node->end;
    }

    int countWordsStartingWith(const string &pre)
    {
        TrieNode *node = root;
        for (char c : pre)
        {
            if (node->nexts.find(c) == node->nexts.end())
            {
                return 0;
            }
            node = node->nexts[c];
        }
        return node->pass;
    }
};

// 如果将来增加了数据量，就改大这个值
const int MAXN = 150001;

int tree[MAXN][26];

int end[MAXN];

int pass[MAXN];

int cnt = 1;

void insert(string word)
{
    int cur = 1;
    pass[cur]++;
    for (int i = 0, path; i < word.size(); i++)
    {
        path = word[i] - 'a';
        if (tree[cur][path] == 0)
        {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
        pass[cur]++;
    }
    end[cur]++;
}

int search(string word)
{
    int cur = 1;
    for (int i = 0, path; i < word.size(); i++)
    {
        path = word[i] - 'a';
        if (tree[cur][path] == 0)
        {
            return 0;
        }
        cur = tree[cur][path];
    }
    return end[cur];
}

int prefixNumber(string pre)
{
    int cur = 1;
    for (int i = 0, path; i < pre.size(); i++)
    {
        path = pre[i] - 'a';
        if (tree[cur][path] == 0)
        {
            return 0;
        }
        cur = tree[cur][path];
    }
    return pass[cur];
}

void deletefunc(string word)
{
    if (search(word) > 0)
    {
        int cur = 1;
        for (int i = 0, path; i < word.size(); i++)
        {
            path = word[i] - 'a';
            if (--pass[tree[cur][path]] == 0)
            {
                tree[cur][path] = 0;
                return;
            }
            cur = tree[cur][path];
        }
        end[cur]--;
    }
}

int main()
{
    int m, op;
    cin >> m;
    string word;
    for (int i = 1; i <= m; i++)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> word;
            insert(word);
        }
        else if (op == 2)
        {
            cin >> word;
            deletefunc(word);
        }
        else if (op == 3)
        {
            cin >> word;
            cout << (search(word) > 0 ? "YES" : "NO") << endl;
        }
        else if (op == 4)
        {
            cin >> word;
            cout << prefixNumber(word) << endl;
        }
    }
    return 0;
}
