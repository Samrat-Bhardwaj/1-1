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


int main(){

}