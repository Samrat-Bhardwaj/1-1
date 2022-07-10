import java.util.Arrays;
public class StringType {
    public static void print(String[][] sdp){

        for(String[] d:sdp){
            for(String s:d){
                System.out.print(s+" ");
            }
            System.out.println();
        }
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

    // lcs =================== 
    public static String memo_lcs(String text1, String text2, int n, int m, int[][] dp,String[][] sdp){
        if(n==0 || m==0){
            return sdp[n][m]="";
        }

        if(sdp[n][m]!=null) return sdp[n][m];

        if(text1.charAt(n-1)==text2.charAt(m-1)){
            return sdp[n][m]=memo_lcs(text1, text2, n-1, m-1, dp,sdp) + text1.charAt(n-1);
        } else {
            String s1=memo_lcs(text1,text2,n-1,m,dp,sdp);
            String s2=memo_lcs(text1, text2, n, m-1, dp, sdp);

            if(s1.length()>s2.length()){
                return sdp[n][m]=s1;
            } else {
                return sdp[n][m]=s2;
            }
        }
    }

    public static int tab_lcs(String text1, String text2, int N, int M){
        int[][] dp=new int[N+1][M+1];
        String[][] sdp=new String[N+1][M+1];

        for(int n=0; n<=N; n++){
            for(int m=0; m<=M; m++){
                if(n==0 || m==0){
                    dp[n][m]=0;
                    sdp[n][m]="";
                    continue;
                }
        
                //if(dp[n][m]!=-1) return dp[n][m];
        
                if(text1.charAt(n-1)==text2.charAt(m-1)){
                    dp[n][m]=dp[n-1][m-1]+1;//memo_lcs(text1, text2, n-1, m-1, dp) + 1;
                    sdp[n][m]=sdp[n-1][m-1]+text1.charAt(n-1);
                } else {
                    if(dp[n-1][m]>dp[n][m-1]){
                        dp[n][m]=dp[n-1][m];
                        sdp[n][m]=sdp[n-1][m];
                    } else {
                        dp[n][m]=dp[n][m-1];
                        sdp[n][m]=sdp[n][m-1];
                    }
                    // dp[n][m]=Math.max(dp[n-1][m],dp[n][m-1]);//Math.max(memo_lcs(text1,text2,n-1,m,dp), memo_lcs(text1, text2, n, m-1, dp));
                }
            }
        }
        print(sdp);
        return dp[N][M];
    }

    public static int longestCommonSubsequence(String text1, String text2) {
        int n=text1.length();
        int m=text2.length();

        int[][] dp=new int[n+1][m+1];
        String[][] sdp=new String[n+1][m+1];

        for(String[] s:sdp){
            Arrays.fill(s,null);
        }

        for(int[] a:dp){
            Arrays.fill(a,-1);
        }

        // return memo_lcs(text1,text2,n,m,dp,sdp);

        int ans=tab_lcs(text1, text2, n, m);
        
        return ans;
    }

    // leet 1092 ======================================================

    public String rec_scs(String str1, String str2, int n, int m){
        if(n==0){
            return str2.substring(0,m);
        }
        if(m==0){
            return str1.substring(0,n);
        }
        
        if(str1.charAt(n-1)==str2.charAt(m-1)){
            return rec_scs(str1,str2,n-1,m-1) + str1.charAt(n-1);
        } else {
            String ans1=rec_scs(str1,str2,n-1,m);
            String ans2=rec_scs(str1,str2,n,m-1);
            
            if(ans1.length()<ans2.length()){
                return ans1+str1.charAt(n-1);
            } else {
                return ans2+str2.charAt(m-1);
            }
        }
    }

    public static String tab_lcs(String text1, String text2, int N, int M){
        int[][] dp=new int[N+1][M+1];
        String[][] sdp=new String[N+1][M+1];

        for(int n=0; n<=N; n++){
            for(int m=0; m<=M; m++){
                if(n==0 || m==0){
                    dp[n][m]=0;
                    sdp[n][m]="";
                    continue;
                }
        
                //if(dp[n][m]!=-1) return dp[n][m];
        
                if(text1.charAt(n-1)==text2.charAt(m-1)){
                    dp[n][m]=dp[n-1][m-1]+1;//memo_lcs(text1, text2, n-1, m-1, dp) + 1;
                    sdp[n][m]=sdp[n-1][m-1]+text1.charAt(n-1);
                } else {
                    if(dp[n-1][m]>dp[n][m-1]){
                        dp[n][m]=dp[n-1][m];
                        sdp[n][m]=sdp[n-1][m];
                    } else {
                        dp[n][m]=dp[n][m-1];
                        sdp[n][m]=sdp[n][m-1];
                    }
                    // dp[n][m]=Math.max(dp[n-1][m],dp[n][m-1]);//Math.max(memo_lcs(text1,text2,n-1,m,dp), memo_lcs(text1, text2, n, m-1, dp));
                }
            }
        }
        
        return sdp[N][M];
    }

    public String shortestCommonSupersequence(String str1, String str2) {
        String lcs=tab_lcs(str1,str2,str1.length(),str2.length());
        
        int i=0; int j=0;
        int k=0;
        
        String ans="";
        
        while(k<lcs.length()){
            while(str1.charAt(i)!=lcs.charAt(k)){
                ans+=str1.charAt(i);
                i++;
            }
            
            while(str2.charAt(j)!=lcs.charAt(k)){
                ans+=str2.charAt(j);
                j++;
            }
            
            ans+=lcs.charAt(k);
            i++;
            j++;
            k++;
        }
        
        ans+=str1.substring(i);
        ans+=str2.substring(j);
        
        return ans;
    }

    // https://www.geeksforgeeks.org/maximum-number-of-uncrossed-lines-between-two-given-arrays/

    // solve


    // longest pallindromic subsequnce ============================================= 
    public int memo_lps(String s, int i, int j,int[][] dp){
        if(i>j){
            return dp[i][j]=0;
        }

        if(i==j){
            return dp[i][j]=1;
        }

        if(dp[i][j]!=0) return dp[i][j];

        if(s.charAt(i)==s.charAt(j)){
            return dp[i][j]=memo_lps(s, i+1, j-1, dp) + 2;
        } else {
            return dp[i][j]=Math.max(memo_lps(s, i+1, j, dp),memo_lps(s, i, j-1, dp));
        }
    }
    // create sdp 
    public int tab_lps(String s){
        int n=s.length();
        int[][] dp=new int[n][n];

        for(int gap=0; gap<n; gap++){
            for(int i=0,j=gap; j<n; i++,j++){
                if(i==j){
                    dp[i][j]=1;
                    continue;
                }
        
                // if(dp[i][j]!=0) return dp[i][j];
        
                if(s.charAt(i)==s.charAt(j)){
                    dp[i][j]=dp[i+1][j-1]+2; //memo_lps(s, i+1, j-1, dp) + 2;
                } else {
                    dp[i][j]=Math.max(dp[i+1][j],dp[i][j-1]); //Math.max(memo_lps(s, i+1, j, dp),memo_lps(s, i, j-1, dp));
                }
            }
        }
        return dp[0][n-1];
    }

    public int longestPalindromeSubseq(String s) {
        int[][] dp=new int[s.length()][s.length()];

        return memo_lps(s, 0, s.length()-1, dp);
    }

    // leetcode 72 ========================================== 
    public int memo_72(int n, int m,String s1, String s2, int[][] dp){
        if(n==0) return dp[n][m]=m;
        if(m==0) return dp[n][m]=n;

        if(dp[n][m]!=0) return dp[n][m];

        if(s1.charAt(n-1)==s2.charAt(m-1)){
            return dp[n][m]=memo_72(n-1, m-1, s1, s2, dp);
        } else {
            int insert = memo_72(n, m-1, s1, s2, dp);
            int delete = memo_72(n-1, m, s1, s2, dp);
            int replace= memo_72(n-1, m-1, s1, s2, dp);

            return dp[n][m]= Math.min(Math.min(insert,delete),replace) + 1;
        }
    }

    public int tab(String s1, String s2){
        int N=s1.length();
        int M=s2.length();

        int[][] dp=new int[N+1][M+1];

        for(int n=0; n<=N; n++){
            for(int m=0; m<=M; m++){
                if(n==0) {
                    dp[n][m]=m;
                    continue;
                }
                if(m==0){
                    dp[n][m]=n;
                    continue;
                }

                //if(dp[n][m]!=0) return dp[n][m];

                if(s1.charAt(n-1)==s2.charAt(m-1)){
                    dp[n][m]=dp[n-1][m-1];//memo_72(n-1, m-1, s1, s2, dp);
                } else {
                    int insert = dp[n][m-1];//memo_72(n, m-1, s1, s2, dp);
                    int delete = dp[n-1][m];//[memo_72(n-1, m, s1, s2, dp);
                    int replace= dp[n-1][m-1];//memo_72(n-1, m-1, s1, s2, dp);

                    dp[n][m]= Math.min(Math.min(insert,delete),replace) + 1;
                }
            }
        }

        return dp[N][M];
    }
    public static void main(String[] args) {
        String s1="abecfda";
        String s2="aebfal";

        System.out.println(longestCommonSubsequence(s1,s2));
    }

    // subsequence of type a^i,b^j,c^k

    public int count_subs(String str){
        int eaa=0;
        int eab=0;
        int eac=0;

        for(int i=0; i<str.length(); i++){
            if(str.charAt(i)=='a'){
                eaa=2*eaa + 1;
            } else if(str.charAt(i)=='b'){
                eab = 2*eab + eaa;
            } else {
                eac = 2*eac + eab;
            }
        }

        return eac;
    }

    // wildcard matching ================================================================ 

    // tabulate this

    public int MatchStrings(String s, String p,int n, int m,int[][] dp){
        if(n==0 || m==0){
            if(n==0 && m==0){
                return dp[n][m]=1;
            } else if(m==1 && p.charAt(m-1)=='*'){
                return dp[n][m]=1;
            } else {
                return dp[n][m]=0;
            }
        }
        
        if(dp[n][m]!=-1) return dp[n][m];
        
        if(p.charAt(m-1)=='?'){
            return dp[n][m]=MatchStrings(s,p,n-1,m-1,dp);
        } else if(p.charAt(m-1)=='*'){
            int ans1=MatchStrings(s,p,n-1,m,dp);
            int ans2=MatchStrings(s,p,n,m-1,dp);
            
            if(ans1==1 || ans2==1){
                return dp[n][m]=1;
            } else {
                return dp[n][m]=0;
            }
        } else if(s.charAt(n-1)==p.charAt(m-1)){
            return dp[n][m]=MatchStrings(s,p,n-1,m-1,dp);
        } else {
            return dp[n][m]=0;
        }
    }
    
    public boolean isMatch(String s, String p) {
        StringBuilder sb=new StringBuilder();
        if(p.length()==0){
            return s.length()==0;
        }
        
        int i=1;
        sb.append(p.charAt(0));
        
        while(i<p.length()){
            while(i<p.length() && p.charAt(i)=='*' && p.charAt(i-1)==p.charAt(i)){
                i++;
            }
            
            if(i<p.length())
                sb.append(p.charAt(i));
            
            i++;
        }
        
        p=sb.toString();
        
        int n=s.length();
        int m=p.length();
        
        int[][] dp=new int[n+1][m+1];
        
        for(int[] d:dp){
            Arrays.fill(d,-1);
        }
        
        int ans=MatchStrings(s,p,n,m,dp);
        
        return ans==1;
    }
}
