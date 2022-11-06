import java.util.ArrayList;
import java.util.LinkedList;
class Graph {
    public static class Edge {
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
        graph[v].add(new Edge(v, u, 0));
    }

    public void dfs(int src,boolean[] vis, ArrayList<Edge>[] graph){
        vis[src]=true;

        for(Edge e:graph[src]){
            int nbr=e.v;

            if(vis[nbr]==false){
                dfs(nbr,vis,graph);
            }
        }
    }

    public static boolean hasPath(int src, int des, boolean[] vis, ArrayList<Edge>[] graph){
        if(src==des){
            return true;
        }

        vis[src]=true;
        boolean ans = false;

        for(Edge e:graph[src]){
            int nbr=e.v;

            if(vis[nbr]==false){
                ans = ans || hasPath(nbr, des, vis, graph);
            }
        }

        return ans;
    }

    public static void allPath(int src, int des, boolean[] vis, ArrayList<Edge>[] graph, String psf){
        if(src==des){
            System.out.println(psf+","+des);
            return;
        }

        vis[src]=true;

        for(Edge e:graph[src]){
            int nbr=e.v;

            if(vis[nbr]==false){
                allPath(nbr, des, vis, graph, psf+src);
            }
        }
    }

    public static class Pair {
        int wsf;
        String psf;

        public Pair(){

        }
        public Pair(int wsf, String psf){
            this.wsf=wsf;
            this.psf=psf;
        }
    }

    public static Pair heaviestPath(int src, int des, boolean[] vis, ArrayList<Edge>[] graph){
        if(src==des){
            return new Pair(0,src+"");
        }
        vis[src]=true;

        Pair myAns= new Pair();

        for(Edge e:graph[src]){
            int nbr=e.v;

            if(!vis[nbr]){
                Pair recAns = heaviestPath(nbr, des, vis, graph);

                if(recAns.wsf + e.w > myAns.wsf){
                    myAns.psf=src + recAns.psf;
                    myAns.wsf=recAns.wsf + e.w;
                }
            }
        }

        return myAns;
    }

    // lightest path 
    public static void gcc(int src, boolean[] vis, ArrayList<Edge>[] graph){
        vis[src]=true;

        for(Edge e:graph[src]){
            int nbr=e.v;

            if(vis[nbr]==false){
                gcc(nbr, vis, graph);
            }
        }
    }

    // hamiltonian path and cycle ================================================================== 
    public static boolean checkIfConnected(int u, int v,ArrayList<Edge>[] graph){
        for(Edge e:graph[u]){
            int nbr=e.v;

            if(nbr==v) return true;
        }

        return false;
    }

    public static void hamiltonianPath(int src,int osrc, boolean[] vis,ArrayList<Edge>[] graph, int edgeCount,String psf){
        int vtces = graph.length;
        if(edgeCount == vtces - 1){
            System.out.println("Hamiltonian path is "+psf  + src);

            if(checkIfConnected(src,osrc,graph)){
                System.out.println("Hamiltonian cycle is "+psf+src);
            }         
        }

        vis[src]=true;
        for(Edge e:graph[src]){
            if(!vis[e.v]){
                
                hamiltonianPath(e.v, osrc, vis, graph, edgeCount + 1 , psf+src);
            }
        }

        vis[src]=false;
    }

   
    public static void main(String[] args) {
        int n=7;
        
        ArrayList<Edge>[] graph=new ArrayList[n];

        for(int i=0; i<n; i++){
            graph[i]=new ArrayList<>();
        }
// this graph is for hamiltonian example 
        // addEdge(0, 1, graph);   
        // addEdge(0, 3, graph);   
        // addEdge(0, 6, graph);   
        // addEdge(1, 2, graph);   
        // addEdge(1, 5, graph);   
        // addEdge(2, 3, graph);     
        // addEdge(4, 5, graph);   
        // addEdge(4, 6, graph);   
        // addEdge(5, 6, graph);

        addEdge(1, 2, graph);   
        addEdge(1, 3, graph);     
        addEdge(2, 4, graph);     
        addEdge(2, 5, graph);    
        addEdge(3, 4, graph);     
        addEdge(5, 0, graph);     
        addEdge(5, 6, graph);   
        addEdge(0, 6, graph);     


        // addEdge(4, 5, graph);   
        // addEdge(4, 6, graph);   
        // addEdge(5, 6, graph);

        boolean[] visited=new boolean[n]; // false
        // hamiltonianPath(0, 0, visited, graph, 0, "");

        // for(int i=0; i<n; i++){
        //     if(visited[i]==false)
        //         dfs(i,visited,graph);
        // }

        // hasPath(0,6,visited,graph);

        // int comps=0;
        // for(int i=0; i<n; i++){
        //     if(!visited[i]){
        //         comps++;
        //         gcc(i, visited, graph);
        //     }
        // }

        BFS(1, visited, graph);
    }


    // BFS =============================================================

    public static void BFS(int src, boolean[] vis, ArrayList<Edge>[] graph){
        LinkedList<Integer> que=new LinkedList<>();

        que.addLast(src);
        int level=0;

        while(que.size()>0){
            int size=que.size();

            System.out.print("This is level "+level+"  ->     ");

            while(size-->0){
                int vtx = que.removeFirst();

                if(vis[vtx]){
                    System.out.println("There is a cycle in graph");
                    continue;
                }

                System.out.println(vtx);
                vis[vtx]=true;

                for(Edge e: graph[vtx]){
                    if(vis[e.v]==false){
                        que.addLast(e.v);
                    }
                }
            }

            level++;
        }
    }
}