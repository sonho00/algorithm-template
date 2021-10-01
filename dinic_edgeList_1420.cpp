#include<bits/stdc++.h>
#define FOR(i,a,b) for(ll i=a; i<=b; ++i)
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
using vl=vector<ll>;
const ll INF=1e18;

struct Dinic{
    struct Edge{
        ll par,nxt,cap,flow;
        Edge(ll par,ll nxt,ll cap):par(par),nxt(nxt),cap(cap),flow(0){}
    };
    ll n,src,sink;
    vector<ll> st,cur,lv;
    vector<Edge> edge;
    Dinic(ll n):n(n),src(n+1),sink(n+2),st(n+5,-1){}
    void addEdge(ll a,ll b,ll cap){
        edge.emplace_back(st[a],b,cap);
        st[a]=edge.size()-1;
        edge.emplace_back(st[b],a,0);
        st[b]=edge.size()-1;
    }
    bool bfs(){
        lv=vector<ll>(n+5);
        lv[src]=1;
        queue<ll> q;
        q.push(src);
        while(!q.empty()){
            ll idx=q.front();
            q.pop();
            for(ll i=st[idx]; i!=-1; i=edge[i].par){
                Edge& e=edge[i];
                if(!lv[e.nxt] && e.flow<e.cap){
                    lv[e.nxt]=lv[idx]+1;
                    q.push(e.nxt);
                }
            }
        }
        return lv[sink];
    }
    ll dfs(ll idx,ll flow){
        if(idx==sink) return flow;
        for(ll& i=cur[idx]; i!=-1; i=edge[i].par){
            Edge& e=edge[i];
            if(e.flow<e.cap && lv[e.nxt]==lv[idx]+1){
                ll tmp=dfs(e.nxt,min(flow,e.cap-e.flow));
                if(tmp){
                    e.flow+=tmp;
                    edge[i^1].flow-=tmp;
                    return tmp;
                }
            }
        }
        return 0;
    }
    ll solve(){
        ll ret=0;
        while(bfs()){
            cur=st;
            ll tmp;
            while(tmp=dfs(src,INF)) ret+=tmp;
        }
        return ret;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
    ll n,m;
    cin>>n>>m;
    char g[105][105];
    FOR(i,1,n) cin>>g[i]+1;
    FOR(i,0,n+1) g[i][0]=g[i][m+1]='#';
    FOR(j,0,m+1) g[0][j]=g[n+1][j]='#';
    ll num[105][105];
    ll cnt=0;
    FOR(i,1,n) FOR(j,1,m){
        if(g[i][j]!='#') num[i][j]=++cnt;
    }
    Dinic dinic(cnt<<1);
    FOR(i,1,n) FOR(j,1,m){
        switch(g[i][j]){
            case '#':
                continue;
            case 'K':
                dinic.src=num[i][j]<<1|1;
                break;
            case 'H':
                dinic.sink=num[i][j]<<1;
                break;
            default:
                dinic.addEdge(num[i][j]<<1,num[i][j]<<1|1,1);
                break;
        }
        FOR(k,0,3){
            ll a=i+dir[k][0];
            ll b=j+dir[k][1];
            if(g[a][b]!='#'){
                dinic.addEdge(num[i][j]<<1|1,num[a][b]<<1,INF);
            }
        }
    }
    ll ans=dinic.solve();
    cout<<(ans<=n*m?ans:-1);
    return 0;
}
