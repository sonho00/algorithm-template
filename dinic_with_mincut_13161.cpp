#define _USE_MATH_DEFINES
#include<bits/stdc++.h>
#define FOR(i,a,b) for(ll i=a; i<=b; ++i)
#define ALL(x) x.begin(),x.end()
#define gcd __gcd
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
const ll MAX=1e5;
const ll MOD=1e9+7;

struct maxfl{
    ll n,src,sink;
    vl work,lv;
    vector<vl> cap,flow;
    maxfl(ll n):n(n),src(n+1),sink(n+2),
    cap(vector<vl>(n+5,vl(n+5))),
    flow(vector<vl>(n+5,vl(n+5))){}
    bool bfs(){
        lv=vl(n+5);
        queue<ll> q;
        q.push(src);
        lv[src]=1;
        while(!q.empty()){
            ll top=q.front();
            q.pop();
            FOR(i,1,n+2){
                if(!lv[i] && flow[top][i]<cap[top][i]){
                    lv[i]=lv[top]+1;
                    q.push(i);
                }
            }
        }
        return lv[sink];
    }
    ll dfs(ll idx,ll f){
        if(idx==sink) return f;
        ll ret=0,rest;
        for(ll& i=work[idx]; i<=n+2; ++i){
            rest=cap[idx][i]-flow[idx][i];
            if(lv[i]==lv[idx]+1 && rest){
                if(ret=dfs(i,min(f,rest))){
                    flow[idx][i]+=ret;
                    flow[i][idx]-=ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    ll operator()(){
        ll ret=0,d;
        while(bfs()){
            work=vl(n+5,1);
            while(d=dfs(src,INF)) ret+=d;
        }
        return ret;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin>>n;
    maxfl dinic(n);
    FOR(i,1,n){
        ll s;
        cin>>s;
        switch(s){
        case 1:
            dinic.cap[dinic.src][i]=INF;
            break;
        case 2:
            dinic.cap[i][dinic.sink]=INF;
            break;
        }
    }
    FOR(i,1,n) FOR(j,1,n) cin>>dinic.cap[i][j];
    cout<<dinic()<<endl;
    dinic.bfs();
    FOR(i,1,n) if(dinic.lv[i]) cout<<i<<' ';
    cout<<endl;
    FOR(i,1,n) if(!dinic.lv[i]) cout<<i<<' ';
    cout<<endl;
    return 0;
}