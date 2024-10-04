// 全O(1)的数据结构
// 测试链接 : https://leetcode.cn/problems/all-oone-data-structure/

#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class AllOne
{
    // 双向链表
    // 链表中的每个节点存储一个字符串集合 keys，
    // 和一个正整数count，表示keys 中的字符串均出现count 次。
    // 链表从头到尾的每个节点的 count 值单调递增（但不一定连续）。
    // 此外，每个节点还需存储指向上一个节点的指针 prev 和指向下一个节点的指针 next

    list<pair<unordered_set<string>, int>> lst;

    // 另外还要用一个哈希表 nodes 维护每个字符串当前所处的链表节点。
    unordered_map<string, list<pair<unordered_set<string>, int>>::iterator> nodes;

public:
    AllOne() {
        lst.clear();
        nodes.clear();
    }

    void inc(string key)
    {
        if (nodes.count(key))
        {
            auto cur = nodes[key], nxt = next(cur);
            if (nxt == lst.end() || nxt->second > cur->second + 1)
            {
                unordered_set<string> s({key});
                nodes[key] = lst.emplace(nxt, s, cur->second + 1);
            }
            else
            {
                nxt->first.emplace(key);
                nodes[key] = nxt;
            }
            cur->first.erase(key);
            if (cur->first.empty())
            {
                lst.erase(cur);
            }
        }
        else
        { // key 不在链表中
            if (lst.empty() || lst.begin()->second > 1)
            {
                unordered_set<string> s({key});
                lst.emplace_front(s, 1);
            }
            else
            {
                lst.begin()->first.emplace(key);
            }
            nodes[key] = lst.begin();
        }
    }

    void dec(string key)
    {
        auto cur = nodes[key];
        if (cur->second == 1)
        { // key 仅出现一次，将其移出 nodes
            nodes.erase(key);
        }
        else
        {
            auto pre = prev(cur);
            if (cur == lst.begin() || pre->second < cur->second - 1)
            {
                unordered_set<string> s({key});
                nodes[key] = lst.emplace(cur, s, cur->second - 1);
            }
            else
            {
                pre->first.emplace(key);
                nodes[key] = pre;
            }
        }
        cur->first.erase(key);
        if (cur->first.empty())
        {
            lst.erase(cur);
        }
    }

    string getMaxKey()
    {
        return lst.empty() ? "" : *lst.rbegin()->first.begin();
    }

    string getMinKey()
    {
        return lst.empty() ? "" : *lst.begin()->first.begin();
    }
};