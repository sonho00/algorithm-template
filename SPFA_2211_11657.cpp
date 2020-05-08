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

struct graph{
    ll n;
    vector<vector<pll>> adj;
    vector<ll> dist,par;
    graph(ll n):n(n),adj(vector<vector<pll>>(n+5)){}
    bool spfa(ll idx){
        dist=vector<ll>(n+5,INF);
        dist[idx]=0;
        par=vector<ll>(n+5);
        vector<bool> inq(n+5);
        vector<ll> cnt(n+5);
        inq[idx]=1;
        queue<ll> q;
        q.push(idx);
        while(!q.empty()){
            ll top=q.front();
            q.pop();
            if(++cnt[top]>=n) return 0;
            inq[top]=0;
            for(pll& p:adj[top]){
                ll d=dist[top]+p.fi;
                if(dist[p.se]>d){
                    dist[p.se]=d;
                    par[p.se]=top;
                    if(!inq[p.se]){
                        inq[p.se]=1;
                        q.push(p.se);
                    }
                }
            }
        }
        return 1;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,m;
    cin>>n>>m;
    graph G(n);
    while(m--){
        ll a,b,c;
        cin>>a>>b>>c;
        G.adj[a].eb(c,b);
    }
    if(!G.spfa(1)){
        cout<<-1;
        return 0;
    }
    FOR(i,2,n){
        if(G.dist[i]!=INF) cout<<G.dist[i]<<'\n';
        else cout<<"-1\n";
    }
    return 0;
}