/* Valid Anagram */

class Solution {
public:
    bool isAnagram(string s, string t) {
        int l1 = s.size();
        int l2 = t.size();
        if(l1 != l2)
            return false;
        int h1[26];
        int h2[26];
        for(int i=0; i<26; i++) {
            h1[i] = 0;
            h2[i] = 0;
        }
        
        for(int i=0; i<l1; i++) {
            h1[s[i]-'a']++;
            h2[t[i]-'a']++;
        }
        
        for(int i=0; i<26; i++) {
            if(h1[i] != h2[i])
                return false;
        }
        
        return true;
    }
};
