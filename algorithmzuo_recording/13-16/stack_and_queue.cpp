#include <stack>
#include <queue>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string CYAN = "\033[36m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string YELLOW = "\033[33m";

// 设计循环队列
// 测试链接 : https://leetcode.cn/problems/design-circular-queue/
class MyCircularQueue
{
public:
    int *queue;
    int len, head, tail;
    MyCircularQueue(int k)
    {
        queue = new int[k + 1];
        len = k + 1;
        head = tail = 0;
    }

    bool enQueue(int value)
    {
        if (isFull())
            return false;
        queue[tail] = value;
        tail = (tail + 1) % len;
        return true;
    }

    bool deQueue()
    {
        if (isEmpty())
            return false;
        head = (head + 1) % len;
        return true;
    }

    int Front()
    {
        if (isEmpty())
            return -1;
        return queue[head];
    }

    int Rear()
    {
        if (isEmpty())
            return -1;
        int count = (tail - head + len) % len;
        return queue[(head + count - 1) % len];
    }

    bool isEmpty()
    {
        return head == tail;
    }

    bool isFull()
    {
        return (tail + 1) % len == head;
    }
};

// 用栈实现队列
// 测试链接 : https://leetcode.cn/problems/implement-queue-using-stacks/
class MyQueue
{
public:
    stack<int> stIn;
    stack<int> stOut;
    /** Initialize your data structure here. */
    MyQueue()
    {
    }
    /** Push element x to the back of queue. */
    void push(int x)
    {
        stIn.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop()
    {
        // 只有当stOut为空的时候，再从stIn里导入数据（导入stIn全部数据）
        if (stOut.empty())
        {
            // 从stIn导入数据直到stIn为空
            while (!stIn.empty())
            {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        stOut.pop();
        return result;
    }

    /** Get the front element. */
    int peek()
    {
        int res = this->pop(); // 直接使用已有的pop函数
        stOut.push(res);       // 因为pop函数弹出了元素res，所以再添加回去
        return res;
    }

    /** Returns whether the queue is empty. */
    bool empty()
    {
        return stIn.empty() && stOut.empty();
    }
};

// 用队列实现栈
// 测试链接 : https://leetcode.cn/problems/implement-stack-using-queues/
class MyStack
{
public:
    queue<int> que1;
    queue<int> que2; // 辅助队列，用来备份
    /** Initialize your data structure here. */
    MyStack()
    {
    }

    /** Push element x onto stack. */
    void push(int x)
    {
        que1.push(x);
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop()
    {
        int size = que1.size();
        size--;
        while (size--)
        { // 将que1 导入que2，但要留下最后一个元素
            que2.push(que1.front());
            que1.pop();
        }

        int result = que1.front(); // 留下的最后一个元素就是要返回的值
        que1.pop();
        que1 = que2; // 再将que2赋值给que1
        while (!que2.empty())
        { // 清空que2
            que2.pop();
        }
        return result;
    }

    /** Get the top element. */
    int top()
    {
        return que1.back();
    }

    /** Returns whether the stack is empty. */
    bool empty()
    {
        return que1.empty();
    }
};

// 最小栈
// 测试链接 : https://leetcode.cn/problems/min-stack/
class MinStack
{
public:
    stack<int> s, m;
    MinStack()
    {
    }

    void push(int val)
    {
        s.push(val);
        if (m.empty())
            m.push(val);
        else
        {
            m.push(min(m.top(), val));
        }
    }

    void pop()
    {
        s.pop();
        m.pop();
    }

    int top()
    {
        return s.top();
    }

    int getMin()
    {
        return m.top();
    }
};

// 设计循环双端队列
// 测试链接 : https://leetcode.cn/problems/design-circular-deque/
class MyCircularDeque
{
public:
    int f, r, size, limit;
    int arr[1000];
    MyCircularDeque(int k)
    {
        size = 0;
        limit = k;
        f = 0;
        r = 0;
    }

    bool insertFront(int value)
    {
        if (isFull())
            return false;
        if (isEmpty())
        {
            f = r = 0;
            arr[f] = value;
        }
        else
        {
            f = (f - 1 + limit) % limit;
            arr[f] = value;
        }
        size++;
        return true;
    }

    bool insertLast(int value)
    {
        if (isFull())
            return false;
        if (isEmpty())
        {
            f = r = 0;
            arr[r] = value;
        }
        else
        {
            r = (r + 1) % limit;
            arr[r] = value;
        }
        size++;
        return true;
    }

    bool deleteFront()
    {
        if (isEmpty())
            return false;
        f = (f + 1) % limit;
        size--;
        return true;
    }

    bool deleteLast()
    {
        if (isEmpty())
            return false;
        r = r == 0 ? limit - 1 : r - 1;
        size--;
        return true;
    }

    int getFront()
    {
        if (isEmpty())
            return -1;
        return arr[f];
    }

    int getRear()
    {
        if (isEmpty())
            return -1;
        return arr[r];
    }

    bool isEmpty()
    {
        return !size;
    }

    bool isFull()
    {
        return size == limit;
    }
};

bool printCaseResult(const string &module, const string &caseName, bool ok, const string &detail)
{
    cout << "\n"
         << CYAN << BOLD << "[" << module << "] " << caseName << RESET << "\n";
    cout << detail << "\n";
    cout << "结果: " << (ok ? (GREEN + string("PASS") + RESET) : (RED + string("FAIL") + RESET)) << "\n";
    return ok;
}

bool expectBool(bool actual, bool expected, const string &label, bool &ok, string &d, string &firstFail)
{
    bool pass = (actual == expected);
    d += BOLD + label + RESET + " | " +
         CYAN + string("actual") + RESET + "=" + string(actual ? "true" : "false") + ", " +
         YELLOW + string("expected") + RESET + "=" + string(expected ? "true" : "false") + " | " +
         (pass ? (GREEN + string("PASS") + RESET) : (RED + string("FAIL") + RESET)) + "\n";
    if (!pass)
    {
        ok = false;
        if (firstFail.empty())
        {
            firstFail = label + " 期望=" + (expected ? string("true") : string("false")) + "，实际=" +
                        (actual ? string("true") : string("false"));
        }
    }
    return pass;
}

bool expectInt(int actual, int expected, const string &label, bool &ok, string &d, string &firstFail)
{
    bool pass = (actual == expected);
    d += BOLD + label + RESET + " | " +
         CYAN + string("actual") + RESET + "=" + to_string(actual) + ", " +
         YELLOW + string("expected") + RESET + "=" + to_string(expected) + " | " +
         (pass ? (GREEN + string("PASS") + RESET) : (RED + string("FAIL") + RESET)) + "\n";
    if (!pass)
    {
        ok = false;
        if (firstFail.empty())
        {
            firstFail = label + " 期望=" + to_string(expected) + "，实际=" + to_string(actual);
        }
    }
    return pass;
}

bool testMyCircularQueue()
{
    MyCircularQueue q(3);
    bool ok = true;
    string firstFail;
    string d;
    d += "容量=3\n";
    expectBool(q.enQueue(1), true, "步骤1 enQueue(1)", ok, d, firstFail);
    expectBool(q.enQueue(2), true, "步骤2 enQueue(2)", ok, d, firstFail);
    expectBool(q.enQueue(3), true, "步骤3 enQueue(3)", ok, d, firstFail);
    bool enqueue4 = q.enQueue(4);
    expectBool(enqueue4, false, "步骤4 enQueue(4)", ok, d, firstFail);
    expectInt(q.Front(), 1, "步骤5 Front()", ok, d, firstFail);
    expectInt(q.Rear(), 3, "步骤6 Rear()", ok, d, firstFail);
    bool deq = q.deQueue();
    bool enq4After = q.enQueue(4);
    expectBool(deq, true, "步骤7 deQueue()", ok, d, firstFail);
    expectBool(enq4After, true, "步骤8 enQueue(4)", ok, d, firstFail);
    expectInt(q.Front(), 2, "步骤9 Front()", ok, d, firstFail);
    expectInt(q.Rear(), 4, "步骤10 Rear()", ok, d, firstFail);

    if (!ok)
    {
        d += RED + string("首个失败点: ") + firstFail + RESET + "\n";
    }
    return printCaseResult("MyCircularQueue", "循环队列基础流程", ok, d);
}

bool testMyQueue()
{
    MyQueue q;
    bool ok = true;
    string firstFail;
    string d;
    q.push(10);
    q.push(20);
    q.push(30);
    int p1 = q.peek();
    int pop1 = q.pop();
    bool e1 = q.empty();
    int pop2 = q.pop();
    int pop3 = q.pop();
    bool e2 = q.empty();

    d += "push: 10,20,30\n";
    expectInt(p1, 10, "步骤1 peek()", ok, d, firstFail);
    expectInt(pop1, 10, "步骤2 pop()", ok, d, firstFail);
    expectBool(e1, false, "步骤3 empty()", ok, d, firstFail);
    expectInt(pop2, 20, "步骤4 pop()", ok, d, firstFail);
    expectInt(pop3, 30, "步骤5 pop()", ok, d, firstFail);
    expectBool(e2, true, "步骤6 empty()", ok, d, firstFail);

    if (!ok)
    {
        d += RED + string("首个失败点: ") + firstFail + RESET + "\n";
    }
    return printCaseResult("MyQueue", "双栈实现队列", ok, d);
}

bool testMyStack()
{
    MyStack st;
    bool ok = true;
    string firstFail;
    string d;
    st.push(1);
    st.push(2);
    st.push(3);
    int t1 = st.top();
    int p1 = st.pop();
    int p2 = st.pop();
    int t2 = st.top();
    bool e1 = st.empty();
    int p3 = st.pop();
    bool e2 = st.empty();

    d += "push: 1,2,3\n";
    expectInt(t1, 3, "步骤1 top()", ok, d, firstFail);
    expectInt(p1, 3, "步骤2 pop()", ok, d, firstFail);
    expectInt(p2, 2, "步骤3 pop()", ok, d, firstFail);
    expectInt(t2, 1, "步骤4 top()", ok, d, firstFail);
    expectBool(e1, false, "步骤5 empty()", ok, d, firstFail);
    expectInt(p3, 1, "步骤6 pop()", ok, d, firstFail);
    expectBool(e2, true, "步骤7 empty()", ok, d, firstFail);

    if (!ok)
    {
        d += RED + string("首个失败点: ") + firstFail + RESET + "\n";
    }
    return printCaseResult("MyStack", "双队列实现栈", ok, d);
}

bool testMinStack()
{
    MinStack st;
    bool ok = true;
    string firstFail;
    string d;
    st.push(-2);
    st.push(0);
    st.push(-3);
    int m1 = st.getMin();
    st.pop();
    int t1 = st.top();
    int m2 = st.getMin();

    d += "push: -2,0,-3\n";
    expectInt(m1, -3, "步骤1 getMin()", ok, d, firstFail);
    d += "步骤2 pop() 执行完成\n";
    expectInt(t1, 0, "步骤3 top()", ok, d, firstFail);
    expectInt(m2, -2, "步骤4 getMin()", ok, d, firstFail);

    if (!ok)
    {
        d += RED + string("首个失败点: ") + firstFail + RESET + "\n";
    }
    return printCaseResult("MinStack", "最小栈流程", ok, d);
}

bool testMyCircularDeque()
{
    MyCircularDeque dq(3);
    bool ok = true;
    string firstFail;
    string d;
    bool i1 = dq.insertLast(1);
    bool i2 = dq.insertLast(2);
    bool i3 = dq.insertFront(3);
    bool i4 = dq.insertFront(4);
    int rear1 = dq.getRear();
    bool full1 = dq.isFull();
    bool del1 = dq.deleteLast();
    bool i5 = dq.insertFront(4);
    int front1 = dq.getFront();

    expectBool(i1, true, "步骤1 insertLast(1)", ok, d, firstFail);
    expectBool(i2, true, "步骤2 insertLast(2)", ok, d, firstFail);
    expectBool(i3, true, "步骤3 insertFront(3)", ok, d, firstFail);
    expectBool(i4, false, "步骤4 insertFront(4)", ok, d, firstFail);
    expectInt(rear1, 2, "步骤5 getRear()", ok, d, firstFail);
    expectBool(full1, true, "步骤6 isFull()", ok, d, firstFail);
    expectBool(del1, true, "步骤7 deleteLast()", ok, d, firstFail);
    expectBool(i5, true, "步骤8 insertFront(4)", ok, d, firstFail);
    expectInt(front1, 4, "步骤9 getFront()", ok, d, firstFail);

    if (!ok)
    {
        d += RED + string("首个失败点: ") + firstFail + RESET + "\n";
    }
    return printCaseResult("MyCircularDeque", "循环双端队列流程", ok, d);
}

int main()
{
    int total = 0;
    int pass = 0;

    cout << BOLD << YELLOW << "===== 栈与队列模块测试开始 =====" << RESET << "\n";

    total++;
    pass += testMyCircularQueue() ? 1 : 0;
    total++;
    pass += testMyQueue() ? 1 : 0;
    total++;
    pass += testMyStack() ? 1 : 0;
    total++;
    pass += testMinStack() ? 1 : 0;
    total++;
    pass += testMyCircularDeque() ? 1 : 0;

    int fail = total - pass;
    cout << "\n"
         << BOLD << YELLOW << "===== 测试汇总 =====" << RESET << "\n";
    cout << "总用例数: " << total << "\n";
    cout << GREEN << "通过数: " << pass << RESET << "\n";
    cout << (fail == 0 ? GREEN : RED) << "失败数: " << fail << RESET << "\n";
    cout << "通过率: " << (pass * 100 / total) << "%\n";

    cout << "\n"
         << BOLD << YELLOW << "===== 栈与队列模块测试结束 =====" << RESET << "\n";
    return fail == 0 ? 0 : 1;
}