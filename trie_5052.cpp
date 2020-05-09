#include<bits/stdc++.h>
#define FOR(i,a,b) for(ll i=a; i<=b; ++i)
#define ALL(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const ll INF=1e18;
const ll MAX=1e5;
const ll MOD=1e9+7;
const ll LOG=20;

struct node{
    ll cnt;
    bool end;
    vector<ll> idx;
    node(ll n):cnt(0),end(0),idx(vector<ll>(n)){} 
};
struct TRIE{
    ll n;
    vector<node> v;
    TRIE(ll n):n(n),v(vector<node>(1,n)){}
    ll find(string& s){
        ll sz=s.size()-1;
        ll vi=0;
        FOR(i,0,sz){
            ll nxt=v[vi].idx[s[i]];
            if(nxt) vi=nxt;
            else return 0;
        }
        return v[vi].cnt;
    }
    void add(string& s){
        ll sz=s.size()-1;
        ll vi=0;
        ++v[0].cnt;
        FOR(i,0,sz){
            ll nxt=v[vi].idx[s[i]];
            if(!nxt){
                nxt=v[vi].idx[s[i]]=v.size();
                v.eb(n);
            }
            vi=nxt;
            ++v[vi].cnt;
        }
        v[vi].end=1;
    }
};

void tc(){
    TRIE trie(10);
    ll n;
    cin>>n;
    string str[n+5];
    FOR(i,1,n){
        cin>>str[i];
        for(char& ch:str[i]) ch-='0';
        trie.add(str[i]);
    }
    FOR(i,1,n){
        if(trie.find(str[i])){
            cout<<"NO\n";
            return;
        }
    }
    cout<<"YES\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin>>t;
    FOR(i,1,t){
        // cout<<"Case #"<<i<<": "<<'\n';
        tc();
        // cout<<'\n';
    }
    return 0;
}