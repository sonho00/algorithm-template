#include<bits/stdc++.h>
#define FOR(i,a,b) for(ll i=a; i<=b; ++i)
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const ll INF=1e18;
const ll MAX=1e5;

struct node{
    ll val,li,ri;
    node(ll val=0):val(val),li(0),ri(0){}
    void updt(node& a,node& b){
        val=a.val+b.val;
    }
};
struct seg{
    ll sz;
    vector<node> v;
    seg(ll n):sz(n),v(vector<node>(1)){}
    void mkch(ll vi){
        if(!v[vi].li){
            v[vi].li=v.size();
            v.eb();
        }
        if(!v[vi].ri){
            v[vi].ri=v.size();
            v.eb();
        }
    }
    void updt(ll idx,ll val){updt(idx,val,1,sz,0);}
    void updt(ll idx,ll val,ll s,ll e,ll vi){
        if(e<idx || idx<s) return;
        v[vi].val=val;
        if(s==e) return;
        mkch(vi);
        ll m=s+e>>1;
        updt(idx,val,s,m,v[vi].li);
        updt(idx,val,m+1,e,v[vi].ri);
        v[vi].updt(v[v[vi].li],v[v[vi].ri]);
    }
    ll query(ll l,ll r){return query(l,r,1,sz,0);}
    ll query(ll l,ll r,ll s,ll e,ll vi){
        if(r<s || e<l) return 0;
        if(l<=s && e<=r) return v[vi].val;
        ll m=s+e>>1;
        ll lval=query(l,r,s,m,v[vi].li);
        ll rval=query(l,r,m+1,e,v[vi].ri);
        return lval+rval;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,q,m,k,a,b,c;
    cin>>n>>m>>k;
    seg tree(n);
    FOR(i,1,n){
        cin>>a;
        tree.updt(i,a);
    }
    q=m+k;
    while(q--){
        cin>>a>>b>>c;
        if(a==1) tree.updt(b,c);
        else cout<<tree.query(b,c)<<'\n';
    }
    return 0;
}