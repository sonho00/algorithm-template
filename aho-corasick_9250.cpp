#include<bits/stdc++.h>
using namespace std;

struct TRIE{
    struct node{
        int idx[26];
        bool ans;
    };
    TRIE():v(1){}
    vector<node> v;
    void push(string& s){
        int vi=0;
        for(char x:s){
            x-='a';
            if(!v[vi].idx[x]){
                v[vi].idx[x]=v.size();
                v.emplace_back();
            }
            vi=v[vi].idx[x];
        }
        v[vi].ans=1;
    }
    void solve(){
        queue<pair<int,int>> q;
        for(int x:v[0].idx){
            if(x) q.emplace(x,0);
        }
        while(!q.empty()){
            auto[vi,prv]=q.front();
            q.pop();
            v[vi].ans|=v[prv].ans;
            for(int i=0; i<26; ++i){
                if(v[vi].idx[i]) q.emplace(v[vi].idx[i],v[prv].idx[i]);
                else v[vi].idx[i]=v[prv].idx[i];
            }
        }
    }
    bool qry(string& s){
        int vi=0;
        for(char x:s){
            vi=v[vi].idx[x-'a'];
            if(v[vi].ans) return 1;
        }
        return 0;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    TRIE trie;
    string s;
    for(int i=0; i<n; ++i){
        cin>>s;
        trie.push(s);
    }
    trie.solve();
    int q;
    cin>>q;
    for(int i=0; i<q; ++i){
        cin>>s;
        if(trie.qry(s)) cout<<"YES\n";
        else cout<<"NO\n";
    }
}