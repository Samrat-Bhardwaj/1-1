import java.util.ArrayList;
import java.util.LinkedList;
class directedGraph {
    public class Edge {
        int u;
        int v;
        int w;

        public Edge(int u, int v, int w){
            this.u=u;
            this.v=v;
            this.w=w;
        }
    }

    public static void addEdge(int u, int v, ArrayList<Edge>[] graph){
        graph[u].add(new Edge(u, v, 0));
    }

    public static void dfs_topo(int src, ArrayList<Edge>[] graph, boolean[] vis, ArrayList<Integer> ans){
        vis[src] = true;
        for(Edge e: graph[src]){
            if(vis[e.v]==false){
                dfs_topo(e.v, graph, vis, ans);
            }
        }

        ans.add(src);
    }

    public static void topologicalSort(int n, ArrayList<Edge>[] graph){
        boolean[] vis = new boolean[n];

        ArrayList<Integer> ans = new ArrayList<>();

        for(int i=0; i<n; i++){
            if(vis[i]==false){
                dfs_topo(i,graph,vis,ans);
            }
        }

        for(int i=ans.size()-1; i>=0; i--){
            System.out.println(ans.get(i));
        }
    }

    // Kahn's algo ===================================
    public static ArrayList<Integer> Kahns(int n, ArrayList<Edge>[] graph){
        LinkedList<Integer> que=new LinkedList<>();
        ArrayList<Integer> ans= new ArrayList<>();
        
        int[] indegree = new int[n];
        for(int i=0; i<n; i++){
            for(Edge e: graph[i]){
                indegree[e.v]++;
            }
        }

        for(int i=0; i<n; i++){
            if(indegree[i]==0){
                que.addLast(i);
            }
        }

        while(que.size()>0){
            int u = que.removeFirst();
            ans.add(u);

            for(Edge e: graph[u]){
                if(--indegree[e.v]==0){
                    que.addLast(e.v);
                }
            }
        }

        if(ans.size()!=n){
            System.out.println("Topological sorting is not possible because of cycle");
            ans = new ArrayList<>();
        }

        return ans;
    }
    public static void main(String[] args) {
        
    }
}
