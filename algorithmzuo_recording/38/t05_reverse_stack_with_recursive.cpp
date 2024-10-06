#include <iostream>
#include <stack>

using namespace std;

int bottomOut(stack<int> &stack);

// 用递归函数逆序栈
// 栈底->栈顶
// a b c
// b c  num=a
// c   num=b
// num=c
// c num=b
// c b num=a
// c b a
void reverse(stack<int> &stack)
{
    if (stack.empty())
    {
        return;
    }
    int num = bottomOut(stack);
    reverse(stack);
    stack.push(num);
}

// 栈底元素移除掉，上面的元素盖下来
// 返回移除掉的栈底元素
// 栈底->栈顶
// a b c
// b c  return a
int bottomOut(stack<int> &stack)
{
    int ans = stack.top();
    stack.pop();
    if (stack.empty())
    {
        return ans;
    }
    else
    {
        int last = bottomOut(stack);
        stack.push(ans);
        return last;
    }
}

int main()
{
    stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    reverse(stack);
    while (!stack.empty())
    {
        cout << stack.top() << endl;
        stack.pop();
    }
    return 0;
}
