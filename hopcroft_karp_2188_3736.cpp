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

struct bimat{
    ll n,m;
    vl mata,matb,lv;
    vector<vl> adj;
    bimat(ll n,ll m):n(n),m(m),
    mata(vl(n+5)),matb(vl(m+5)),
    adj(vector<vl>(n+5)){}
    void bfs(){
        lv=vl(n+5);
        queue<ll> q;
        FOR(i,1,n){
            if(!mata[i]){
                lv[i]=1;
                q.push(i);
            }
        }
        while(!q.empty()){
            ll top=q.front();
            q.pop();
            for(ll nxt:adj[top]){
                nxt=matb[nxt];
                if(nxt && !lv[nxt]){
                    lv[nxt]=lv[top]+1;
                    q.push(nxt);
                }
            }
        }
    }
    bool dfs(ll idx){
        for(ll i:adj[idx]){
            ll nxt=matb[i];
            if(!nxt || lv[nxt]==lv[idx]+1 && dfs(nxt)){
                matb[i]=idx;
                mata[idx]=i;
                return true;
            }
        }
        return false;
    }
    ll operator()(){
        ll ret=0;
        while(1){
            bfs();
            ll cnt=0;
            FOR(i,1,n) if(!mata[i] && dfs(i)) ++cnt;
            if(cnt) ret+=cnt;
            else break;
        }
        return ret;
    }
};

ll n;
void tc(){
    bimat hop(n,n);
    ll j,s,a;
    FOR(i,1,n){
        scanf("%lld: (%lld)",&j,&s);
        while(s--){
            scanf("%lld",&a);
            hop.adj[j+1].pb(a-n+1);
        }
    }
    printf("%lld\n",hop());
}

int main(){
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    while(scanf("%lld",&n)>0) tc();
    return 0;
}