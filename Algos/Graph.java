import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.LinkedList;

public class Graph {
    public static void addEdge(int u, int v, ArrayList<Integer>[] graph){
        graph[u].add(v);
        graph[v].add(u);
    }

    public static void dfs(int src, boolean[] visited,ArrayList<Integer>[] graph){
        visited[src]=true;

        System.out.println("I am at vertex "+src);

        for(int nbr : graph[src]){
           if(!visited[nbr]){
            System.out.println("Moving from "+src+" to "+nbr);
            dfs(nbr,visited,graph); 
           }
        }
        // for(int i=0; i<graph[src].size(); i++){
        //     int nbr=graph[src].get(i);
        // }

        System.out.println("Removing from the stack "+ src);
        
    }

    public static void bfs(ArrayList<Integer>[] graph, int src){
        int n=graph.length;

        boolean[] visited=new boolean[n];

        LinkedList<Integer> que=new LinkedList<>();

        que.addLast(src);
        visited[src]=true;
        int level=0;

        while(que.size()>0){
            System.out.println("I am on level " + level + " and vertices on this level are following ");

            int size=que.size();
            while(size-->0){
                int v=que.removeFirst();
                System.out.println(v + " is removed ");

                for(int nbr : graph[v]){
                    if(!visited[nbr]){
                        visited[nbr]=true;
                        System.out.println("===== "+nbr+" is added on level "+(level+1));
                        que.addLast(nbr);
                    }
                }                
            }

            level++;
        }
    }

    public static void main(String[] args) {
        int n=8;
        ArrayList<Integer>[] graph=new ArrayList[n];

        for(int i=0; i<n; i++){
            graph[i]=new ArrayList<>();
        }

        addEdge(0, 1, graph);   
        addEdge(1, 2, graph);   
        addEdge(2, 3, graph);   
        addEdge(1, 3, graph);   
        addEdge(4, 6, graph);   
        addEdge(6, 7, graph);   
        addEdge(4, 7, graph);   
        addEdge(4, 5, graph);   

        boolean[] visited=new boolean[n];

        for(int i=0; i<n; i++){
            if(visited[i]==false)
                dfs(i,visited,graph);
        }

        addEdge(3, 4, graph);
        addEdge(0, 2, graph);

        System.out.println("============================== BFS ================================ ");

        bfs(graph,0);
    }
}
