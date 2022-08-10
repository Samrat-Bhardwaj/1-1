#include<iostream>
#include<vector>
using namespace std;

// longest bitonic sub gfg=========================================== 
int LongestBitonicSequence(vector<int>nums){
	 int n=nums.size();

    vector<int> dp_lr(n,0);


    for(int i=0; i<n; i++){
        dp_lr[i]=1;

        for(int j=i-1; j>=0; j--){
            if(nums[j]<nums[i]){
                dp_lr[i]=max(dp_lr[i],dp_lr[j]+1);
            }
        }
    }

    vector<int> dp_rl(n,0);

    for(int i=n-1; i>=0; i--){
        dp_rl[i]=1;

        for(int j=i+1; j<n; j++){
            if(nums[j]<nums[i]){
                dp_rl[i]=max(dp_rl[i],dp_rl[j]+1);
            }
        }
    }

    int ans=0;

    for(int i=0; i<n; i++){
        ans=max(ans,dp_lr[i]+dp_rl[i]-1);
    }

    return ans;
}

// https://practice.geeksforgeeks.org/problems/maximum-sum-increasing-subsequence4749/1 ====================================== 

int maxSumIS(int arr[], int n) {  
    vector<int> dp(n,0);
    int ans=0;

	for(int i=0; i<n; i++){
        dp[i]=arr[i];

        for(int j=i-1; i>=0; i--){
            if(arr[j] < arr[i]){
                dp[i]=max(dp[i],dp[j]+arr[i]);
            }
        }
        ans=max(ans,dp[i]);
    }    

    return ans;
}  

// https://practice.geeksforgeeks.org/problems/maximum-sum-bitonic-subsequence1857/1 ================================================ 


// leet 673 =================================================
int findNumberOfLIS(vector<int>& nums) {
    int n=nums.size();

    vector<int> dp(n,0);        
    vector<int> count(n,0);   

    int maxLen=0;
    int maxCount=0;

    for(int i=0; i<n; i++){
        dp[i]=1;
        count[i]=1;

        for(int j=i-1; j>=0; j--){
            if(nums[j] < nums[i]){
                if(dp[j]+1 > dp[i]){
                    dp[i]=dp[j]+1;
                    count[i]=count[j];
                } else if(dp[j]+1 == dp[i]){
                    count[i]+=count[j];
                }
            }
        }

        if(dp[i]>maxLen){
            maxLen=dp[i];
            maxCount=count[i];
        } else if(maxLen == dp[i]){
            maxCount+=count[i];
        }
    }     

    return maxCount;
}

int BS(vector<int>& dp, int h){
    int l=0;
    int r=dp.size()-1;

    while(l<=r){
        int mid=(l+r)/2;

        if(dp[mid]<h){
            l=mid+1;
        } else {
            r=mid-1;
        }
    }

    return l;
}

int maxEnvelopes(vector<vector<int>>& envelopes) {

    sort(envelopes.begin(),envelopes.end(),[](vector<int>& a,vector<int>& b){
        if(a[0]==b[0]) return a[1] > b[1];

        return a[0] < b[0];
    }); 

    // Arrays.sort(envelopes,(int[] a, int[] b)->{
    //     if(a[0]==b[0]) return b[1] - a[1];

    //     return a[0] - b[0];
    // }); 

    int n=envelopes.size();  

    vector<int> dp;

    for(int i=0; i<n; i++){
        int h=envelopes[i][1];

        int idx=BS(dp,h);
        if(idx==dp.size()){
            dp.push_back(h);
        } else {
            dp[idx]=h;
        }
    }

    return dp.size();
}

// https://www.geeksforgeeks.org/dynamic-programming-building-bridges/

// https://leetcode.com/problems/maximum-height-by-stacking-cuboids/

// https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/submissions/
int minimumMountainRemovals(vector<int>& nums) {
         int n=nums.size();

        vector<int> dp_lr(n,0);


        for(int i=0; i<n; i++){
            dp_lr[i]=1;

            for(int j=i-1; j>=0; j--){
                if(nums[j]<nums[i]){
                    dp_lr[i]=max(dp_lr[i],dp_lr[j]+1);
                }
            }
        }

        vector<int> dp_rl(n,0);

        for(int i=n-1; i>=0; i--){
            dp_rl[i]=1;

            for(int j=i+1; j<n; j++){
                if(nums[j]<nums[i]){
                    dp_rl[i]=max(dp_rl[i],dp_rl[j]+1);
                }
            }
        }

        int ans=0;

        for(int i=1; i<n-1; i++){
            if(dp_lr[i]==1 || dp_rl[i]==1){
                continue;
            }
            
            ans=max(ans,dp_lr[i]+dp_rl[i]-1);
        }

        return n-ans;
    }

int main(){

}