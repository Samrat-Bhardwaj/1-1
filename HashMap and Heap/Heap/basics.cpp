class comp {
    public:
    bool operator()(vector<int>& a, vector<int>& b){
        return a[0] < b[0]; // default order -> max
        // return a[0] > b[0]; // minPQ  
    }
}

int main(){
    priority_queue<int> pq; // maxpq
    priority_queue<int,vector<int>,greater<int>> pq2; // maxpq
    priority_queue<string,vector<string>,greater<string>> pq2; // maxpq

    priority_queue<vector<int>,vector<vector<int>>,comp> pq3;
    return 0;
}