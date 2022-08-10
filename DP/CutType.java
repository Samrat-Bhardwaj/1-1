public class CutType {
    public static int mcm_rec(int[] arr, int si, int ei){
        if(si+1==ei){
            return 0;
        }

        int ans=(int)(1e9);

        for(int cut=si+1; cut<ei; cut++){
            int left = mcm_rec(arr, si, cut);
            int right= mcm_rec(arr, cut, ei);

            int curr_ans= left + arr[si]*arr[cut]*arr[ei] +right;
            ans=Math.min(ans,curr_ans);
        }

        return ans;
    }

    public static int mcm_memo(int[] arr, int si, int ei, int[][] dp){
        if(si+1==ei){
            return dp[si][ei]=0;
        }

        if(dp[si][ei]!=0) return dp[si][ei];

        int ans=(int)(1e9);
        for(int cut=si+1; cut<ei; cut++){
            int left = mcm_memo(arr, si, cut,dp);
            int right= mcm_memo(arr, cut, ei,dp);

            int curr_ans= left + arr[si]*arr[cut]*arr[ei] +right;
            ans=Math.min(ans,curr_ans);
        }

        return dp[si][ei]=ans;
    }

    public static int mcm_tab(int[] arr, int SI, int EI, int[][] dp){
        int n=arr.length;

        for(int gap=1; gap<n; gap++){
            for(int si=0,ei=gap; ei<n; si++,ei++){
                if(si+1==ei){
                    dp[si][ei]=0;
                    continue;
                }
        
                int ans=(int)(1e9);
                for(int cut=si+1; cut<ei; cut++){
                    int left = dp[si][cut];//mcm_memo(arr, si, cut,dp);
                    int right= dp[cut][ei]; //mcm_memo(arr, cut, ei,dp);
        
                    int curr_ans= left + arr[si]*arr[cut]*arr[ei] +right;
                    ans=Math.min(ans,curr_ans);
                }
        
                dp[si][ei]=ans;
            }
        }

        return dp[SI][EI];
    }

    // https://www.geeksforgeeks.org/minimum-maximum-values-expression/ ==================================== 

    static class Pair {
        int minV;
        int maxV;
        String minR;
        String maxR;

        public Pair(int minV, int maxV, String minR, String maxR){
            this.minV=minV;
            this.maxV=maxV;
            this.minR=minR;
            this.maxR=maxR;
        }
    }

    public static Pair evaluateMinMax(String str, int si, int ei, Pair[][] dp){
        if(si==ei){
            int val=str.charAt(si)-'0';
            Pair bPair=new Pair(val, val, val+"", val+"");
            return dp[si][ei]=bPair;
        }

        if(dp[si][ei]!=null) return dp[si][ei];

        Pair ansPair=new Pair((int)(1e9), (int)(-1e9), "", "maxR");

        for(int cut=si+1; cut<ei; cut+=2){
            Pair lpair=evaluateMinMax(str, si, cut-1, dp);
            Pair rPair=evaluateMinMax(str, cut+1, ei, dp);

            int minV=eval(lpair.minV,rPair.minV,str.charAt(cut));   
            int maxV=eval(lpair.maxV,rPair.maxV,str.charAt(cut));
            
            if(minV < ansPair.minV){
                ansPair.minV=minV;
                ansPair.minR="("+lpair.minR+" "+str.charAt(cut)+" "+rPair.minR+")";
            }

            if(maxV>ansPair.maxV){
                ansPair.maxV=maxV;
                ansPair.maxR="("+lpair.maxR+" "+str.charAt(cut)+" "+rPair.maxR+")";;
            }
        }

        return dp[si][ei]=ansPair;
    }

    public static int eval(int a, int b, char ch){
        if(ch=='+'){
            return a+b;
        } else {
            return a*b;
        }
    }

    public static void printArray(int[][] dp){
        for(int i=0; i<dp.length; i++){
            for(int j=0; j<dp[i].length; j++){
                System.out.print(dp[i][j]+" ");
            }
            System.out.println();
        }
    }

    // leetcode 132 ============================================================================================
    public boolean[][] makeIsPallindrome(String str){
        int n=str.length();

        boolean[][] dp=new boolean[n][n];

        for(int diag=0; diag<n; diag++){
            for(int i=0,j=diag; j<n; i++,j++){
                if(diag==0){ // length 1 (i==j)
                    dp[i][j]=true;
                } else if(diag==1){ // length 2;
                    dp[i][j]= (str.charAt(i)==str.charAt(j));
                } else {
                    if(str.charAt(i)==str.charAt(j)){
                        dp[i][j]=dp[i+1][j-1];
                    }
                }
            }
        }

        return dp;
    }

    public int minCut_memo(String str,int si, boolean[][] isPallindrome, int[] dp){
        if(isPallindrome[si][str.length()-1]){
            return dp[si]=0;
        }

        if(dp[si]!=-1){
            return dp[si];
        }

        int ans=(int)(1e9);
        for(int cut=si; cut<str.length(); cut++){
            if(isPallindrome[si][cut]){
                ans=Math.min(ans,minCut_memo(str,cut+1,isPallindrome,dp)+1);
            }
        }

        return dp[si]=ans;
    }

    public int minCut_tab(String str, int SI, boolean[][] isPallindrome, int[] dp){
        for(int si=str.length()-1; si>=0; si--){
            if(isPallindrome[si][str.length()-1]){
                dp[si]=0;
                continue;
            }
    
            int ans=(int)(1e9);
            for(int cut=si; cut<str.length(); cut++){
                if(cut+1<str.length() && isPallindrome[si][cut]){
                    ans=Math.min(ans,dp[cut+1]+1);//ans=Math.min(ans,minCut_memo(str,cut+1,isPallindrome,dp)+1);
                }
            }
    
            dp[si]=ans;
        }

        return dp[SI];
    }

    public int minCut(String s) {
        boolean[][] isPallindrome=makeIsPallindrome(s);
        int[] dp=new int[s.length()];

        Arrays.fill(dp,-1);

        // return minCut_memo(s, 0, isPallindrome, dp);
        return minCut_tab(s, 0, isPallindrome, dp);
    }

    public static void main(String[] args) {
        // int[] arr={40,20,30,10,30};
        // int n=arr.length;
        // int[][] dp=new int[n][n];
        // System.out.println(mcm_tab(arr,0,arr.length-1,dp));

        String str="1+2*3+4*5";
        int n=str.length();
        Pair dp[][]=new Pair[n][n];

        Pair ansPair=evaluateMinMax(str, 0, n-1, dp);

        System.out.println("Min value is "+ansPair.minV+" by using this "+ansPair.minR);
        System.out.println("Max value is "+ansPair.maxV+" by using this "+ansPair.maxR);
        // printArray(dp);
    }
}