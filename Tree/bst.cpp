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