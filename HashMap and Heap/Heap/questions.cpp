#include<vector>
#include<priority_queue>

// leet 215 ================================================
int findKthLargest(vector<int>& nums, int k) {
    // nlog(k);
    priority_queue<int,vector<int>,greater<int>> pq;
    
    for(int e:nums){
        pq.push(e);
        
        if(pq.size()>k){
            pq.pop();
        }
    }
    
    return pq.top();
}

// leetcode 350 =======================================
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int> map;
        
        vector<int> ans;
        for(int e:nums1){
            map[e]++;
        }
        
        
        for(int e:nums2){
            if(map.find(e)!=map.end()){
                ans.push_back(e);
                
                map[e]--;
                if(map[e]==0){
                    map.erase(e);
                }
            }
        }
        
        return ans;
    }

// leetcode 128 =================================== 
int longestConsecutive(vector<int>& nums) {
    unordered_map<int,int> map;
    
    for(int e:nums){
        map[e]++;
    }
    
    int ans=0;
    for(int e:nums){
        if(map.find(e)==map.end()) continue;
        
        int prev=e-1;
        int next=e+1;
        
        while(map.find(prev)!=map.end()){
            map.erase(prev);
            prev--;
        }
        
        while(map.find(next)!=map.end()){
            map.erase(next);
            next++;
        }
        
        int len = next - prev - 1;
        ans=max(ans,len);
    }
    
    return ans;
}

// leetcode 703 ==============================================

class KthLargest {
public:
    int k;
    priority_queue<int,vector<int>,greater<int>> pq;
    KthLargest(int k, vector<int>& nums) {
        this->k=k;
        
        for(int e:nums){
            pq.push(e);
            
            if(pq.size()>k){
                pq.pop();
            }
        }
    }
    
    int add(int val) {
        pq.push(val);
        
        if(pq.size()>k){
            pq.pop();
        }
        
        return pq.top();
    }
    // 10,9,8,5,5,4,4,3,2
};

// leet 692 ========================================================================================== 

public List<String> topKFrequent(String[] words, int k) {
    HashMap<String,Integer> map=new HashMap<>();
    
    for(String s:words){
        map.put(s,map.getOrDefault(s,0)+1);
    }
    
    PriorityQueue<String> pq=new PriorityQueue<>((a,b)->{
        if(map.get(a)==map.get(b)){
            return b.compareTo(a); // lexiographical greater string top (b-a) (max)
        }
        
        return map.get(a) - map.get(b); // smaller fre (a-b)(min)
    });
    
    // if 0th index smaller, it should be on top
    // if 0th index equal, array with 1st index greater should be on top
//         PriorityQueue<int[]> pq=new PriorityQueue<>((a,b)->{
//            if(a[0]==b[0]){
//                return b[1] - a[1];
//            } 
        
//             return a[0] - b[0]; 
//         });
    
    // a-b => default behaviour = min pq
    // b-a => opp of defualt = max pq
    
    for(String s:map.keySet()){
        pq.add(s);
        
        if(pq.size()>k){
            pq.remove();
        }
    }
    
    List<String> ans=new ArrayList<>();
    
    while(pq.size()>0){
        ans.add(pq.remove());
    }
    
    Collections.reverse(ans);
    return ans;
}

vector<string> topKFrequent(vector<string>& words, int k) {    
    unordered_map<string,int> m;
    for(string s:words){
        m[s]++;
    }
    
    auto comp = [&](const pair<string,int>& a, const pair<string,int>& b) {
        return a.second > b.second || (a.second == b.second && a.first < b.first);
    };
    
    typedef priority_queue< pair<string,int>, vector<pair<string,int>>, decltype(comp) > my_priority_queue_t;
    my_priority_queue_t  pq(comp);
    
    for(auto it:m){
        pq.push(it);
        
        if(pq.size()>k){
            pq.pop();
        }
    }
    
    vector<string> ans;
    
    while(pq.size()){
        ans.push_back(pq.top().first);
        pq.pop();
    }
    
    reverse(ans.begin(),ans.end());
    
    return ans;
}


// leet 347 ========================================== 

// leet 295 =============================================
class MedianFinder {
public:
    priority_queue<int> left; // max pq
    priority_queue<int,vector<int>,greater<int>> right; // min pq
    
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(left.size()==0 || left.top()>=num) left.push(num);
        else right.push(num);
        
        int ls=left.size();
        int rs=right.size();
        
        if(ls - rs > 1){
            right.push(left.top());
            left.pop();
        } else if(rs > ls){
            left.push(right.top());
            right.pop();
        }
    }
    
    double findMedian() {
        if(left.size()==right.size()){
            return (left.top() + right.top())/(2.0);
        } else {
            return left.top();
        }
    }
};

// Question ->  why we should not use .size in c++
// ans -> https://stackoverflow.com/questions/52906628/vector-size-is-working-unexpectedly-in-comparision

// leet 378 =================================================================================
int kthSmallest(vector<vector<int>>& matrix, int k) {
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    
    int n=matrix.size();
    int m=matrix[0].size();
    
    for(int i=0; i<n; i++){
        pq.push({matrix[i][0],i*m+0});
    }
    
    while(k-- > 1){
        pair<int,int> p=pq.top();
        pq.pop();
        
        int idx=p.second;
        
        int r=idx/m;
        int c=idx%m;
        
        if(c+1<m)
            pq.push({matrix[r][c+1],r*m+c+1});
    }
    
    return pq.top().first;
}

// leet 895 ============================================================== 

class FreqStack {
public:
    unordered_map<int,int> fre;
    unordered_map<int, stack<int>> stacks;
    int maxFre=0;
    
    FreqStack() {
        
    }
    
    void push(int val) {
        fre[val]++;
        
        maxFre=max(maxFre,fre[val]);
        stacks[fre[val]].push(val);
    }
    
    int pop() {
        int rv=stacks[maxFre].top();
        stacks[maxFre].pop();
        
        if(stacks[maxFre].size()==0) maxFre--;
        fre[rv]--;
        
        // if(fre[rv]==0) fre.erase(rv);
        
        return rv;
    }
};
int main(){

}