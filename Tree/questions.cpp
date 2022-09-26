struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}

// node to root Path ====================
bool nodeToRootPath(TreeNode* root, TreeNode* p,vector<TreeNode*>& ntr){
    if(root==nullptr) return false;
    if(root==p){
        ntr.push_back(p);
        return true;
    }
    
    bool left=nodeToRootPath(root->left,p,ntr);
    bool right=nodeToRootPath(root->right,p,ntr);
    
    if(left || right){
        ntr.push_back(root);
        return true;
    }
    
    return false;
}

// node to root Path 2 =========================================================
vector<TreeNode*> nodeToRootPath(TreeNode* root, TreeNode* p){
    if(root==nullptr) return {};
    if(root==p){
        return {root};
    }
    
    vector<TreeNode*> left=nodeToRootPath(root->left,p);
    if(left.size()){
        left.push_back(root);
        return left;
    }
    
    vector<TreeNode*> right=nodeToRootPath(root->right,p);
    if(right.size()){
        right.push_back(root);
        return right;
    }
    
    return {};
}

// lowest common ancestor ===========
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    vector<TreeNode*> ntr1;
    nodeToRootPath(root,p,ntr1);
    vector<TreeNode*> ntr2;
    nodeToRootPath(root,q,ntr2);
    
    int i=ntr1.size()-1;
    int j=ntr2.size()-1;
    
    while(i>=0 && j>=0 && ntr1[i]==ntr2[j]){
        i--;
        j--;
    }
    
    return ntr1[i+1]; // ntr2[j+1];
}

// LCA with O(1) space ============================================================= 
bool lca_better(TreeNode* root, TreeNode* d1, TreeNode* d2,TreeNode*& lca){
    if(root==nullptr) return false;
    if(lca!=nullptr) return true;
    
    bool self=false;
    if(root==d1 || root==d2) self=true;
    
    bool left=lca_better(root->left,d1,d2,lca);
    bool right=lca_better(root->right,d1,d2,lca);
    
    if(lca!=nullptr) return true;
    if((left && right) || (self && left) || (self && right)) lca=root;
    
    return self || left || right;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* lca=nullptr;
    lca_better(root,p,q,lca);
    
    return lca;
}

// https://practice.geeksforgeeks.org/problems/k-distance-from-root/1 
vector<int> Kdistance(struct Node *root, int k){
    if(root==nullptr) return {};
    
    if(k==0){
        return {root->data};
    }
    
    vector<int> ans;
    vector<int> left=Kdistance(root->left,k-1);
    vector<int> right=Kdistance(root->right,k-1);
    
    for(int e:left){
        ans.push_back(e);
    }
    
    for(int e:right){
        ans.push_back(e);
    }
    
    return ans;
}

// print k level down from any node ===================================

void kdown(TreeNode* root, TreeNode* node, int k, vector<TreeNode*> ans,bool find){
    if(root==nullptr) return;

    if(k==0){
        ans.push_back(root);
        return;
    }

    if(root==node) find=true;

    if(find){
        kdown(root->left,node,k-1,ans,find);
        kdown(root->right,node,k-1,ans,find);
    } else {
        kdown(root->left,node,k,ans,find);
        kdown(root->right,node,k,ans,find);
    }
}

// K far away (leet 863 ========================================================== )
void klevelDown(TreeNode* root, TreeNode* blocker, int k,vector<int>& ans){
    if(root==nullptr || root==blocker) return;

    if(k==0){
        ans.push_back(root->val);
    }

    klevelDown(root->left,blocker,k-1,ans);
    klevelDown(root->right,blocker,k-1,ans);
}

vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    vector<TreeNode*> ntr=nodeToRootPath(root,target);

    vector<int> ans;
    TreeNode* blocker=nullptr;

    for(int i=0; i<ntr.size(); i++){
        TreeNode* currNode=ntr[i];

        klevelDown(currNode,blocker,k-i,ans);
        blocker=currNode;
    }

    return ans;
}

// k far away 2 (in O(1) space) ========================================================================== 


// diameter =======================================================
int height(TreeNode* root){
    return root == nullptr ? -1 : max(height(root->left),height(root->right)) + 1;
}

// method O(n^2) ============================================================= 
int diameter(TreeNode* root){
    if(root==nullptr){
        return -1;
    }

    int lh=height(root->left);
    int rh=height(root->right);

    int myDia=lh+rh+2;

    int ldia=diameter(root->left); // left subtree ka max dia 
    int rdia=diameter(root->left); // right subtree ka max dia

    int diameter=max(myDia,max(ldia,rdia));

    return diameter;
}


// diameter 2 in O(1) time with global variable ===================================
int dia2=0;

int height2(TreeNode* root){
    if(root==nullptr) return -1;

    int lh=height2(root->left);
    int rh=height2(root->right);

    int myDia = lh + rh +2;
    dia2=max(dia2,myDia);

    return max(lh,rh)+1;
}

// diameter 2 in O(1) time with without global variable ===================================
vector<int> heightDia(TreeNode* root){
    if(root==nullptr){
        return {-1,-1};
    }

    vector<int> lhd=heightDia(root.left);
    vector<int> rhd=heightDia(root.left);

    int height=max(lhd[0],rhd[0]) + 1;
    int myDia=lhd[0] + rhd[0] + 2;

    int dia=max(myDia,max(lhd[1],rhd[1]));

    return {height,dia};
}


// BFS / Level-order traversal ============================================================

