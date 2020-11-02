#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const ll INF=1e18;

// prime less than sqrt(max(n_i))
vector<ll> prime={2,3,5,7,11,13,17};

// ax+by=gcd(a,b)
// return {x,y,gcd(a,b)}
vector<ll> ext_euc(ll a,ll b){
    vector<ll> ret={1,0,a};
    vector<ll> tmp={0,1,b};
    while(tmp[2]){
        ll q=ret[2]/tmp[2];
        for(ll i=0; i<3; ++i) ret[i]-=q*tmp[i];
        swap(ret,tmp);
    }
    if(ret[2]>=0) return ret;
    else return {-ret[0],-ret[1],-ret[2]};
}
// write x=a mod n as pll(a,n)
// input = array of (a,n)
// output = (x,N)
pll crt(vector<pll> arr){
    ll r=0,n=1;
    for(pll& p:arr){
        p.fi=(p.se+p.fi%p.se)%p.se;
        n*=p.se;
    }
    for(pll& p:arr) r=(r+n/p.se*ext_euc(n/p.se,p.se)[0]*p.fi%n)%n;
    return {(n+r%n)%n,n};
}
pll ext_crt(vector<pll> arr){
    vector<pll> tmp;
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
        if(b!=1) tmp.emplace_back(a,b);
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
        tmp.emplace_back(a,b);
    }
    return crt(tmp);
}