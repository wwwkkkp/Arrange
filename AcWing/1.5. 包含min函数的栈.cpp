//5.41. 包含min函数的栈 

/*
设计一个支持push，pop，top等操作并且可以在O(1)时间内检索出最小元素的堆栈。
push(x)–将元素x插入栈中
pop()–移除栈顶元素
top()–得到栈顶元素
getMin()–得到栈中最小元素
样例
MinStack minStack = new MinStack();
minStack.push(-1);
minStack.push(3);
minStack.push(-4);
minStack.getMin();   --> Returns -4.
minStack.pop();
minStack.top();      --> Returns 3.
minStack.getMin();   --> Returns -1.
*/

class MinStack {
public:
    /** initialize your data structure here. */
    
    stack<int>s,sin;  //精髓就是设计一个栈用于存放到目前为止最小的数，比如s:[-1,3,-4],sin:[-1,-1,-4]
    
    MinStack() {
        
    }
    
    void push(int x) {
        s.push(x);
        if(sin.size())  sin.push(min(sin.top(),x));
        else sin.push(x);
    }
    
    void pop() {
        s.pop();
        sin.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return sin.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */