import java.util.ArrayList;

public class LIS {
    public static int lengthOfLIS(int[] nums){
        int n=nums.length;

        int[]dp=new int[n];

        int lis_len=0;

        for(int i=0; i<n; i++){
            dp[i]=1;

            for(int j=i-1; j>=0; j--){
                if(nums[j]<nums[i]){
                    dp[i]=Math.max(dp[i],dp[j]+1);
                }
            }
            lis_len=Math.max(lis_len,dp[i]);
        }

        return lis_len;
    }

    // LIS better ================================================================ 

    public int BS(ArrayList<Integer> dp, int ele){
        int si=0;
        int ei=dp.size()-1;
        
        while(si<=ei){
            int mid=(si+ei)/2;
            
            if(dp.get(mid)<ele){
                si=mid+1;
            } else {
                ei=mid-1;
            }
        }
        
        return si;
    }
    public int lengthOfLIS_better(int[] nums){
        ArrayList<Integer> dp=new ArrayList<>();
        
        for(int i=0; i<nums.length; i++){
            int ele=nums[i];
            
            int inserting_position=BS(dp,ele);
            
            if(dp.size()==inserting_position){
                dp.add(ele);
            } else {
                dp.set(inserting_position,ele);
            }
        }
        
        return dp.size();
    }
    public static void main(String[] args) {
        
    }
}
