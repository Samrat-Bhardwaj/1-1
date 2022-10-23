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


// left view of a tree ================================================

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};

vector<int> leftView(Node *root) {
    queue<Node*> q;

    que.push(root);

    int level=0;
    vector<int> ans;

    while(que.size()){
        int size=que.size();

        while(size--){
            Node* top=que.pop();

            if(level==ans.size()){
                que.add(top->data);
            }

            if(top->left){
                que.push(top->left);
            }

            if(top->right){
                que.push(top->right);
            }
        }
        level++;
    }

    return ans;
}

void rec_left_view(Node* root, vector<int>& ans, int level){
    if(root==nullptr) return;

    if(level==ans.size()){
        ans.push_back(root->data);
    }

    rec_left_view(root->left,ans,level+1);
    rec_left_view(root->right,ans,level+1);
}

vector<int> leftView(Node *root) {
    vector<int> ans;

    rec_left_view(root,ans,0);
    return ans;
}


// https://practice.geeksforgeeks.org/problems/right-view-of-binary-tree/1

void rec_right_view(Node* root, vector<int>& ans, int level){
    if(root==nullptr) return;

    if(level==ans.size()){
        ans.push_back(root->data);
    }

    rec_right_view(root->right,ans,level+1);
    rec_right_view(root->left,ans,level+1);
}

vector<int> rightView(Node *root){
    vector<int> ans;
    rec_right_view(root,ans,0);

    return ans;
}

// vertical order ==========================================================

void getWidth(TreeNode* root,vector<int>& minMax, int vl){
    if(root==nullptr) return;

    minMax[0]=min(vl,minMax[0]);
    minMax[1]=max(vl,minMax[1]);

    getWidth(root->left,minMax,vl-1);
    getWidth(root->right,minMax,vl+1);
}

vector<vector<int>> verticalOrder(TreeNode* root){
    vector<int> minMax(2,0); // { min_vertical_level, max_vertical_level }

    getWidth(root,minMax,0);

    int width=minMax[1] - minMax[0] + 1;

    int shift=-minMax[0];

    vector<vector<int>> ans(width);

    queue<pair<TreeNode*,int>> que; // node vs vertical level
    que.push({root,0});

    while(que.size()){
        int s=que.size();

        while(s--){
            pair<TreeNode*,int> top=que.front(); que.pop();

            TreeNode* t=top.first;
            int vl=top.second;

            int idx = vl + shift;
            ans[idx].push_back(t->val);

            if(t->left){
                que.push({t->left,vl-1});
            }
            if(t->right){
                que.push({t->right,vl+1});
            }
        }
    }
}

// https://practice.geeksforgeeks.org/problems/print-a-binary-tree-in-vertical-order/1

// vertical sum 
// https://practice.geeksforgeeks.org/problems/vertical-sum/1

// bottom view 
// https://practice.geeksforgeeks.org/problems/bottom-view-of-binary-tree/1

// top view sum
// https://www.geeksforgeeks.org/sum-of-nodes-in-top-view-of-binary-tree/

// diagonal order  ============================================================== 

// try with level order (may not work)
void diagonalWidth(Node* root, int& min_vl, int vl){
    if(!root) return;
    
    min_vl=max(min_vl,vl);
    
    diagonalWidth(root->left,min_vl,vl+1);
    diagonalWidth(root->right,min_vl,vl);
}

void getDiagonalView(Node* root,vector<vector<int>>& ans, int vl){
    if(!root) return;
    
    ans[vl].push_back(root->data);
    
    getDiagonalView(root->left,ans,vl+1);
    getDiagonalView(root->right,ans,vl);
}

vector<int> diagonal(Node *root)
{
    int min_vl=0;
    diagonalWidth(root,min_vl,0);    
    
    vector<vector<int>> ans(min_vl+1);
    
    getDiagonalView(root,ans,0);
    
    vector<int> res;
    for(int i=0; i<=min_vl; i++){
        for(int e:ans[i]){
            res.push_back(e);
        }
    }
    
    return res;
}

// all solutions (predecessor, successor, ceil, floor)

class allPair {
    public:
    Node* prev;
    Node* pred; 
    Node* succ;

    int ceil;
    int floor;
};

void findAllSolutions(Node* root, int data, allPair* ans){
    if(!root) return;

    if(root->data < data){ // maximum of all values smaller than data
        ans->floor=max(ans->floor,root->data);
    } 

    if(root->data > data){ // minimum of all values greater than data
        ans->ceil=min(ans->ceil,root->data);
    }

    findAllSolutions(root->left,data,ans);

    if(root->data==data){  // predecessor
        ans->pred = ans->prev;
    }

    if(ans->prev!=nullptr && ans->prev->data == data){ // successor 
        ans->succ = root;
    }

    ans->prev=root;
    findAllSolutions(root->right,data,ans);
}


// Morris traversal (O(1) space traversal) ==========================================================

Node* rightMost(Node* root, Node* curr){
    while(root->right!=nullptr && root->right!=curr){
        root=root->right;
    }

    return root;
}

vector<Node*> morrisInorderTraversal(Node* root){
    Node* curr=root;
    vector<Node*> inorder;

    while(curr!=nullptr){
        Node* leftNode=curr->left;

        if(leftNode==nullptr){
            inorder.push_back(curr);
            curr=curr->right;
        } else {
            Node* rm=rightMost(leftNode,curr);

            if(rm->right==nullptr){ // thread creation
                rm->right=curr;
                curr=leftNode;
            } else { // rm->right == curr (thread break)
                rm->right=nullptr;
                inorder.push_back(curr);
                curr=curr->right;
            }
        }
    }

    return inorder;
}


vector<Node*> morrisPreTraversal(Node* root){
    Node* curr=root;
    vector<Node*> preorder;

    while(curr!=nullptr){
        Node* leftNode=curr->left;

        if(leftNode==nullptr){
            preorder.push_back(curr);
            curr=curr->right;
        } else {
            Node* rm=rightMost(leftNode,curr);

            if(rm->right==nullptr){ // thread creation
                rm->right=curr;
                preorder.push_back(curr);
                curr=leftNode;
            } else { // rm->right == curr (thread break)
                rm->right=nullptr;
                
                curr=curr->right;
            }
        }
    }

    return preorder;
}

// iterative post, in, pre using stack ===========================================

class tPair {
    public: 
    Node* node;
    bool selfDone;
    bool leftDone;
    bool rightDone;

    tpair(Node* node, bool selfDone, bool leftDone, bool rightDone){
        this->node=node;
        this->selfDone=selfDone;
        this->leftDone=leftDone;
        this->rightDone=rightDone;
    }
};

void allTraversals(Node* root){
    Stack<tPair*> st;

    vector<Node*> preorder;
    vector<Node*> inorder;
    vector<Node*> postorder;

    tPair* base=new tPair(root,false,false,false);
    st.push(base);

    while(st.size()!=0){
        tPair tp=st.top();

        if(tp->selfDone==false){
            preorder.push_back(tp->node);
            tp->selfDone=true;
        } else if(tp->leftDone==false){
            tp->leftDone=true;
            if(tp->node->left) st.push(new tPair(tp->node->left,false,false,false));
        } else if(tp->rightDone==false){
            inorder.push(tp->node);
            tp->rightDone=true;
            if(tp->node->right) st.push(new tPair(tp->node->right,false,false,false));
        } else {
            postorder.push_back(tp->node);
            st.pop();
        }
    }
}


// 22nd october ==================================================================================

// leet 105 ======================================= 
TreeNode* buildTree(vector<int>& preorder, int prsi, int prei,vector<int>& inorder, int insi,int inei){
    if(prsi > prei) return nullptr;
    
    TreeNode* root=new TreeNode(preorder[prsi]);
    
    int idx=insi;
    
    while(inorder[idx]!=root->val){
        idx++;
    }
    
    int count=idx-insi;
    
    root->left=buildTree(preorder,prsi+1,prsi+count,inorder,insi,idx-1);
    root->right=buildTree(preorder,prsi+count+1,prei,inorder,idx+1,inei);
    
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return buildTree(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1);
}


// https://practice.geeksforgeeks.org/problems/maximum-path-sum/1 ======================================= 

// {left to node max sum, max ans}
vector<int> rec(Node* root){
    if(!root){
        return {(int)(-1e8),(int)(-1e8)};
    }
    
    if(root->left==nullptr && root->right==nullptr){
        return {root->data,(int)(-1e8)};
    }
    
    vector<int> lans=rec(root->left);
    vector<int> rans=rec(root->right);
    
    int lsum=lans[0]; // leaf to node max sum
    int rsum=rans[0]; // leaf to node max sum
    
    int lmax=lans[1];
    int rmax=rans[1];
    
    vector<int> myAns(2,0);
    
    myAns[0]=max(lsum,rsum)+root->data;
    myAns[1]=max(lmax,max(rmax,lsum+rsum+root->data));
    
    return myAns;
}
int maxPathSum(Node* root)
{
    vector<int> ans=rec(root);
    if(root->left==nullptr || root->right==nullptr) return max(ans[0],ans[1]);
    return ans[1];
}

// leetcode 124 ========================================================================= 

//{max path sum, max ans}
vector<int> solve(TreeNode* root){
    if(!root) return {(int)(-1e8),(int)(-1e8)};
    
    vector<int> lans=solve(root->left);
    vector<int> rans=solve(root->right);
    
    int lps=lans[0]; // left max path sum
    int rps=rans[0]; // right max path sum
    
    int lam=lans[1]; // left subtree max ans
    int ram=rans[1]; // right subtree max ans
    
    int mps=max(lps+root->val,max(rps+root->val,root->val)); // my max path sum 
    // three scenarios => lpath + root.val
    // rpath + root.val
    // or we can start path from root.val
    
    int mam=max(mps,max(lps+rps+root->val,max(lam,ram)));
    // for max ans => all the above 3 scenarios 
    // lpath + rpath + root.val 
    // l max ans 
    // r max ans
    
    return {mps,mam};
}

int maxPathSum(TreeNode* root) {
    return solve(root)[1];
}