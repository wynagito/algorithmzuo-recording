// 链表类题目注意点：
// 1，如果笔试中空间要求不严格，直接使用容器来解决链表问题
// 2，如果笔试中空间要求严格、或者在面试中面试官强调空间的优化，需要使用额外空间复杂度O(1)的方法
// 3，最常用的技巧-快慢指针
// 4，链表类题目往往都是很简单的算法问题，核心考察点也并不是算法设计，是coding能力
// 5，这一类问题除了多写多练没有别的应对方法
// 返回两个无环链表相交的第一个节点
// 测试链接 : https://leetcode.cn/problems/intersection-of-two-linked-lists/

#include <cstddef>
#include <algorithm>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        ListNode *curA = headA;
        ListNode *curB = headB;
        int lenA = 0, lenB = 0;
        while (curA != NULL)
        { // 求链表A的长度
            lenA++;
            curA = curA->next;
        }
        while (curB != NULL)
        { // 求链表B的长度
            lenB++;
            curB = curB->next;
        }
        curA = headA;
        curB = headB;
        // 让curA为最长链表的头，lenA为其长度
        if (lenB > lenA)
        {
            swap(lenA, lenB);
            swap(curA, curB);
        }
        // 求长度差
        int gap = lenA - lenB;
        // 让curA和curB在同一起点上（末尾位置对齐）
        while (gap--)
        {
            curA = curA->next;
        }
        // 遍历curA 和 curB，遇到相同则直接返回
        while (curA != NULL)
        {
            if (curA == curB)
            {
                return curA;
            }
            curA = curA->next;
            curB = curB->next;
        }
        return NULL;
    }
};