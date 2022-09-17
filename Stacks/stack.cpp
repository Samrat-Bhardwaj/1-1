#include<stack>
#include<string>
#include<vector>

// balanced brackets (leetcode 20)============================================================= 
bool isValid(string s) {
    stack<char> st;

    for(int i=0; i<s.size(); i++){
        if(s[i]=='(' || s[i]=='{' || s[i]=='['){
            st.push(s[i]);
        } else if(s[i]==')'){
            if(st.size()==0 || st.top()!='(') return false;
            st.pop();
        } else if(s[i]=='}'){
            if(st.size()==0 || st.top()!='{') return false;
            st.pop();
        } else {
            if(st.size()==0 || st.top()!='[') return false;
            st.pop();
        }
    }

    return st.size()==0;
}

// if we have only one type of parenthesses ==========================================================

bool isValid(string s){
   int a=0;

   for(int i=0; i<s.size(); i++){
        char c=s[i];
        if(c=='('){
            a++;
        } else {
            a--;
        }

        if(a<0){ // closing brackets are more than opening brackets 
            return false;
        }
   } 

   return a==0;
}

// next greater right 
vector<long long> nextLargerElement(vector<long long> arr, int n){
    vector<long long> ngr(n,0);

    stack<long long> st;

    for(int i=n-1; i>=0; i--){
        long long ele=arr[i];

        while(st.size()!=0 && st.top()<=ele){
            st.pop();
        }

        if(st.size()==0){
            ngr[i]=-1;
        } else {
            ngr[i]=st.top();
        }
        
        st.push(ele);
    }

    return ngr;
}

// next greater on left 
vector<int> ngol(vector<int> arr, int n){
    vector<int> ngl(n,0);

    stack<int> st;

    for(int i=0; i<n; i++){
        int ele=arr[i];

        while(st.size()!=0 && st.top()<=ele){
            st.pop();
        }

        if(st.size()==0){
            ngl[i]=-1;
        } else {
            ngl[i]=st.top();
        }
        
        st.push(ele);
    }

    return ngl;
}

// next smaller on right 
vector<int> nsor(vector<int> arr, int n){
    vector<int> nsr(n,0);

    stack<int> st;

    for(int i=n-1; i>=0; i--){
        int ele=arr[i];

        while(st.size()!=0 && st.top()>=ele){
            st.pop();
        }

        if(st.size()==0){
            nsr[i]=-1;
        } else {
            nsr[i]=st.top();
        }
        
        st.push(ele);
    }

    return nsr;
}


// next smaller on left
vector<int> nsol(vector<int> arr, int n){
    vector<int> nsl(n,0);

    stack<int> st;

    for(int i=0; i<n; i++){
        int ele=arr[i];

        while(st.size()!=0 && st.top()>=ele){
            st.pop();
        }

        if(st.size()==0){
            nsl[i]=-1;
        } else {
            nsl[i]=st.top();
        }
        
        st.push(ele);
    }

    return nsl;
}

// next greater right starting fromn left side ======================= 

vector<int> ngor(vector<int> arr, int n){
    vector<int> ngr(n,-1);
    stack<int> st; // to push indices

    for(int i=0; i<n; i++){
        while(st.size()!=0 && arr[st.top()]<arr[i]){
            ngr[st.top()]=arr[i];
            st.pop();
        }

        st.push(i);
    }

    return ngr;
}

// next greater left starting from right end ================================ 

vector<int> ngof(vector<int> arr, int n){
   vector<int> ngf(n,-1);

   stack<int> st;

   for(int i=n-1; i>=0; i--){
      while(st.size()!=0 && arr[st.top()]<arr[i]){
         ngf[st.top()] = arr[i];
         st.pop();
      }

      st.push(i);
   }

   return ngf;
}


// leetcode 239 ======================================================= 
vector<int> getNextGreater(vector<int> nums){
    int n=nums.size();

    stack<int> st;
    vector<int> ngr(n,n+1);

    for(int i=0; i<n; i++){
        while(st.size()!=0 && nums[st.top()]<nums[i]){
            ngr[st.top()]=i;
            st.pop();
        }

        st.push(i);
    }

    return ngr;
}

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> ngr=getNextGreater(nums);     
    
    int n=nums.size();
    vector<int> ans(n-k+1);

    int cand=0;
    for(int i=0; i<n-k+1; i++){
        if(cand<i){
            cand=i;
        }

        while(ngr[cand]<=i+k-1){
            cand=ngr[cand];
        }

        ans[i]=nums[cand];
    }

    return ans;
}

// leetcode 946 ================================================================
bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
       stack<int> st;
        int i=0;
        
        for(int e:pushed){
            st.push(e);
            
            while(st.size()!=0 && st.top()==popped[i]){
                st.pop();
                i++;
            }
        }
        
        return st.size()==0;
    }

// leet 496 ===============================

// leet 503=======================================================
vector<int> nextGreaterElements(vector<int>& nums) {
    stack<int> st;  
    int n=nums.size();

    vector<int> ans(n,-1);

    for(int i=0; i<2*n; i++){
        while(st.size()!=0 && nums[st.top()]<nums[i%n]){
            ans[st.top()]=nums[i%n];
            st.pop();
        }

        if(i<n)
           st.push(i);
    }      

    return ans;  
}

// leetcode 1021 ============================================================== 
string removeOuterParentheses(string s) {
    string ans="";
    int a=0;
    
    for(int i=0; i<s.size(); i++){
        if(s[i]=='('){
            a++;
            if(a!=1){
                ans+=s[i];
            }
        } else {
            a--;
            if(a!=0){
                ans+=s[i];
            }
        }
    }
    
    return ans;
}

// leetcode 1249 ===============================================================

string minRemoveToMakeValid(string s) {
    stack<int> st;
    
    int n=s.size();
    
    for(int i=0; i<n; i++){
        if(s[i]==')'){
            if(st.size()!=0){ // popping the corresponding opening bracket
                st.pop();
            } else {
                s[i]='$';
            } 
        } else if(s[i]=='('){
            st.push(i);
        }
    }
    
    while(st.size()){
        s[st.top()]='$';
        st.pop();
    }
    
    string ans="";
    for(int i=0; i<n; i++){
        if(s[i]!='$'){
            ans+=s[i];
        }
    }
    
    return ans;
}

// leetcode 32 ============================================

int longestValidParentheses(string s) {
    stack<int> st;
    int ans=0;
    
    st.push(-1);
    for(int i=0; i<s.size(); i++){
        if(s[i]==')' && st.top()!=-1 && s[st.top()]=='('){
            st.pop();
            ans=max(ans,i-st.top());
        } else {
            st.push(i);
        }
    }
    
    return ans;
}

// leet 2116 ============================================

// leet 735 ================================== 
vector<int> asteroidCollision(vector<int>& asteroids) {
    stack<int> st;

    for(int )        
}


// leet 901 ===============================================
class StockSpanner {
public:
    stack<pair<int,int>> st; // price,day
    int day=0;
    StockSpanner() {
        st.push({-1,-1});    
    }
    
    int next(int price) {
        while(st.top().second!=-1 && st.top().first <= price){
            st.pop();
        }
        
        int span = day - st.top().second; 
        st.push({price,day});
        day++;
        
        return span;
    }
};


// leetcode 84 =========================================== 

class Solution {
public:
vector<int> nsor(vector<int> arr, int n){
    vector<int> nsr(n,0);

    stack<int> st;

    for(int i=n-1; i>=0; i--){
        int ele=arr[i];

        while(st.size()!=0 && arr[st.top()]>=ele){
            st.pop();
        }

        if(st.size()==0){
            nsr[i]=n;
        } else {
            nsr[i]=st.top();
        }
        
        st.push(i);
    }

    return nsr;
}
    
vector<int> nsol(vector<int> arr, int n){
    vector<int> nsl(n,0);

    stack<int> st;

    for(int i=0; i<n; i++){
        int ele=arr[i];

        while(st.size()!=0 && arr[st.top()]>=ele){
            st.pop();
        }

        if(st.size()==0){
            nsl[i]=-1;
        } else {
            nsl[i]=st.top();
        }
        
        st.push(i);
    }

    return nsl;
}
    
    int largestRectangleArea(vector<int>& heights) {
        
        vector<int> nsl = nsol(heights,heights.size());
        vector<int> nsr = nsor(heights,heights.size());
        
        int maximum = -(int)1e9;
        for(int i=0; i<heights.size(); i++){
            int area = (nsr[i] - nsl[i] - 1)*heights[i];
            maximum = max(maximum,area);
            
        }
        
        return maximum;
        
    }
};

// leet 84 without using arrays 

int largestRectangleArea(vector<int>& heights) {
    int area=0;
    int n=heights.size();
    stack<int> st;
    st.push(-1);

    for(int i=0; i<n; i++){
        while(st.top()!=-1 && heights[st.top()]>=heights[i]){
            int h=heights[st.top()];
            st.pop();

            int width = i - st.top() - 1;
            area=max(area,h*width);
        }
        st.push(i);
    }

    while(st.top()!=-1){
        int h=heights[st.top()];
        st.pop();

        int w=n-st.top()-1;
        area=max(area,h*w);
    }

    return area;
}

// leetcode 85================================================================

int maximalRectangle(vector<vector<char>>& matrix) {
    int m=matrix[0].size();
    int area=0;

    vector<int> heights(m,0);

    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<m; j++){
            if(matrix[i][j]=='0'){
                heights[j]=0;
            } else {
                heights[j]++;
            }
        }

        area=max(area,largestRectangleArea(heights));
    }        

    return area;
}

// leet 155 ================================================================

class MinStack {
public:
    stack<long> st;
    long mine=0;
    MinStack() {
        
    }
    
    void push(int val) {
        if(st.size()==0){
            mine=(long)val;
            st.push((long)val);
        } else if(val<mine){
            long tp=((long)val-mine)+(long)val; // tp<val;
            st.push(tp);
            
            mine=(long)val;
        } else {
            st.push((long)val);
        }
    }
    
    void pop() {
        if(st.top()<mine){
            long val=mine;
            long tp=st.top();
            
            long old_min= 2*val-tp;
            
            mine=old_min;
        }
        st.pop();
    }
    
    int top() {
        if(st.top()<mine){
            return (int)(mine);
        } else {
            return (int)st.top();
        }
    }
    
    int getMin() {
        return (int)mine;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */


// leet 402 ========================================================================

string removeKdigits(string num, int k) {
        // 14342          k=3
        // 1$3$2
        // 132 -> 1$2
        // 32
        //12
        
        int n=num.size();
        vector<char> st;
        
        for(int i=0; i<n; i++){
            char ch=num[i];
            
            while(st.size()!=0 && k>0 && st.back()>ch){
                st.pop_back();
                k--;
            }
            
            if(st.size()==0 && ch=='0'){
                continue;
            }
            
            st.push_back(ch);
        }
        
        while(st.size()!=0 && k--){
            st.pop_back();
        }
        
        string ans="";
        for(int i=0; i<st.size(); i++){
            ans+=st[i];
        }
        
        return ans.size()==0 ? "0" : ans;
    }

    // leet 316 ========================================================== 
    string removeDuplicateLetters(string s) {
        vector<int> fre(26,0);
        vector<bool> vis(26,false);
        
        for(char c:s){
            fre[c-'a']++;
        }
        
        vector<char> st;
        
        for(char ch:s){
            fre[ch-'a']--;
            
            if(vis[ch-'a']){ // if it is inside my stack
                continue;
            }
            
            while(st.size()!=0 && st.back()>ch && fre[st.back()-'a']>0){
                vis[st.back()-'a']=false;
                st.pop_back();
            }
            
            st.push_back(ch);
            vis[ch-'a']=true;
        }
        
        string ans="";
        for(int i=0; i<st.size(); i++){
            ans+=st[i];
        }
        
        return ans;
    }

    // leet 1541 ========================================= 
    int minInsertions(string s) {
        int a=0;
        int ans=0;
        for(int i=0; i<s.size(); i++){
            if(s[i]=='('){
                a++;
            } else {
                if(i+1<s.size() && s[i+1]==')') i++;
                else ans++;
                
                a--;
            }
            
            if(a<0){
                a=0;
                ans++;
            }
        }
        
        return ans+2*a;
    }

    // leet 42 ============================================================== 
    int trap(vector<int>& height) {
        int n=height.size();
        
        vector<int> left(n,0);
        vector<int> right(n,0);
        
        int msf=0;
        for(int i=0; i<n; i++){
            left[i]=max(msf,height[i]);
            msf=left[i];
        }
        
        msf=0;
        for(int i=n-1; i>=0; i--){
            right[i]=max(msf,height[i]);
            msf=right[i];
        }
        
        int ans=0;
        for(int i=0; i<n; i++){
            int mlr=min(left[i],right[i]);
            
            ans+=(mlr-height[i]);
        }
        
        return ans;
    }

    // solution 2 ===============================================================
     int trap(vector<int>& height) {
        int n=height.size();
        int ans=0;
        
        stack<int> st;
        
        for(int i=0; i<n; i++){
            while(st.size()!=0 && height[st.top()]<=height[i]){
                int h=height[st.top()];
                st.pop();
                
                if(st.size()==0) break;
                
                int w=i-st.top()-1;
                ans+=w*(min(height[i],height[st.top()])-h);
            }
            st.push(i);
        }
        
        return ans;
    }

    // solution 3 =================================
    int trap(vector<int>& height) {
        int n=height.size();
        int ans=0;
        
        int i=0;
        int j=n-1;
        int lmax=0;
        int rmax=0;
        
        while(i<j){
            lmax=max(lmax,height[i]);
            rmax=max(rmax,height[j]);
            
            if(lmax<=rmax){
                ans+=lmax-height[i];
                i++;
            } else {
                ans+=(rmax-height[j]);
                j--;
            }
        }
        
        return ans;
    }

    // leetcode 456 ===================================================================== 
bool find132pattern(vector<int>& nums) {
    int n=nums.size();
    
    vector<int> msf(n); // this will tell me if there is some nums[i]
    stack<int> st; // this will have nums[k]
    msf[0]=nums[0];
    
    for(int i=1; i<n; i++){
        msf[i]=min(msf[i-1],nums[i]);
    }
    
    for(int j=n-1; j>=0; j--){ // jth candidate , msf[j] -> {0,j} minimum = nums[i]
        if(msf[j]<nums[j]){
            while(st.size()!=0 && st.top()<=msf[j]){ // all the k elements should be greater than msf[j]
                st.pop();
            }
            
            if(st.size()!=0 && st.top()<nums[j]){
                return true;
            }
            
            st.push(nums[j]);
        }
    }
    
    return false;
}
int main(){

}