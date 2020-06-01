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

struct MCMF{
    ll n,src,sink;
    vector<vl> cap,flow;
    vector<vp> adj;
    MCMF(ll n):n(n),src(n+1),sink(n+2),
    cap(vector<vl>(n+5,vl(n+5))),
    flow(vector<vl>(n+5,vl(n+5))),
    adj(vector<vp>(n+5))
    {}
    MCMF(ll n,ll src,ll sink):n(n),src(src),sink(sink),
    cap(vector<vl>(n+5,vl(n+5))),
    flow(vector<vl>(n+5,vl(n+5))),
    adj(vector<vp>(n+5))
    {}
    pll spfa(){
        vl dist(n+5,INF);
        dist[src]=0;
        vl par(n+5);
        vector<bool> inq(n+5);
        inq[src]=1;
        queue<ll> q;
        q.push(src);
        while(!q.empty()){
            ll top=q.front();
            q.pop();
            inq[top]=0;
            for(pll& p:adj[top]){
                ll a,b;
                tie(a,b)=p;
                if(flow[top][b]<cap[top][b]){
                    ll d=dist[top]+a;
                    if(dist[b]>d){
                        dist[b]=d;
                        par[b]=top;
                        if(!inq[b]){
                            inq[b]=1;
                            q.push(b);
                        }
                    }
                }
            }
        }
        if(!par[sink]) return pll(0,0);
        ll f=INF,v=sink,p;
        while(v!=src){
            p=par[v];
            f=min(f,cap[p][v]-flow[p][v]);
            v=p;
        }
        v=sink;
        while(v!=src){
            p=par[v];
            flow[p][v]+=f;
            flow[v][p]-=f;
            v=p;
        }
        return pll(f*dist[sink],f);
    }
    pll operator()(){
        pll ret;
        while(1){
            pll tmp=spfa();
            if(!tmp.se) break;
            ret.fi+=tmp.fi;
            ret.se+=tmp.se;
        }
        return ret;
    }
    void addEdge(ll a,ll b,ll capa,ll cst){
        cap[a][b]=capa;
        adj[a].eb(cst,b);
        adj[b].eb(-cst,a);
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
    cout<<mcmf().fi;
    return 0;
}