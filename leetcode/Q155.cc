/* Min Stack */

class MinStack {
public:
    void push(int x) {
        s1.push(x);
        
        if(s2.empty()) {
            s2.push(x);
        } else {
           int tmp = s2.top();
           s2.push(tmp<=x?tmp:x);
        }
    }

    void pop() {
        s1.pop();
        s2.pop();
    }

    int top() {
        return s1.top();
    }

    int getMin() {
        return s2.top();
    }
    
private:
    stack<int> s1;
    stack<int> s2;
};
