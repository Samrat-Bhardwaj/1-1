import java.util.ArrayList;

public class Implementation {
    public static class MyHeap {
        ArrayList<Integer> data;
        boolean isMaxHeap;

        public MyHeap(){
            data=new ArrayList<>();
            isMaxHeap=false;
        }

        public MyHeap(int[] arr, boolean isMaxHeap){ // nlogn 
            this();
            this.isMaxHeap=isMaxHeap;

            for(int e:arr) this.data.add(e);

            for(int i=data.size()-1; i>=0; i--){
                downHeapify(i);
            }
        }

        private void swap(int i, int j){
            int temp=data.get(i);

            data.set(i,data.get(j));
            data.set(j,temp);
        }

        private int compareTo(int a, int b){ // a=lci/rci, b=pi
            if(isMaxHeap) return data.get(a) - data.get(b);
            return data.get(b) - data.get(a);
        }

        private void downHeapify(int pi){ // log(n)
            int lci=2*pi+1;
            int rci=2*pi+2;

            int mIdx=pi;

            if(lci<data.size() && compareTo(lci,mIdx)>0) mIdx = lci;
            if(rci<data.size() && compareTo(rci,mIdx)>0) mIdx = rci;
            
            if(mIdx!=pi){
                swap(mIdx,pi);
                downHeapify(mIdx);
            }
        }

        private void upHeapify(int ci){ // log(n)
            int pi = (ci-1)/2; 

            if(pi>=0 && compareTo(ci, pi) > 0){
                swap(ci, pi);
                upHeapify(pi);
            }
        }

        // public functions ====================================
        public int size(){
            return this.data.size();
        }

        public int remove(){
            int rv=this.data.get(0);

            swap(0,this.data.size()-1);
            this.data.remove(data.size()-1);

            downHeapify(0);
            return rv;
        }

        public void add(int val){
            this.data.add(val);
            upHeapify(this.data.size()-1);
        }

        public int peek(){
            return this.data.get(0);
        }
    }
    public static void main(String[] args) {
        int[] arr={4,1,2,5,12,5,-2,-5,13,11,9};

        MyHeap pq=new MyHeap(arr,false);

        while(pq.size()>0){
            int a=pq.remove();
            System.out.println(a);
        }
    }    
}
