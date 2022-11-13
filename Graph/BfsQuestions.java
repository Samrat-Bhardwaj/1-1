import java.util.LinkedList;

public class BfsQuestions {
    // leetcode 994 ==================================================
    public int orangesRotting(int[][] grid) {
        LinkedList<Integer> que=new LinkedList<>();
        int n=grid.length;
        int m=grid[0].length;

        int fresh_oranges=0;
        for(int i=0; i<grid.length; i++){
            for(int j=0; j<grid[0].length; j++){
                if(grid[i][j]==1){
                    fresh_oranges++;
                } else if(grid[i][j]==2) {
                    int idx=i*m+j;
                    que.addLast(idx);
                }
            }
        }

        int level=0;
        int[][] dirs={{0,1},{1,0},{0,-1},{-1,0}};

        while(que.size()>0){
            int size=que.size();

            while(size-->0){
                int idx=que.removeFirst();

                int i=idx/m;
                int j=idx%m;

                for(int[] dir:dirs){
                    int x=i+dir[0];
                    int y=j+dir[1];

                    if(x>=0 && y>=0 && x<n && y<m && grid[x][y]==1){
                        que.addLast(x*m+y);
                        grid[x][y]=2; // rotting oranges
                        fresh_oranges--;
                    }
                }
            }
            level++;
        }

        return fresh_oranges == 0 ? level + 1 : -1;
    }

    // is graph bipartite 

    // all graphs are bipartite except odd cycle graph ======================================================

    // -1 => unvisited
    // 0 => green;
    // 1=> blue
    public boolean isOddCycle(int src, int[][] graph, int[] vis){
        LinkedList<Integer> que = new LinkedList<>();
        que.addLast(src);

        int color = 0; // level
        while(que.size()>0){
            int size = que.size();

            while(size -- > 0){
                int u = que.removeFirst();

                if(vis[u]!=-1){
                    if(vis[u]!=color) return true;
                    continue;
                }
                // removal time mark
                vis[u] = color;

                for(int v : graph[u]){
                    if(vis[v]==-1){
                        que.addLast(v);
                    }
                }
            }
            color = (color+1)%2;
        }

        return false;
    }

    public boolean isBipartite(int[][] graph) {
        int n = graph.length;
        int[] vis = new int[n];
        Arrays.fill(vis,-1); 

        for(int i=0; i<graph.length; i++){
            if(vis[i]==-1){
                if(isOddCycle(i, graph, vis)) return false;
            }
        }

        return true;
    }

    // walls and gates lintcode  ====================================================

    public void wallsAndGates(int[][] rooms) {
        int inf = 2147483647;
        LinkedList<Integer> que = new LinkedList<>();

        int n = rooms.length;
        int m = rooms[0].length;

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(rooms[i][j] == 0){
                    que.addLast(i*m+j);
                }
            }
        }

        int[][] dirs={{0,1},{1,0},{0,-1},{-1,0}};
        int level=0;
        while(que.size()>0){
            int s = que.size();
            while(s-- > 0){
                int idx = que.removeFirst();

                int i=idx/m;
                int j=idx%m;

                for(int[] dir:dirs){
                    int x=i+dir[0];
                    int y=j+dir[1];

                    if(x>=0 && y>=0 && x<n && y<m && rooms[x][y]==inf){
                        que.addLast(x*m+y);
                        rooms[x][y] = level + 1;
                    }
                }
            }
            level++;
        }
        
    }

    // leet 207 =====================================================
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        int[] indegree = new int[numCourses];
        
        ArrayList<Integer>[] graph = new ArrayList[numCourses];
        LinkedList<Integer> que = new LinkedList<>();
        ArrayList<Integer> ans = new ArrayList<>();
        
        for(int i=0; i<numCourses; i++){
            graph[i] = new ArrayList<>();
        }
        
        for(int[] pre:prerequisites){
            int v = pre[0];
            int u = pre[1];
            
            indegree[v]++;
            graph[u].add(v);
        }
        
        for(int i=0; i<numCourses; i++){
            if(indegree[i]==0){
                que.addLast(i);
            }
        }
        
        while(que.size()>0){
            int u = que.removeFirst();
            ans.add(u);

            for(int e: graph[u]){
                if(--indegree[e]==0){
                    que.addLast(e);
                }
            }
        }
        
        return ans.size() == numCourses;
    }

    // leet 210 =======================================================
    public int[] findOrder(int numCourses, int[][] prerequisites) {
        int[] indegree = new int[numCourses];
        
        ArrayList<Integer>[] graph = new ArrayList[numCourses];
        LinkedList<Integer> que = new LinkedList<>();
        ArrayList<Integer> ans = new ArrayList<>();
        
        for(int i=0; i<numCourses; i++){
            graph[i] = new ArrayList<>();
        }
        
        for(int[] pre:prerequisites){
            int v = pre[0];
            int u = pre[1];
            
            indegree[v]++;
            graph[u].add(v);
        }
        
        for(int i=0; i<numCourses; i++){
            if(indegree[i]==0){
                que.addLast(i);
            }
        }
        
        while(que.size()>0){
            int u = que.removeFirst();
            ans.add(u);

            for(int e: graph[u]){
                if(--indegree[e]==0){
                    que.addLast(e);
                }
            }
        }
        
        if(ans.size() != numCourses) return new int[]{};
        
        int[] res = new int[numCourses];
        for(int i=0; i<numCourses; i++){
            res[i] = ans.get(i);
        }
        
        return res;
    }
}
