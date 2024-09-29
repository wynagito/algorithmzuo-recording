// 复制带随机指针的链表
// 测试链接 : https://leetcode.cn/problems/copy-list-with-random-pointer/

#include <cstddef>

class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution
{
public:
    Node *copyRandomList(Node *head)
    {
        if (!head)
            return head;
        Node *p = head;
        // 1 -> 2 -> 3 -> ...
        // 变成 : 1 -> 1' -> 2 -> 2' -> 3 -> 3' -> ...
        while (p)
        {
            Node *q = new Node(p->val);
            q->next = p->next;
            p->next = q;
            p = p->next->next;
        }
        p = head;
        Node *r = head->next;
        // 利用上面新老节点的结构关系，设置每一个新节点的random指针
        while (p)
        {
            r->random = (p->random ? p->random->next : p->random);
            if (r->next)
                r = r->next->next;
            else
                r = r->next;
            p = p->next->next;
        }
        p = head;
        Node *h = new Node(0);
        Node *hh = new Node(0);
        Node *pp = hh;
        Node *rr = h;
        // 新老链表分离 : 老链表重新连在一起，新链表重新连在一起
        while (p)
        {
            Node *q = p->next;
            pp->next = p;
            pp = p;
            pp->next = NULL;
            p = q;
            q = p->next;
            rr->next = p;
            rr = p;
            rr->next = NULL;
            p = q;
        }
        head = hh->next;
        delete hh;
        r = h;
        h = h->next;
        delete r;
        return h;
    }
};