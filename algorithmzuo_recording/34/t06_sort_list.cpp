// 排序链表
// 要求时间复杂度O(n*logn)，额外空间复杂度O(1)，还要求稳定性
// 数组排序做不到，链表排序可以
// 测试链接 : https://leetcode.cn/problems/sort-list/

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    // 时间复杂度O(n*logn)，额外空间复杂度O(1)，有稳定性
    // 注意为了额外空间复杂度O(1)，所以不能使用递归
    // 因为mergeSort递归需要O(log n)的额外空间
    ListNode *sortList(ListNode *head)
    {
        int n = 0;
        ListNode *cur = head;
        while (cur != nullptr)
        {
            n++;
            cur = cur->next;
        }
        // l1...r1 每组的左部分
        // l2...r2 每组的右部分
        // next 下一组的开头
        // lastTeamEnd 上一组的结尾
        ListNode *l1, *r1, *l2, *r2, *next, *lastTeamEnd;
        for (int step = 1; step < n; step <<= 1)
        {
            // 第一组很特殊，因为要决定整个链表的头，所以单独处理
            l1 = head;
            r1 = findEnd(l1, step);
            l2 = r1->next;
            r2 = findEnd(l2, step);
            next = r2->next;
            r1->next = nullptr;
            r2->next = nullptr;
            merge(l1, r1, l2, r2);
            head = start;
            lastTeamEnd = end;
            while (next != nullptr)
            {
                l1 = next;
                r1 = findEnd(l1, step);
                l2 = r1->next;
                if (l2 == nullptr)
                {
                    lastTeamEnd->next = l1;
                    break;
                }
                r2 = findEnd(l2, step);
                next = r2->next;
                r1->next = nullptr;
                r2->next = nullptr;
                merge(l1, r1, l2, r2);
                lastTeamEnd->next = start;
                lastTeamEnd = end;
            }
        }
        return head;
    }

    // 包括s在内，往下数k个节点返回
    // 如果不够，返回最后一个数到的非空节点
    ListNode *findEnd(ListNode *s, int k)
    {
        while (s->next != nullptr && --k != 0)
        {
            s = s->next;
        }
        return s;
    }

    ListNode *start, *end; // 全局变量，记录整体的头和尾

    // l1...r1 -> null : 有序的左部分
    // l2...r2 -> null : 有序的右部分
    // 整体merge在一起，保证有序
    // 并且把全局变量start设置为整体的头，全局变量end设置为整体的尾
    void merge(ListNode *l1, ListNode *r1, ListNode *l2, ListNode *r2)
    {
        ListNode *pre;
        if (l1->val <= l2->val)
        {
            start = l1;
            pre = l1;
            l1 = l1->next;
        }
        else
        {
            start = l2;
            pre = l2;
            l2 = l2->next;
        }
        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val <= l2->val)
            {
                pre->next = l1;
                pre = l1;
                l1 = l1->next;
            }
            else
            {
                pre->next = l2;
                pre = l2;
                l2 = l2->next;
            }
        }
        if (l1 != nullptr)
        {
            pre->next = l1;
            end = r1;
        }
        else
        {
            pre->next = l2;
            end = r2;
        }
    }
};