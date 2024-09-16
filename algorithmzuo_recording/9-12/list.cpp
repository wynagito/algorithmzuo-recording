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
    // 反转单链表测试链接 : https://leetcode.cn/problems/reverse-linked-list/
    ListNode *reverseList(ListNode *head)
    {
        ListNode *temp; // 保存cur的下一个节点
        ListNode *cur = head;
        ListNode *pre = nullptr;
        while (cur)
        {
            temp = cur->next; // 保存一下 cur的下一个节点，因为接下来要改变cur->next
            cur->next = pre;  // 翻转操作
            // 更新pre 和 cur指针
            pre = cur;
            cur = temp;
        }
        return pre;
    }

    // 将两个升序链表合并为一个新的 升序 链表并返回
    // 新链表是通过拼接给定的两个链表的所有节点组成的
    // 测试链接 : https://leetcode.cn/problems/merge-two-sorted-lists/
    ListNode *mergeTwoLists(ListNode *head1, ListNode *head2)
    {
        if (head1 == nullptr || head2 == nullptr)
        {
            return head1 == nullptr ? head2 : head1;
        }
        ListNode *head = head1->val <= head2->val ? head1 : head2;
        ListNode *cur1 = head->next;
        ListNode *cur2 = head == head1 ? head2 : head1;
        ListNode *pre = head;
        while (cur1 != nullptr && cur2 != nullptr)
        {
            if (cur1->val <= cur2->val)
            {
                pre->next = cur1;
                cur1 = cur1->next;
            }
            else
            {
                pre->next = cur2;
                cur2 = cur2->next;
            }
            pre = pre->next;
        }
        pre->next = cur1 != nullptr ? cur1 : cur2;
        return head;
    }

    // 给你两个 非空 的链表，表示两个非负的整数
    // 它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字
    // 请你将两个数相加，并以相同形式返回一个表示和的链表。
    // 你可以假设除了数字 0 之外，这两个数都不会以 0 开头
    // 测试链接：https://leetcode.cn/problems/add-two-numbers/
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *dummy = new ListNode(0);
        ListNode *cur = dummy;
        int carry = 0;
        while (l1 || l2 || carry)
        {
            int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
            carry = sum / 10;
            cur->next = new ListNode(sum % 10);
            cur = cur->next;
            if (l1)
                l1 = l1->next;
            if (l2)
                l2 = l2->next;
        }
        return dummy->next;
    }

    // 给你一个链表的头节点 head 和一个特定值 x
    // 请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
    // 你应当 保留 两个分区中每个节点的初始相对位置
    // 测试链接 : https://leetcode.cn/problems/partition-list/
    ListNode *partition(ListNode *head, int x)
    {
        ListNode *dummy1 = new ListNode(0);
        ListNode *dummy2 = new ListNode(0);
        ListNode *cur1 = dummy1;
        ListNode *cur2 = dummy2;
        while (head)
        {
            if (head->val < x)
            {
                cur1->next = head;
                cur1 = cur1->next;
            }
            else
            {
                cur2->next = head;
                cur2 = cur2->next;
            }
            head = head->next;
        }
        cur2->next = nullptr;
        cur1->next = dummy2->next;
        return dummy1->next;
    }
};