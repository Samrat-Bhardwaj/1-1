struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

TreeNode* construct(vector<int>& inorder, int si, int ei){ // creating a balanced tree 
    if(si>ei) return nullptr;
    if(si==ei) return new TreeNode(inorder[si]);

    int mid=(si+ei)/2;

    TreeNode* root=new TreeNode(inorder[mid]);

    root->left=construct(inorder,si,mid-1);
    root->right=construct(inorder,mid+1,ei);

    return root;
}

  TreeNode* bstFromInorder(vector<int>& inorder) {
        return construct(inorder,0,inorder.size()-1);
  }

int max(TreeNode* root){
    TreeNode* curr=root;

    while(curr->right!=nullptr){
        curr=curr->right;
    }

    return curr->val;
}

int min(TreeNode* root){
    TreeNode* curr=root;

    while(curr->left!=nullptr){
        curr=curr->left;
    }

    return curr->val;
}

bool find(TreeNode* root, int data){
    TreeNode* curr=root;

    while(curr){
        if(curr->val < data){
            curr=curr->right;
        } else if(curr-> val > data){
            curr=curr->left;
        } else {
            return true;
        }
    }

    return false;
}
// leet 701 =======================================================
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if(root==nullptr){
        return new TreeNode(val);
    }

    if(root->val < val){
        root->right=insertIntoBST(root->right,val);
    } else {
        root->left=insertIntoBST(root->left,val);
    }

    return root;
}

// leet 450 ===================================================== 
int getMin(TreeNode* root){
    TreeNode* curr=root;

    while(curr->left!=nullptr){
        curr=curr->left;
    }

    return curr->val;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if(root==nullptr) return nullptr;
    
    if(root->val < key){
        root->right=deleteNode(root->right,key);
    } else if(root->val > key){
        root->left=deleteNode(root->left,key);
    } else {
        // if its a leaf node
        if(root->left==nullptr && root->right==nullptr){
            return nullptr;
        }
        
        // if it has one child 
        if(root->left==nullptr){
            return root->right;
        }
        if(root->right==nullptr){
            return root->left;
        }
        
        // if it has 2 children
        int justLarger=getMin(root->right);
        
        root->val=justLarger;
        root->right=deleteNode(root->right,justLarger);
    }
    
    return root;
}

// leetcode 98 ======================================================== 
bool isBST(TreeNode* root, TreeNode*& prev){
    if(!root) return true;
    
    if(!isBST(root->left,prev)) return false;
    
    if(prev!=nullptr && prev->val >= root->val) return false;
    prev=root;
    
    if(!isBST(root->right,prev)) return false;
    
    return true;
}

bool isValidBST(TreeNode* root) {
    TreeNode* prev=nullptr;
    return isBST(root,prev);
}

// method 2 ========================================

class bstPair {
    public:
        bool isBST=true;
        long minV=1e15;
        long maxV=-1e15;
        
        bstPair(){
            
        }
    
        bstPair(bool isBST, long minV, long maxV){
            this->isBST=isBST;
            this->minV=minV;
            this->maxV=maxV;
        }
};

bstPair* check(TreeNode* root){
    if(root==nullptr) return new bstPair(true,1e15,-1e15);
    
    bstPair* lp=check(root->left);
    bstPair* rp=check(root->right);
    
    bstPair* ansPair=new bstPair();
    if(!lp->isBST || !rp->isBST || lp->maxV >= root->val || rp->minV <=root->val){
        ansPair->isBST=false;
        return ansPair;
    }
    
    ansPair->minV=min(lp->minV,(long)root->val);
    ansPair->maxV=max(rp->maxV,(long)root->val);
    
    return ansPair;
}

bool isValidBST(TreeNode* root) {
    return check(root)->isBST;
}

// leetcode 1373 =============================================================== 

// leet 109 =================================== 

// leetcode 1038 ================================================== 
void makeGreater(TreeNode* root, int& sum){
    if(!root) return;
    
    makeGreater(root->right,sum);
    
    sum+=root->val;
    root->val=sum;
    
    makeGreater(root->left,sum);
}

TreeNode* bstToGst(TreeNode* root) {
    int sum=0;
    
    makeGreater(root,sum);
    return root;
}

 public ListNode getMid(ListNode head,ListNode tail){
        ListNode slow=head;
        ListNode fast=head;
        
        while(fast!=tail && fast.next!=tail){
            slow=slow.next;
            fast=fast.next.next;
        }
        
        return slow;
    }
    
// leetcode 89 =============================================================== 

TreeNode* a=nullptr;
TreeNode* b=nullptr;
TreeNode* prev=nullptr;

bool recoverTree2(TreeNode* root){
    if(!root) return false;
    
    if(recoverTree2(root->left)) return true;
    
    if(prev!=nullptr && prev->val > root->val){
        b=root;
        if(a==nullptr){
            a=prev;
        } else {
            return true;
        }
    }
    
    prev=root;
    if(recoverTree2(root->right)) return true; // not compulsory to stop iterating once we get a && b
                                                // jst to save some time 
    
    return false;
}
void recoverTree(TreeNode* root) {
    recoverTree2(root);
    
    if(a){
        int temp=a->val;
        a->val=b->val;
        b->val=temp;
    }
    
}

// leet 230 ================================================================ 

void addAllLeft(TreeNode* root,stack<TreeNode*>& st){
    TreeNode* curr=root;
    
    while(curr){
        st.push(curr);
        curr=curr->left;
    }
}

int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode*> st;
    addAllLeft(root,st);
    
    while(k-- > 1){
        TreeNode* t=st.top(); st.pop();
        
        addAllLeft(t->right,st); // adding just larger elements
    }
    
    return st.top()->val;
}

// leetcode 653 ==========================================
addAllRight(TreeNode* root, stack<TreeNode*> st){
    while(curr){
        st.push(curr);
        curr=curr->right;
    }
}

bool findTarget(TreeNode* root, int k) {
        stack<TreeNode*> sl,sr;
        
        TreeNode* curr=root;
        addAllLeft(root,sl);
        addAllRight(root,sr);

        while(sl.size() && sr.size()){
            int sum=sl.top()->val+sr.top()->val;
            if(sum==k && sl.top()!=sr.top()) return true;
            
            if(sum>k){
                TreeNode* tr=sr.top();
                sr.pop();
                addAllRight(tr->left);
            } else {
                TreeNode* tl=sl.top();
                sl.pop();
                tr=tr->right;
                addAllLeft(tl->right);   
            }
        }
        return false;
    }

// leetcode 173 =============================================================== 
class BSTIterator {
public:
    stack<TreeNode*> st;
    void addAllLeft(TreeNode* root){
        TreeNode* curr=root;

        while(curr){
            st.push(curr);
            curr=curr->left;
        }
    }
    
    BSTIterator(TreeNode* root) {
        addAllLeft(root);
    }
    
    int next() {
        TreeNode* t=st.top(); st.pop();
        addAllLeft(t->right);
        
        return t->val;
    }
    
    bool hasNext() {
        return st.size()!=0;
    }
};

// lintcode 448 ========================================================
void traverse(TreeNode* root, TreeNode*& prev, TreeNode* p, TreeNode*& succ){
    if(!root) return;

    traverse(root->left,prev,p,succ);
    
    if(prev==p){
        succ=root;
    }

    prev=root;
    traverse(root->right,prev,p,succ);
}
TreeNode * inorderSuccessor(TreeNode * root, TreeNode * p) {
    // write your code here
    TreeNode* prev=nullptr;
    TreeNode* succ=nullptr;
    traverse(root,prev,p,succ);
    return succ;
}

// try with Morris traversal 

// inorder successor 2 (leetcode 510 ) ==================================================================

TreeNode* inorderSuccessor(TreeNode* node){
    if(node->right){
        TreeNode* succ=node->right;

        while(succ->left){
            succ=succ->left;
        }
        return succ;
    }

    // while(curr->parent && curr->parent->val < node->val){
    //     curr=curr->parent;
    // }

    // if(curr->val < node->val) return nullptr;
    // return curr;

    while(curr->parent){
        if(curr->parent->left == curr){
            return curr->parent;
        }

        curr=curr->parent;
    }

    return nullptr;
}