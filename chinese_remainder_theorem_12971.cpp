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

vl prime={2,3,5,7,11,13,17};
vl ext_euc(ll a,ll b){
    vl ret={1,0,a};
    vl tmp={0,1,b};
    while(tmp[2]){
        ll q=ret[2]/tmp[2];
        FOR(i,0,2) ret[i]-=q*tmp[i];
        swap(ret,tmp);
    }
    if(ret[2]>=0) return ret;
    else return {-ret[0],-ret[1],-ret[2]};
}
pll crt(vp arr){
    ll r=0,n=1;
    for(pll& p:arr){
        p.fi=(p.se+p.fi%p.se)%p.se;
        n*=p.se;
    }
    for(pll& p:arr) r=(r+n/p.se*ext_euc(n/p.se,p.se)[0]*p.fi%n)%n;
    return {(n+r%n)%n,n};
}
pll ext_crt(vp arr){
    vp tmp;
    ll m=INF;
    for(ll x:prime){
        if(x*x>m) break;
        m=1;
        ll a=0,b=1;
        for(pll& p:arr){
            ll c=1;
            while(p.se%x==0){
                p.se/=x;
                c*=x;
            }
            if((p.fi-a)%min(b,c)) return {-1,-1};
            if(b<c){
                a=p.fi;
                b=c;
            }
            m=max(m,p.se);
        }
        if(b!=1) tmp.eb(a,b);
    }
    for(pll& p:arr){
        ll a,b;
        tie(a,b)=p;
        if(b==1) continue;
        for(pll& q:arr){
            if(q.se==1) continue;
            if(b==q.se){
                if((a-q.fi)%b) return {-1,-1};
                q.se=1;
            }
        }
        tmp.eb(a,b);
    }
    return crt(tmp);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll a[3],b[3];
    FOR(i,0,2) cin>>a[i];
    FOR(i,0,2) cin>>b[i];
    vp arr;
    FOR(i,0,2) arr.eb(b[i],a[i]);
    cout<<ext_crt(arr).fi;
    return 0;
}