/* Reverse Words in a String */

class Solution {
public:
    void reverseWords(string &s) 
        int size = s.size();
            
        string vs;
        for(int i=0; i<size; i++) {
            if(i!=0 && s[i]==' ' && s[i-1]==' ')
                continue;
            if((i==0||i==size-1) && s[i]==' ')
                continue;
            vs.push_back(s[i]);
        }
        
        size = vs.size();
        if(size == 0) {
            s = vs;
            return;
        }
        
        if(vs[size-1] == ' ') {
            vs.resize(size-1);
            size--;
        }
            
        int mid = (size-1)/2;
        for(int i=0; i<=mid; i++) {
            char tmp = vs[i];
            vs[i] = vs[size-1-i];
            vs[size-1-i] = tmp;
        }
        
        int start = 0;
        for(int i=0; i<=size; i++) {
            if(i==size || vs[i] == ' ') {
                reverseWord(vs, start, i-1);
                start = i+1;
            }
        }
        
        s = vs;
        return;
    }
    
    void reverseWord(string& vs, int p, int q) {
        int size = q-p+1;
        int mid = (size-1)/2;
        for(int i=0; i<=mid; i++) {
            char tmp = vs[i+p];
            vs[i+p] = vs[size-1-i+p];
            vs[size-1-i+p] = tmp;
        }
    }
};
