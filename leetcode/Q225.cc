/* Implement Stack using Queues */

class Stack {
public:
    queue<int> q[2];
    int idx = 0;

    // Push element x onto stack.
    void push(int x) {
        q[idx].push(x);
    }

    // Removes the element on top of the stack.
    void pop() {
        while(q[idx].size() > 1) {
            q[1-idx].push(q[idx].front());
            q[idx].pop();
        }
        q[idx].pop();
        idx = 1-idx;
    }

    // Get the top element.
    int top() {
        while(q[idx].size() > 1) {
            q[1-idx].push(q[idx].front());
            q[idx].pop();
        }
        int val = q[idx].front();
        q[1-idx].push(q[idx].front());
        q[idx].pop();
        idx = 1-idx;
        
        return val;
    }

    // Return whether the stack is empty.
    bool empty() {
        return q[idx].empty();
    }
};
