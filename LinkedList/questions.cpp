#include<priority_queue>

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// always write base case -> if there is 0 or 1 node in the whole linked list
ListNode* middleNode(ListNode* head) {
    if(head==nullptr || head->next==nullptr){
        return head;
    }

    ListNode* slow=head;
    ListNode* fast=head;

    while(fast!=NULL && fast->next!=NULL){
        slow=slow->next;
        fast=fast->next->next;
    }        

    return slow;
}

ListNode* middleNode2(ListNode* head) {
    if(head==nullptr || head->next==nullptr){
        return head;
    }

    ListNode* slow=head;
    ListNode* fast=head;

    while(fast->next!=NULL && fast->next->next!=NULL){
        slow=slow->next;
        fast=fast->next->next;
    }        

    return slow;
}


ListNode* reverseList(ListNode* head) {
    if(head==nullptr || head->next==nullptr){
        return head;
    }        

    ListNode* curr=head;
    ListNode* prev=nullptr;

    while(curr!=nullptr){
        ListNode* currKaNext=curr->next;
        
        curr->next=prev;

        prev=curr;
        curr=currKaNext;
    }

    return prev;
}

// leetcode 234
bool isPalindrome(ListNode* head) {
    if(head==nullptr || head->next==nullptr){
        return true;
    }

    // find mid
    ListNode* midNode=middleNode2(head);
    // create L2
    ListNode* head2=midNode->next;
    midNode->next=nullptr;

    head2=reverseList(head2);

    // compare List 1 and list 2
    ListNode* itr1=head;
    ListNode* itr2=head2;

    while(itr1 && itr2){
        if(itr1->val != itr2->val){
            return false;
        }
        itr1=itr1->next;
        itr2=itr2-> next;
    }

    return true;
}

void deleteNode(ListNode* node) {
    while(node->next && node->next->next){
       node->val=node->next->val;
       node=node->next; 
    }        

    node->val=node->next->val;
    node->next=nullptr;
}

// leetcode 143 ================================================= 
void reorderList(ListNode* head) {
    if(head==nullptr || head->next==nullptr){
        return;
    }

    // find mid
    ListNode* midNode=middleNode2(head);
    // create L2
    ListNode* head2=midNode->next;
    midNode->next=nullptr;

    head2=reverseList(head2);

    // compare List 1 and list 2
    ListNode* itr1=head;
    ListNode* itr2=head2;

    while(itr1 && itr2){
        ListNode* itr1KaNext=itr1->next;
        ListNode* itr2KaNext=itr2->next;

        itr1->next=itr2;
        itr2->next=itr1KaNext;

        itr1=itr1KaNext;
        itr2=itr2KaNext;
    }
}

ListNode* thead1=nullptr;
ListNode* ttail1=nullptr;
ListNode* thead2=nullptr;
ListNode* ttail2=nullptr;

void addFirst(ListNode* node){
    if(thead2==nullptr){
        thead2=ttail2=node;
    } else {
        node->next=thead2;
        thead2=node;
    }
}

void addLast(ListNode* node){
    if(thead1==nullptr){
        thead1=ttail1=node;
    } else {
        ttail1->next=node;
        ttail1=node;
    }
}

ListNode* orderList(ListNode* head){
    if(head==nullptr || head->next==nullptr){
        return head;
    }

    int curr_node=0;
    ListNode* itr=head;

    while(itr){
        ListNode* itrKaNext=itr->next;
        itr->next=nullptr;

        if(curr_node%2==0){
            addLast(itr);
        } else {
            addFirst(itr);
        }

        curr_node++;
        itr=itrKaNext;
    }

    ttail1->next=thead2;
    return thead1;
}

// leetcode 21 ================================================
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* dummy=new ListNode(-1);
    ListNode* itr=dummy;

    while(list1 && list2){
        if(list1->val < list2->val){
            itr->next=list1;
            list1=list1->next;
        } else {
            itr->next=list2;
            list2=list2->next;
        }

        itr=itr->next;
    }        

    if(list1){
        itr->next=list1;
    } 
    if(list2){
        itr->next=list2;
    }

    return dummy->next;
}

// leetcode 148 ============= 
ListNode* sortList(ListNode* head) {
    if(head==nullptr || head->next==nullptr){
        return head;
    }

    ListNode* midNode=middleNode2(head);
    ListNode* head2=midNode->next;
    midNode->next=nullptr;

    return mergeTwoLists(sortList(head),sortList(head2));
}

// leetcode 23 ==============================
ListNode* mergeKLists(vector<ListNode*>& lists, int si, int ei){
    if(si==ei){
        return lists[si];
    }

    int mid=(si+ei)/2;

    return mergeTwoLists(mergeKLists(lists,si,mid), mergeKLists(lists,mid+1,ei));
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    if(lists.size()==0) return nullptr;
    return mergeKLists(lists,0,lists.size()-1);
}

class compare {
    public:
        bool operator()(ListNode* a, ListNode* b){
            return a->val > b->val;  // node with smaller val will be on top
            // return a->val < b->val;  // node with greater val will be on top
        }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    if(lists.size()==0) return nullptr;

    priority_queue<ListNode*,vector<ListNode*>,compare> pq;

    // PriorityQueue<ListNode> pq=new PriorityQueue<>((a,b)->{
    //     return a.val - b.val; // smaller val node on top
    //     return b.val - a.val; // larger node on top
    // });

    for(int i=0; i<lists.size(); i++){
        ListNode* ith=lists[i];
        if(ith)
        pq.push(ith);
    }

    ListNode* dummy=new ListNode(-1);
    ListNode* itr=dummy;

    while(pq.size()){
        ListNode* top=pq.top(); pq.pop();

        itr->next=top;

        if(top->next){
            pq.push(top->next);
        }

        itr=itr->next;
    }

    return dummy->next;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    if(n==0 || head==nullptr){
        return head;
    }        

    ListNode* slow=head;
    ListNode* fast=head;

    while(n--){
        fast=fast->next;
    }

    if(fast==nullptr){
        return head->next;
    }

    while(fast->next){
        slow=slow->next;
        fast=fast->next;
    }

    slow->next=slow->next->next;

    return head;
}

// leetcode 328

// https://practice.geeksforgeeks.org/problems/segregate-even-and-odd-nodes-in-a-linked-list5035/1

// leetcode 92 ==================================
    ListNode* th=nullptr;
    ListNode* tt=nullptr;
    
    void addFirst(ListNode* node){
        if(th==nullptr){
            th=tt=node;
        } else {
            node->next=th;
            th=node;
        }
    }
    
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* itr=head;   
        int curr_node=1;
        ListNode* left_prev=nullptr;
        
        while(itr){
            while(curr_node>=left && curr_node<=right){
                ListNode* itrKaNext=itr->next;
                itr->next=nullptr;
                addFirst(itr);
                
                itr=itrKaNext;
                curr_node++;
            }
            
            if(curr_node>right){
                if(left_prev==nullptr){ // head
                    head=th;
                } else {
                    left_prev->next=th;
                }
                
                tt->next=itr;
                break;
            } else if(curr_node<left){
                 left_prev=itr;
                itr=itr->next;
                curr_node++;
            }
        }
        
        return head;
    }

// linked list cycle ==============================

bool hasCycle(ListNode *head) {
        if(head==nullptr || head->next==nullptr){
            return false;
        }

        ListNode* slow=head;
        ListNode* fast=head;   

        while(fast && fast->next){
            slow=slow->next;
            fast=fast->next->next;
            
            if(slow==fast) return true;
        }     
        
        return false;
    }

// leetcode 142 ==================================================== 
// floyd cycle method
ListNode *detectCycle(ListNode *head) {
    if(head==nullptr || head->next==nullptr){
        return nullptr;
    }

    ListNode* slow=head;
    ListNode* fast=head;

    while(fast && fast->next){
        slow=slow->next;
        fast=fast->next->next;
        
        if(slow==fast) break;
    } 

    if(slow!=fast) return nullptr;

    fast=head;
    while(slow!=fast){
        slow=slow->next;
        fast=fast->next;
    }

    return slow;
}

// leetcode 160 =================================================================
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if(headA == nullptr || headB==nullptr){
        return nullptr;
    }        

    ListNode* tail=headA;
    ListNode* curr=headA;

    while(curr){
        tail=curr;
        curr=curr->next;
    }

    tail->next=headB;

    ListNode* ans=detectCycle(headA);

    tail->next=nullptr;
    return ans;
}

// leetcode 83 ====================

ListNode* deleteDuplicates(ListNode* head) {
        if(head==nullptr || head->next==nullptr){
            return head;
        }
        
        ListNode* curr=head;
     
        while(curr && curr->next){
            if(curr->val==curr->next->val){
                ListNode* currKaNext=curr->next;
                curr->next=nullptr;
                curr->next=currKaNext->next;
                
                currKaNext->next=nullptr; // not neccessory
            } 
            if(curr->next && curr->val!=curr->next->val){
                curr=curr->next;
            }
        }
        
        return head;
    }


// leetcode 82 ========================================== 
ListNode* deleteDuplicates(ListNode* head) {
    if(head==nullptr || head->next==nullptr){
        return head;
    }

    ListNode* dummy=
}

// leetcode 138 ======================================================================
Node* extractList(Node* head){
    Node* dummy=new ListNode(0);
    Node* itr=dummy;
    Node* curr=head;

    while(curr){
        itr->next=curr->next;
        curr->next=curr->next->next;

        itr=itr->next;
        curr=curr->next;
    }

    return dummy->next;
}

Node* copyRandomList(Node* head) {
    
}

// leetcode 25 ================================================== 
int length(ListNode* head){
        ListNode* temp=head;

        int ans=0;
        while(temp){
            ans++;
            temp=temp->next;
        }

        return ans;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head==nullptr || head->next==nullptr || k<=1){
            return head;
        }

        int l=length(head);

        if(l<k){
            return head;
        }

        ListNode* curr=head;

        ListNode* oh=nullptr;
        ListNode* ot=nullptr;

        int K=k;

        while(curr && l>=k){
            while(K-- > 0){
                ListNode* currKanext=curr->next;
                curr->next=nullptr;

                addFirst(curr);
                curr=currKanext;
            }

            if(oh==nullptr){
                oh=thead2;
                ot=ttail2;
            } else {
                ot->next=thead2;
                ot=ttail2;
            }

            thead2=nullptr;
            ttail2=nullptr;

            l-=k;
            K=k;
        }

        ot->next=curr;
        return oh;
    }

int main(){

}