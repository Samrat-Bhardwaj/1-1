import java.util.LinkedList;

import apple.laf.JRSUIUtils.Tree;

public class questions {
    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode(int x) { val = x; }
    }

    public int size(TreeNode root){
        return root==null ? 0 : size(root.left) + size(root.right) + 1;
    }

    public int height(TreeNode root){
        if(root==null){
            return -1;
        }

        int lh=height(root.left);
        int rh=height(root.right);

        return Math.max(lh,rh) + 1;
    }

    public boolean find(TreeNode root, TreeNode data){
        if(root==null) return false;

        if(root==data) return true;

        return find(root.left, data) || find(root.right, data);
    }

    // height of tree in O(n) ==========================================
    int dia2=0;

    public int height2(TreeNode root){
        if(root==null) return -1;

        int lh=height2(root.left);
        int rh=height2(root.right);

        int myDia = lh + rh +2;
        dia2=Math.max(dia2,myDia);
        
        return Math.max(lh,rh)+1;
    }

    public int[] heightDia(TreeNode root){
        if(root==null){
            return new int[]{-1,-1};
        }

        int []lhd=heightDia(root.left);
        int []rhd=heightDia(root.left);

        int height=Math.max(lhd[0],rhd[0]) + 1;
        int myDia=lhd[0] + rhd[0] + 2;

        int dia=Math.max(myDia,Math.max(lhd[1],rhd[1]));

        return new int[]{height,dia};
    }

// BFS / Level-order traversal ============================================================
    public void BFS(TreeNode root){
        LinkedList<TreeNode> que=new LinkedList<>();

        que.add(root);

        while(que.size()>0){
            TreeNode top=que.removeFirst();
            System.out.print(top+" ");
            if(top.left!=null){
                que.addLast(top.left);
            }

            if(top.right!=null){
                que.addLast(top.right);
            }
        }
    }

    // BFS2 =============================================
    public void BFS2(TreeNode root){
        LinkedList<TreeNode> que=new LinkedList<>();

        que.addLast(root);
        int level=0;

        while(que.size()>1){
            TreeNode top=que.removeFirst();
            if(top==null){
                System.out.println("Moving to level "+level);
                que.addLast(top);
                level++;
                continue;
            } else {
                System.out.print(top+" ");
            }
            
            if(top.left!=null){
                que.addLast(top.left);
            }

            if(top.right!=null){
                que.addLast(top.right);
            }
        }
    }


    public void BFS3(TreeNode root){
        LinkedList<TreeNode> que=new LinkedList<>();

        que.add(root);
        int level=0;

        while(que.size()>0){
            int size=que.size();

            System.out.println("Printing level "+level);
            while(size-->0){
                TreeNode top=que.removeFirst();
                System.out.print(top.val+" ");

                if(top.left!=null){
                    que.addLast(top.left);
                }

                if(top.right!=null){
                    que.addLast(top.right);
                }
            }

            level++;
        }
    }

// vertical order ===============================================

ArrayList<TreeNode>[] 
    public static void main(String[] args) {
        
    }
}


// 22nd october ==================================================================================
// leet 106 ===============================================================================

public TreeNode build(int[] inorder, int insi, int inei, int[] postorder, int posi, int poei){
    if(insi > inei) return null;
    
    TreeNode root=new TreeNode(postorder[poei]);
    
    int idx=insi;
    while(inorder[idx]!=root.val){
        idx++;
    }
    
    int count=idx-insi; // left elements count;
    
    root.left=build(inorder,insi,idx-1,postorder,posi,posi+count-1);
    root.right=build(inorder,idx+1,inei,postorder,posi+count,poei-1);
    
    return root;
}

public TreeNode buildTree(int[] inorder, int[] postorder) {
    int n=inorder.length;
    
    return build(inorder,0,n-1,postorder,0,n-1);
}

// leetcode 889 ================================================================== 
public TreeNode build(int[] preorder, int prsi, int prei, int[] postorder, int posi, int poei){
    if(prsi > prei) return null;
    if(prsi == prei) return new TreeNode(preorder[prsi]);
    
    TreeNode root=new TreeNode(preorder[prsi]);
    
    int idx=posi;
    while(postorder[idx] != preorder[prsi+1]){ // finding left subtree root
        idx++;
    }
    
    int count= idx - posi + 1;
    
    root.left=build(preorder,prsi+1,prsi+count,postorder,posi,idx);
    root.right=build(preorder,prsi+count+1,prei,postorder,idx+1,poei-1);
    
    return root;
}
public TreeNode constructFromPrePost(int[] preorder, int[] postorder) {
    int n=preorder.length;
    
    return build(preorder,0,n-1,postorder,0,n-1);
}