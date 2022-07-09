import java.util.Scanner;

class Intro {
    public static int rec_fib(int n){
        if(n==0 || n==1){
            return n;
        }

        int ans=0;
        ans=rec_fib(n-1)+rec_fib(n-2);

        return ans;
    }
    // memo , 
    public static int memo_fib(int n,Integer[] memo){
        if(n==0 || n==1){
            return n;
        }

        if(memo[n]!=null) return memo[n];

        int ans=0;
        ans=memo_fib(n-1,memo)+memo_fib(n-2,memo);

        return memo[n]=ans;
    }

    public static int tab(int N){
        int[] dp=new int[N+1];

        for(int n=0; n<=N; n++){
            if(n==0 || n==1){
                dp[n]=n;
                continue;
            }
    
            int ans=0;
            ans=dp[n-1]+dp[n-2];//memo_fib(n-1,memo)+memo_fib(n-2,memo);
    
            dp[n]=ans;
        }

        return dp[N];
    }

    // memo of maze path single jump

    // here dp[i][j] represents numbers of paths from i,j to n-1,m-1
    public static int maze_paths_memo(int i, int j, int[][] dp, int n, int m){
        if(i==n-1 && j==m-1){
            return dp[i][j]=1;
        }

        if(dp[i][j]!=0) return dp[i][j];

        int paths=0;

        if(i+1<n)
            paths+=maze_paths_memo(i+1, j, dp, n, m);

        if(j+1<m)
            paths+=maze_paths_memo(i, j+1, dp, n, m);

        if(i+1<n && j+1<m)
            paths+=maze_paths_memo(i+1,j+1,dp,n,m);

        return dp[i][j]=paths;
    }

    public static int tab(int n, int m){
        int[][] dp=new int[n][m];

        for(int i=n-1; i>=0; i--){
            for(int j=m-1; j>=0; j--){
                if(i==n-1 && j==m-1){
                    dp[i][j]=1;
                    continue;
                }
        
                // if(dp[i][j]!=0) return dp[i][j];
        
                int paths=0;
        
                if(i+1<n)
                    paths+=dp[i+1][j];//maze_paths_memo(i+1, j, dp, n, m);
        
                if(j+1<m)
                    paths+=dp[i][j+1];//maze_paths_memo(i, j+1, dp, n, m);
        
                if(i+1<n && j+1<m)
                    paths+=dp[i+1][j+1];//maze_paths_memo(i+1,j+1,dp,n,m);
        
                dp[i][j]=paths;
            }
        }

        return dp[0][0];
    }

    // friends pairing ========================================= 
    public static int memo_friendsPairing(int n, int[] dp){
        if(n==0 || n==1){
            return dp[n]=1;
        }

        if(dp[n]!=0) return dp[n];

        int single=memo_friendsPairing(n-1, dp);

        int pairUP=memo_friendsPairing(n-2, dp)*(n-1);

        return dp[n]=single+pairUP;
    }

    public static int tab_friendsPairing(int N){
        int[] dp=new int[N+1];

        for(int n=0; n<=N; n++){
            if(n==0 || n==1){
                dp[n]=1;
                continue;
            }
    
            //if(dp[n]!=0) return dp[n];
    
            int single=dp[n-1];//memo_friendsPairing(n-1, dp);
    
            int pairUP=dp[n-2]*(n-1);//memo_friendsPairing(n-2, dp)*(n-1);
    
            dp[n]=single+pairUP;
        }

        return dp[N];
    } // solve this using 2 pointers 


    // minimum jumps to reach "n"

    public static int memo_jump_game(int[] jumps, int idx, int[] dp,int n){
        if(idx==n){
            return 0;
        }

        if(jumps[idx]==0){
            return dp[idx]=(int)(1e9);
        }

        if(dp[idx]!=0) return dp[idx];

        int ans=(int)(1e9);

        for(int j=1; j<=jumps[idx]; j++){
            if(idx+j<=n){
                ans=Math.min(ans,memo_jump_game(jumps, idx+j, dp, n));
            }
        }

        return dp[idx]= ans + 1;
    }

    public static int tab_jump_game(int[] jumps, int n){
        int[] dp=new int[n];

        for(int idx=n; idx>=0; idx--){
            if(idx==n){
                dp[idx]=0;
                continue;
            }
    
            if(jumps[idx]==0){
                dp[idx]=(int)(1e9);
                continue;
            }
    
            //if(dp[idx]!=0) return dp[idx];
    
            int ans=(int)(1e9);
    
            for(int j=1; j<=jumps[idx]; j++){
                if(idx+j<=n){
                    ans=Math.min(ans,dp[idx+j]);//Math.min(ans,memo_jump_game(jumps, idx+j, dp, n));
                }
            }
    
            dp[idx]= ans + 1;
        }
        
        return dp[0];
    }

    public static int pallindromic_substrings(String str){
        int n=str.length();

        boolean[][] dp=new boolean[n][n];
        int lsi=-1;
        int lei=-1;

        int number_of_pallindromes=0;
        int longest_pallindrome_length=0;

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

                if(dp[i][j]){
                    number_of_pallindromes++;
                    lsi=i;
                    lei=j;
                    longest_pallindrome_length=diag+1;
                }
            }
        }

        String longest_pall=str.substring(lsi, lei+1);
        return longest_pallindrome_length;
    }


    // goldmine 
    static int rec(int i, int j, int[][] gold, int n, int m,int[][] dp){
        if(j==m-1){
            return dp[i][j]=gold[i][j];
        }
        
        if(dp[i][j]!=0) return dp[i][j];
        
        int ans=0;
        if(i-1>=0)
            ans=Math.max(ans,rec(i-1,j+1,gold,n,m,dp));
        
        ans=Math.max(ans,rec(i,j+1,gold,n,m,dp));
        
        if(i+1<n)
            ans=Math.max(ans,rec(i+1,j+1,gold,n,m,dp));
            
        return dp[i][j]=ans + gold[i][j];
    }

    public static int tab(int[][] gold, int n, int m){
        int[][] dp=new int[n][m];

        for(int j=m-1; j>=0; j--){
            for(int i=0; i<n; i++){
                if(j==m-1){
                    dp[i][j]=gold[i][j];
                    continue;
                }
                
                //if(dp[i][j]!=0) return dp[i][j];
                
                int ans=0;
                if(i-1>=0)
                    ans=Math.max(ans,dp[i-1][j+1]);//Math.max(ans,rec(i-1,j+1,gold,n,m,dp));
                
                ans=Math.max(ans,dp[i][j+1]);//Math.max(ans,rec(i,j+1,gold,n,m,dp));
                
                if(i+1<n)
                    ans=Math.max(ans,dp[i+1][j+1]);//Math.max(ans,rec(i+1,j+1,gold,n,m,dp));
                    
                dp[i][j]=ans + gold[i][j];
            }
        }

        int max_gold=0;
        for(int i=0; i<n; i++){
            max_gold=Math.max(max_gold,dp[i][0]);
        }

        return max_gold;
    }
    public static void main(String[] args) {
        Scanner scn=new Scanner(System.in);

        int n=scn.nextInt();

        Integer[] memo=new Integer[n+1];
        int nthTerm=memo_fib(n,memo);

        System.out.println(nthTerm);
    }
}