#include <stack>
#include <queue>

using namespace std;

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