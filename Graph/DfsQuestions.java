public class DfsQuestions {
    // leet 200 ====================== 
    public void dfs(int i, int j, char[][] grid){
        // vis mark
        grid[i][j]='0';

        int[][] dirs = {{0,1},{1,0},{0,-1},{-1,0}};

        for(int[] dir:dirs){
            int x = i + dir[0];
            int y = j + dir[1];

            if(x>=0 && y>=0 && x<grid.length && y<grid[0].length && grid[x][y]=='1'){
                dfs(x,y,grid);
            }
        }
    }

    public int numIslands(char[][] grid) {
        int comps=0;

        for(int i=0; i<grid.length; i++){
            for(int j=0; j<grid[0].length; j++){
                if(grid[i][j]=='1'){
                    comps++;
                    dfs(i,j,grid);
                }
            }
        }

        return comps;
    }

// leet 130 ===========================================
    public void changeTo$(int i, int j, char[][] grid){
        grid[i][j]='$';

        int[][] dirs = {{0,1},{1,0},{0,-1},{-1,0}};

        for(int[] dir:dirs){
            int x = i + dir[0];
            int y = j + dir[1];

            if(x>=0 && y>=0 && x<grid.length && y<grid[0].length && grid[x][y]=='O'){
                changeTo$(x, y, grid);
            }
        }
    }

    public void solve(char[][] board) {
        int n=board.length;
        int m=board[0].length;


        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(i==0 || j==0 || i==n-1 || j==m-1){
                    if(board[i][j]=='O'){
                        changeTo$(i, j, board);
                    }
                }
            }
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(board[i][j]=='$'){
                    board[i][j]='O';
                } else if(board[i][j]=='O'){
                    board[i][j]='X';
                }
            }
        }
    }
}
