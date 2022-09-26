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

// LRU Cache (leet 146) =========================================================================== 

class LRUCache {
public:
    class Node {
        public:
            int key;
            int val;
            Node* prev;
            Node* next;
        
            Node(int key, int val){
                this->key=key;
                this->val=val;
                prev=nullptr;
                next=nullptr;
            }
    };
    
    Node* head;
    Node* tail;
    int size;
    
    void addLast(Node* node){
        if(head==NULL){
            head=tail=node;
        } else {
            node->prev=tail;
            tail->next=node;
            
            tail=node;
        }
        
        size++;
    }
    
    Node* removeHead(){
        Node* headKaNext=head->next;
        
        head->next=nullptr;
        
        if(headKaNext!=nullptr)
            headKaNext->prev=nullptr;
        
        Node* tr=head;
        head=headKaNext;
        
        size--;
        return tr;
    }
    
    void removeNode(Node* node){
        if(node==head){
            removeHead();
        } else if(node==tail){
            Node* tailKaPrev=tail->prev;
            tail->prev=nullptr;
            
            tail=tailKaPrev;
            tail->next=nullptr;
            size--;
        } else {
            Node* nodeKaPrev=node->prev;
            Node* nodeKaNext=node->next;
            
            nodeKaPrev->next=nodeKaNext;
            nodeKaNext->prev=nodeKaPrev;
            size--;
        }
    }
    
    map<int,Node*> map; // key vs node (val)
    int maxSize;
    
    LRUCache(int capacity) {
        head=nullptr;
        tail=nullptr;
        size=0;
        maxSize=capacity;
    }
    
    void makeRecent(Node* node){
        if(tail==node) return;
        
        removeNode(node);
        addLast(node);
    }
    
    int get(int key) {
        if(map.find(key)==map.end()) return -1;
        
        Node* node=map[key];
        makeRecent(node);
        return node->val;
    }
    
    void put(int key, int value) {
        if(map.find(key)==map.end()){
            
            if(size==maxSize){
                Node* node=removeHead();
                map.erase(node->key);
            }
            
            Node* node=new Node(key,value);
            addLast(node);
            map.insert({key,node});
        } else {
            Node* node=map[key];
            node->val=value;
            makeRecent(node);
        }
    }
};

// Insert,delete,getRandom O(1) leetcode 380 ==========================================

class RandomizedSet {
public:
    vector<int> arr;
    unordered_map<int,int> map; // key vs index
    RandomizedSet() {
        
    }
    
    bool insert(int val) {
        if(map.find(val)==map.end()){
            map[val]=arr.size();
            arr.push_back(val);
            return true;
        } else {
            return false;
        }
    }
    
    bool remove(int val) {
        if(map.find(val)==map.end()){
            return false;
        } else {
            int idx=map[val];
            
            int last=arr.back();
            
            arr[idx]=last;
            map[last]=idx;
            
            arr.pop_back();
            map.erase(val);
            
            return true;
        }
    }
    
    int getRandom() {
        return arr[rand() % arr.size()];
    }
};

// leet 1488 ================================================== 
vector<int> avoidFlood(vector<int>& rains) {
    unordered_map<int,int> filled;
    set<int> empty;
    
    vector<int> ans(rains.size(),-1);
    
    for(int i=0; i<rains.size(); i++){
        if(rains[i]==0){
            empty.insert(i);
            ans[i]=1;
        } else {
            int lake=rains[i];
            if(filled.find(lake)!=filled.end()){
                int day=filled[lake]; // day it was rained on lake
                
                auto zidx=empty.lower_bound(day);
                    
                if(zidx==empty.end()){
                    return {};
                }
                
                int ld=*zidx;
                
                ans[ld]=lake;
                empty.erase(ld);
                filled[lake]=i;
            } else {
                filled.insert({lake,i});
            }
            ans[i]=-1;
        }
    }
    
    return ans;
}

// leet 1146 ======================================================

class SnapshotArray {
public:
    int snap_id;
    vector<map<int,int>> arr;
    
    SnapshotArray(int length) {
        arr.resize(length);
        snap_id=0;
    }
    
    void set(int index, int val) {
        arr[index][snap_id]=val;
    }
    
    int snap() {
        return snap_id++;
    }
    
    int get(int index, int snap_id) {
        auto itr=arr[index].upper_bound(snap_id);
        
        if(itr==arr[index].begin()) return 0;
        // itr--; 
        return prev(itr)->second;
    }
};

// subarray sum problems  =============================================================================================================

// https://practice.geeksforgeeks.org/problems/subarray-with-0-sum-1587115621/1
bool subArrayExists(int arr[], int n){
    unordered_map<int,int> m;
    
    m[0]=-1;
    int csum=0;
    
    for(int i=0; i<n; i++){
        csum+=arr[i];
        
        if(m.find(csum)!=m.end()) return true;
        m[csum]=i;
    }
    
    return false;
}

// https://leetcode.com/problems/subarray-sum-equals-k/

// leet 1642 ================================================================== 

int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
    priority_queue<int,vector<int>,greater<int>> pq;
    for(int i=1; i<heights.size(); i++){
        int diff=heights[i]-heights[i-1];
        if(diff<=0) continue;
        pq.push(diff);
        if(pq.size()>ladders){
            cout<<pq.top()<<" ";
            bricks-=pq.top(); pq.pop();
        }
        if(bricks==0) return i;
        if(bricks<0) return i-1;
    }
    return heights.size()-1;
}
int main(){

}