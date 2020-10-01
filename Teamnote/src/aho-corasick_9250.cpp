#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll n;
struct node{
    ll idx[26]={};
    ll fail=0;
    bool fin=0;
};
struct Trie{
    vector<node> v;
    Trie(){v.emplace_back();}
    void insert(string& s){
        ll vi=0;
        ll fail=0;
        for(char& x:s){
            x-='a';
            if(!v[vi].idx[x]){
                v[vi].idx[x]=v.size();
                v.emplace_back();
            }
            vi=v[vi].idx[x];
        }
        v[vi].fin=1;
    }
    void bfs(){
        queue<ll> q;
        q.push(0);
        while(!q.empty()){
            ll top=q.front();
            ll fail=v[top].fail;
            v[top].fin|=v[fail].fin;
            q.pop();
            for(ll i=0; i<26; ++i){
                ll nxt=v[top].idx[i];
                if(!nxt) continue;
                q.push(nxt);
                fail=v[top].fail;
                while(fail && !v[fail].idx[i]) fail=v[fail].fail;
                fail=v[fail].idx[i];
                if(fail!=nxt) v[nxt].fail=fail;
            }
        }
    }
    bool query(string &s){
        ll vi=0;
        for(char& x:s){
            x-='a';
            while(vi && !v[vi].idx[x]) vi=v[vi].fail;
            if(v[vi].idx[x]) vi=v[vi].idx[x];
            if(v[vi].fin) return true;
        }
        return false;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    Trie trie;
    while(n--){
        string s;
        cin>>s;
        trie.insert(s);
    }
    trie.bfs();
    cin>>n;
    while(n--){
        string s;
        cin>>s;
        cout<<(trie.query(s)?"YES":"NO")<<endl;
    }
    return 0;
}