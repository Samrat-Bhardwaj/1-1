public class bst {
    // leetcode 1008 =====================================================
    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode() {}
        TreeNode(int val) { this.val = val; }
        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }

    public TreeNode build(int[] preorder, int si, int ei){
        if(si > ei) return null;
        if(si == ei) return new TreeNode(preorder[si]);
        
        TreeNode root=new TreeNode(preorder[si]);
        int idx=si+1;
        
        while(idx <= ei && preorder[idx] < root.val){
            idx++;
        }
        
        int count= idx - si - 1;
        root.left = build(preorder,si+1,si+count);
        root.right=build(preorder,idx,ei);
        
        return root;
    }
    public TreeNode bstFromPreorder(int[] preorder) {
        int n=preorder.length;
        
        return build(preorder,0,n-1);
    }

    // method 2 ====================================================================
    int idx=0;
    public TreeNode construct(int[] preorder, int lbound, int rbound){
        if(idx >= preorder.length || preorder[idx] <= lbound || preorder[idx] >= rbound){
            return null;
        }
        
        TreeNode root=new TreeNode(preorder[idx]);
        idx++;
        
        root.left=construct(preorder,lbound,root.val);
        root.right=construct(preorder,root.val,rbound);
        
        return root;
    }
    public TreeNode bstFromPreorder(int[] preorder) {
        return construct(preorder,-1001,1001);
    }
}

// leetcode 669 ================================================== 
public TreeNode trimBST(TreeNode root, int low, int high) {
    if(root==null) return null;
    
    if(root.val < low){
        return trimBST(root.right,low,high);
    } else if(root.val > high){
        return trimBST(root.left,low,high);
    } else {
        root.left=trimBST(root.left,low,high);
        root.right=trimBST(root.right,low,high);
    }
    
    return root;
}

// leet 109 ==============================
public ListNode getMid(ListNode head,ListNode tail){
    ListNode slow=head;
    ListNode fast=head;
    
    while(fast!=tail && fast.next!=tail){
        slow=slow.next;
        fast=fast.next.next;
    }
    
    return slow;
}

public TreeNode makeBST(ListNode head,ListNode tail){ // tail = next point of actual tail 
    if(head==tail){
        return null;
    }
    
    ListNode mid=getMid(head,tail);
    
    TreeNode root=new TreeNode(mid.val);
    
    root.left=makeBST(head,mid);
    root.right=makeBST(mid.next,tail);
    
    return root;
}

public TreeNode sortedListToBST(ListNode head) {
    if(head==null) return null;
    return makeBST(head,null);
}