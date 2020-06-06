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

struct Edge{
    ll nxt,des,cap,flow;
    Edge(ll nxt,ll des,ll cap):nxt(nxt),des(des),cap(cap),flow(0){}
};
struct maxfl{
    ll n,src,sink;
    vl st,cur,lv;
    vector<Edge> edge;
    maxfl(ll n):n(n),src(n+1),sink(n+2),st(vl(n+5,-1)){}
    void addEdge(ll a,ll b,ll capa){
        edge.eb(st[a],b,capa);
        st[a]=edge.size()-1;
        edge.eb(st[b],a,0);
        st[b]=edge.size()-1;
    }
    bool bfs(){
        lv=vl(n+5);
        lv[src]=1;
        queue<ll> q;
        q.push(src);
        while(!q.empty()){
            ll top=q.front();
            q.pop();
            for(ll idx=st[top]; idx!=-1; idx=edge[idx].nxt){
                Edge& e=edge[idx];
                if(e.flow==e.cap || lv[e.des]) continue;
                lv[e.des]=lv[top]+1;
                q.push(e.des);
            }
        }
        return lv[sink];
    }
    ll dfs(ll v,ll f){
        if(v==sink) return f;
        for(ll& idx=cur[v]; idx!=-1; idx=edge[idx].nxt){
            Edge& e=edge[idx];
            if(e.flow==e.cap || lv[e.des]!=lv[v]+1) continue;
            ll tmp=dfs(e.des,min(f,e.cap-e.flow));
            if(tmp){
                e.flow+=tmp;
                edge[idx^1].flow-=tmp;
                return tmp;
            }
        }
        return 0;
    }
    ll operator()(){
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
    maxfl dinic(cnt<<1);
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
    ll ans=dinic();
    cout<<(ans<=n*m?ans:-1);
    return 0;
}
