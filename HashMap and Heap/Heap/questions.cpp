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

int main(){

}