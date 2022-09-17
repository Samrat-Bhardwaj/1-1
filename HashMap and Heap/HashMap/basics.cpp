#include<unordered_map>

int main(){
    unordered_map<string,int> m;  // O(n)
    map<string,int> ma; 

    m["abc"]++;
    m["abc"]--;
    m.erase("abc");

    int a=m["def"];
    // contains 
    if(m.find("abc")==m.end()){
        // not in map
    }

    for(pair<string,int> kv:m){
        cout<<kv.first<<" "<<kv.second;
    }
}