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

vl ext_euc(ll a,ll b){
    vl ret={1,0,a};
    vl tmp={0,1,b};
    while(tmp[2]){
        ll q=ret[2]/tmp[2];
        ret={ret[0]-q*tmp[0],ret[1]-q*tmp[1],ret[2]-q*tmp[2]};
        swap(ret,tmp);
    }
    return ret;
}

/*
Chinese remainder theorem
write x=a mod n as pll{a,n}

input = array of {a_i,n_i}
output = {x,N}
*/
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
    ll m=1,a=0,b=1;
    for(pll& p:arr){
        ll c=1;
        while(!(p.se&1)){
            p.se>>=1;
            c<<=1;
        }
        if(b<c){
            if((p.fi-a)%b) return {-1,-1};
            a=p.fi;
            b=c;
        }
        else{
            if((p.fi-a)%c) return {-1,-1};
        }
        m=max(m,p.se);
    }
    if(b!=1) tmp.eb(a,b);
    ll sqm=sqrt(m)+3;
    vector<bool> visit(sqm+5);
    for(ll i=3; i<=sqm; i+=2){
        if(visit[i]) continue;
        a=0,b=1;
        for(pll& p:arr){
            ll c=1;
            while(!(p.se%i)){
                p.se/=i;
                c*=i;
            }
            if(b<c){
                if((p.fi-a)%b) return {-1,-1};
                a=p.fi;
                b=c;
            }
            else{
                if((p.fi-a)%c) return {-1,-1};
            }
        }
        if(b!=1) tmp.eb(a,b);
        for(ll j=i*i; j<=sqm; j+=i<<1){
            visit[j]=1;
        }
    }
    for(pll& p:arr){
        tie(a,b)=p;
        if(b==1) continue;
        for(pll& p:arr){
            if(p.se==b){
                if((p.fi-a)%b) return {-1,-1};
                p.se=1;
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