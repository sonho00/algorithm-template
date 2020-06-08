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

struct graph{
    ll n;
    vector<vp> adj;
    vl dist,par;
    graph(ll n):n(n),adj(vector<vp>(n+5)){}
    void dijk(ll idx){
        dist=vl(n+5,INF);
        dist[idx]=0;
        par=vl(n+5);
        priority_queue<pll,vp,greater<pll>> pq;
        pq.emplace(0,idx);
        ll a,b,c,d;
        while(!pq.empty()){
            tie(a,b)=pq.top();
            pq.pop();
            if(dist[b]!=a) continue;
            for(pll& p:adj[b]){
                tie(c,d)=p;
                c+=a;
                if(dist[d]>c){
                    dist[d]=c;
                    par[d]=b;
                    pq.emplace(c,d);
                }
            }
        }
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
        G.adj[b].eb(c,a);
    }
    G.dijk(1);
    cout<<n-1<<endl;
    FOR(i,2,n) cout<<i<<' '<<G.par[i]<<endl;
    return 0;
}