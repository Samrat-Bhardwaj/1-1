import java.util.PriorityQueue;

public class basics {
    public static void main(String[] args) {
        PriorityQueue<Integer> pq=new PriorityQueue<>((a,b)->{
            return a-b; // default order -> min pq;
            // return b-a; // max pq;
        });
    }    
}
