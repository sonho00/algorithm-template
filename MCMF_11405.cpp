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
    vector<vl> cap,cost,flow;
    MCMF(ll n):n(n),src(n+1),sink(n+2),
    cap(vector<vl>(n+5,vl(n+5))),
    cost(vector<vl>(n+5,vl(n+5))),
    flow(vector<vl>(n+5,vl(n+5)))
    {}
    MCMF(ll n,ll src,ll sink):n(n),src(src),sink(sink),
    cap(vector<vl>(n+5,vl(n+5))),
    cost(vector<vl>(n+5,vl(n+5))),
    flow(vector<vl>(n+5,vl(n+5)))
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
            FOR(i,1,n+2){
                if(flow[top][i]<cap[top][i]){
                    ll d=dist[top]+cost[top][i];
                    if(dist[i]>d){
                        dist[i]=d;
                        par[i]=top;
                        if(!inq[i]){
                            inq[i]=1;
                            q.push(i);
                        }
                    }
                }
            }
        }
        if(dist[sink]==INF) return pll(0,0);
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
        pll ret,tmp;
        while(1){
            tmp=spfa();
            if(!tmp.fi) break;
            ret.fi+=tmp.fi;
            ret.se+=tmp.se;
        }
        return ret;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,m,v,a;
    cin>>n>>m;
    MCMF mcmf(n+m);
    FOR(i,1,n) cin>>mcmf.cap[mcmf.src][i];
    FOR(i,n+1,n+m) cin>>mcmf.cap[i][mcmf.sink];
    FOR(j,n+1,n+m) FOR(i,1,n){
        cin>>mcmf.cost[i][j];
        mcmf.cost[j][i]=-mcmf.cost[i][j];
        mcmf.cap[i][j]=INF;
    }
    cout<<mcmf().fi;
    return 0;
}