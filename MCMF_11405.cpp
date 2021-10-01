#include<bits/stdc++.h>
#define FOR(i,a,b) for(ll i=a; i<=b; ++i)
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const ll INF=1e18;

struct MCMF{
    struct Edge{
        ll par,nxt,cap,cost,flow;
        Edge(ll par,ll nxt,ll cap,ll cost):par(par),nxt(nxt),cap(cap),cost(cost),flow(0){}
    };
    ll n,src,sink;
    vector<ll> st,lv;
    vector<Edge> edge;
    MCMF(ll n):n(n),src(n+1),sink(n+2),st(n+5,-1){}
    void addEdge(ll a,ll b,ll cap,ll cost){
        edge.emplace_back(st[a],b,cap,cost);
        st[a]=edge.size()-1;
        edge.emplace_back(st[b],a,0,-cost);
        st[b]=edge.size()-1;
    }
    pll spfa(){
        vector<ll> dist(n+5,INF);
        dist[src]=0;
        vector<bool> inq(n+5);
        inq[src]=1;
        queue<ll> q;
        q.push(src);
        vector<ll> par;
        while(!q.empty()){
            ll idx=q.front();
            q.pop();
            inq[idx]=0;
            for(ll i=st[idx]; i!=-1; i=edge[i].par){
                Edge& e=edge[i];
                if(e.flow<e.cap){
                    if(dist[e.nxt]>dist[idx]+e.cost){
                        dist[e.nxt]=dist[idx]+e.cost;
                        par[e.nxt]=i;
                        if(!inq[e.nxt]){
                            inq[e.nxt]=1;
                            q.push(e.nxt);
                        }
                    }
                }
            }
        }
        if(!par[sink]) return {0,0};
        ll flow=INF;
        for(ll idx=sink; idx!=src; idx=edge[par[idx]^1].nxt){
            Edge& e=edge[par[idx]];
            flow=min(flow,e.cap-e.flow);
        }
        for(ll idx=sink; idx!=src; idx=edge[par[idx]^1].nxt){
            Edge& e=edge[par[idx]];
            e.flow+=flow;
            edge[par[idx]^1].flow-=flow;
        }
        return pll(flow*dist[sink],flow);
    }
    pll solve(){
        pll ret;
        while(1){
            auto[a,b]=spfa();
            if(!b) break;
            ret.first+=a;
            ret.second+=b;
        }
        return ret;
    }
    void print(){
        for(ll i=1; i<=n+2; ++i){
            cout<<i<<'\n';
            for(ll j=st[i]; j!=-1; j=edge[j].par){
                Edge& e=edge[j];
                cout<<j<<' '<<e.par<<' '<<e.nxt<<' '<<e.cap<<' '<<e.cost<<' '<<e.flow<<'\n';
            }
            cout<<'\n';
        }
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,m,v,a;
    cin>>n>>m;
    MCMF mcmf(n+m);
    FOR(i,1,n){
        ll k;
        cin>>k;
        mcmf.addEdge(mcmf.src,i,k,0);
    }
    FOR(i,n+1,n+m){
        ll k;
        cin>>k;
        mcmf.addEdge(i,mcmf.sink,k,0);
    }
    FOR(j,n+1,n+m) FOR(i,1,n){
        ll k;
        cin>>k;
        mcmf.addEdge(i,j,INF,k);
    }
    mcmf.print();
    return 0;
    cout<<mcmf.solve().first;
    return 0;
}