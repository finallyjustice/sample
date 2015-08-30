/* Valid Parentheses */

class Solution {
public:
    bool isValid(string s) {
        int n = s.size();
        const char *str = s.c_str();
        stack<char> st;
        
        if(n % 2 == 1)
            return false;
        if(n == 0)
            return true;
        
        for(int i=0; i<n; i++)
        {
            if(str[i]=='(' || str[i]=='{' || str[i]=='[')
            {
                st.push(str[i]);
            }
            else
            {
                if(st.empty())
                    return false;
                    
                if(str[i]==')' && st.top()=='(')
                    st.pop();
                else if(str[i]==']' && st.top()=='[')
                    st.pop();
                else if(str[i]=='}' && st.top()=='{')
                    st.pop();
                else
                    return false;
            }
        }
        
        if(!st.empty())
            return false;
            
        return true;
    }
};
