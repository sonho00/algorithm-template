#include<bits/stdc++.h>
#define FOR(i,a,b) for(ll i=a; i<=b; ++i)
#define ALL(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define endl '\n'
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
using vl=vector<ll>;
using vp=vector<pll>;
const ll INF=1e18;
const ll MAXV=1e4;

ll v,e;
vl adj[MAXV+5];
ll dfn[MAXV+5];
ll low[MAXV+5];
bool fin[MAXV+5];
ll dfsn;
vector<vl> scc;
stack<ll> st;

void dfs(ll i){
    st.push(i);
    low[i]=dfn[i]=++dfsn;
    for(ll nxt:adj[i]){
        if(!dfn[nxt]) dfs(nxt);
        if(!fin[nxt] && low[i]>low[nxt]){
            low[i]=low[nxt];
        }
    }
    if(low[i]==dfn[i]){
        scc.eb();
        ll tmp;
        do{
            tmp=st.top();
            fin[tmp]=1;
            st.pop();
            scc.back().pb(tmp);
        } while(tmp!=i);
        sort(ALL(scc.back()));
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>v>>e;
    while(e--){
        ll a,b;
        cin>>a>>b;
        adj[a].pb(b);
    }
    FOR(i,1,v) if(!dfn[i]) dfs(i);
    sort(ALL(scc),[](vl& a,vl& b){
        return a.front()<b.front();
    });
    cout<<scc.size()<<endl;
    for(vl& v:scc){
        for(ll i:v) cout<<i<<endl;
        cout<<"-1\n";
    }
    return 0;
}