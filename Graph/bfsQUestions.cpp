int orangesRotting(vector<vector<int>>& grid) {
    
}

// leet 542 ===================================
vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int n=matrix.size();
    int m=matrix[0].size();

    vector<vector<int>> ans(n,vector<int>(m,0));

    queue<int> q;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(mat[i][j]==0){
                q.push(i*m+j);
                mat[i][j]=-1;
            }
        }
    }        

    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    int level=0;
    while(q.size()){
        int s=q.size();
        while(s-->0){
            int idx = q.front(); q.pop();

            int i = idx/m;
            int j = idx%m;

            for(int[] dir: dirs){
                int x = i + dir[0];
                int y = j + dir[1];

                if(x>=0 && y>=0 && x<n && y<m && mat[x][y]!=-1){
                    if(mat[x][y]==1){
                        ans[x][y] =  level + 1;
                    }
                    que.push(x*m+y);
                    mat[x][y]=-1;
                }
            }
        }
        level++;
    }

    return ans;
}

// leet 1020 =============================================== 