#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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

const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string CYAN = "\033[36m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string YELLOW = "\033[33m";

ListNode *buildList(const vector<int> &nums)
{
    ListNode *dummy = new ListNode(0);
    ListNode *tail = dummy;
    for (int x : nums)
    {
        tail->next = new ListNode(x);
        tail = tail->next;
    }
    ListNode *head = dummy->next;
    delete dummy;
    return head;
}

vector<int> listToVector(ListNode *head)
{
    vector<int> ans;
    while (head)
    {
        ans.push_back(head->val);
        head = head->next;
    }
    return ans;
}

void freeList(ListNode *head)
{
    while (head)
    {
        ListNode *next = head->next;
        delete head;
        head = next;
    }
}

void printVector(const vector<int> &nums)
{
    cout << "[";
    for (int i = 0; i < (int)nums.size(); i++)
    {
        cout << nums[i] << (i + 1 == (int)nums.size() ? "" : ", ");
    }
    cout << "]";
}

bool equalVector(const vector<int> &a, const vector<int> &b)
{
    if (a.size() != b.size())
    {
        return false;
    }
    for (int i = 0; i < (int)a.size(); i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}

bool runReverseCase(const string &name, const vector<int> &in, const vector<int> &expect)
{
    ListNode *head = buildList(in);
    ListNode *outHead = reverseList(head);
    vector<int> out = listToVector(outHead);
    bool ok = equalVector(out, expect);

    cout << "\n"
         << CYAN << BOLD << "[reverseList] " << name << RESET << "\n";
    cout << "输入: ";
    printVector(in);
    cout << "\n输出: ";
    printVector(out);
    cout << "\n期望: ";
    printVector(expect);
    cout << "\n结果: " << (ok ? (GREEN + string("PASS") + RESET) : (RED + string("FAIL") + RESET)) << "\n";

    freeList(outHead);
    return ok;
}

bool runMergeCase(const string &name, const vector<int> &a, const vector<int> &b, const vector<int> &expect)
{
    ListNode *h1 = buildList(a);
    ListNode *h2 = buildList(b);
    ListNode *outHead = mergeTwoLists(h1, h2);
    vector<int> out = listToVector(outHead);
    bool ok = equalVector(out, expect);

    cout << "\n"
         << CYAN << BOLD << "[mergeTwoLists] " << name << RESET << "\n";
    cout << "链表1: ";
    printVector(a);
    cout << "\n链表2: ";
    printVector(b);
    cout << "\n输出: ";
    printVector(out);
    cout << "\n期望: ";
    printVector(expect);
    cout << "\n结果: " << (ok ? (GREEN + string("PASS") + RESET) : (RED + string("FAIL") + RESET)) << "\n";

    freeList(outHead);
    return ok;
}

bool runAddCase(const string &name, const vector<int> &a, const vector<int> &b, const vector<int> &expect)
{
    ListNode *h1 = buildList(a);
    ListNode *h2 = buildList(b);
    ListNode *outHead = addTwoNumbers(h1, h2);
    vector<int> out = listToVector(outHead);
    bool ok = equalVector(out, expect);

    cout << "\n"
         << CYAN << BOLD << "[addTwoNumbers] " << name << RESET << "\n";
    cout << "数字1(逆序): ";
    printVector(a);
    cout << "\n数字2(逆序): ";
    printVector(b);
    cout << "\n输出(逆序): ";
    printVector(out);
    cout << "\n期望(逆序): ";
    printVector(expect);
    cout << "\n结果: " << (ok ? (GREEN + string("PASS") + RESET) : (RED + string("FAIL") + RESET)) << "\n";

    freeList(h1);
    freeList(h2);
    freeList(outHead);
    return ok;
}

bool runPartitionCase(const string &name, const vector<int> &in, int x, const vector<int> &expect)
{
    ListNode *head = buildList(in);
    ListNode *outHead = partition(head, x);
    vector<int> out = listToVector(outHead);
    bool ok = equalVector(out, expect);

    cout << "\n"
         << CYAN << BOLD << "[partition] " << name << RESET << "\n";
    cout << "输入: ";
    printVector(in);
    cout << "\nx = " << x;
    cout << "\n输出: ";
    printVector(out);
    cout << "\n期望: ";
    printVector(expect);
    cout << "\n结果: " << (ok ? (GREEN + string("PASS") + RESET) : (RED + string("FAIL") + RESET)) << "\n";

    freeList(outHead);
    return ok;
}

int main()
{
    int total = 0;
    int pass = 0;

    cout << BOLD << YELLOW << "===== 链表算法测试开始 =====" << RESET << "\n";

    total++;
    pass += runReverseCase("基础反转", {1, 2, 3, 4, 5}, {5, 4, 3, 2, 1}) ? 1 : 0;
    total++;
    pass += runReverseCase("单节点", {7}, {7}) ? 1 : 0;

    total++;
    pass += runMergeCase("交错合并", {1, 2, 4}, {1, 3, 4}, {1, 1, 2, 3, 4, 4}) ? 1 : 0;
    total++;
    pass += runMergeCase("一条空链表", {}, {0}, {0}) ? 1 : 0;

    total++;
    pass += runAddCase("无进位", {2, 4, 3}, {5, 6, 4}, {7, 0, 8}) ? 1 : 0;
    total++;
    pass += runAddCase("长进位", {9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9}, {8, 9, 9, 9, 0, 0, 0, 1}) ? 1 : 0;

    total++;
    pass += runPartitionCase("典型用例", {1, 4, 3, 2, 5, 2}, 3, {1, 2, 2, 4, 3, 5}) ? 1 : 0;
    total++;
    pass += runPartitionCase("全部小于x", {1, 1, 1}, 5, {1, 1, 1}) ? 1 : 0;

    int fail = total - pass;

    cout << "\n"
         << BOLD << YELLOW << "===== 测试汇总 =====" << RESET << "\n";
    cout << "总用例数: " << total << "\n";
    cout << GREEN << "通过数: " << pass << RESET << "\n";
    cout << (fail == 0 ? GREEN : RED) << "失败数: " << fail << RESET << "\n";
    cout << "通过率: " << (pass * 100 / total) << "%\n";

    cout << "\n"
         << BOLD << YELLOW << "===== 链表算法测试结束 =====" << RESET << "\n";
    return fail == 0 ? 0 : 1;
}