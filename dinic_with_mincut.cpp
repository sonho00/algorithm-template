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
const ll MAX=500;
const ll MOD=1e9+7;
const ll LOG=20;

ll n;
ll cap[MAX+5][MAX+5];

struct maxfl{
    vector<ll> side,work,lv;
    ll flow[MAX+5][MAX+5]={};
    void make(ll n){
        side=vector<ll>(n+5,0);
    }
    bool bfs(){
        lv=vector<ll>(n+5,0);
        ll q[MAX+5];
        ll s=0,e=0;
        q[e++]=n+1;
        lv[n+1]=1;
        while(s<e){
            ll top=q[s++];
            FOR(i,1,n+2){
                if(!lv[i] && flow[top][i]<cap[top][i]){
                    lv[i]=lv[top]+1;
                    q[e++]=i;
                }
            }
        }
        return lv[n+2];
    }
    ll dfs(ll idx=n+1,ll f=INF){
        if(idx==n+2) return f;
        ll ret=0,rest;
        for(ll& i=work[idx]; i<=n+2; ++i){
            rest=cap[idx][i]-flow[idx][i];
            if(lv[i]==lv[idx]+1 && rest && (ret=dfs(i,min(f,rest)))){
                flow[idx][i]+=ret;
                flow[i][idx]-=ret;
                return ret;
            }
        }
        return 0;
    }
    ll operator()(){
        ll ret=0,d;
        while(bfs()){
            work=vector<ll>(n+5,1);
            while(d=dfs()) ret+=d;
        }
        return ret;
    }
    void cut(){
        ll q[MAX+5];
        ll s=0,e=0;
        q[e++]=n+1;
        bool visit[MAX+5]={};
        visit[n+1]=1;
        while(s<e){
            ll top=q[s++];
            FOR(i,1,n+2){
                if(!visit[i] && flow[top][i]<cap[top][i]){
                    visit[i]=1;
                    q[e++]=i;
                    side[i]=1;
                }
            }
        }
    }
};

maxfl dinic;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    dinic.make(n);
    FOR(i,1,n){
        cin>>dinic.side[i];
        switch(dinic.side[i]){
        case 1:
            cap[n+1][i]=INF;
            break;
        case 2:
            cap[i][n+2]=INF;
            break;
        }
    }
    FOR(i,1,n) FOR(j,1,n) cin>>cap[i][j];
    cout<<dinic()<<'\n';
    dinic.cut();
    FOR(i,1,n) if(dinic.side[i]==1) cout<<i<<' ';
    cout<<'\n';
    FOR(i,1,n) if(dinic.side[i]!=1) cout<<i<<' ';
    cout<<'\n';
    return 0;
}