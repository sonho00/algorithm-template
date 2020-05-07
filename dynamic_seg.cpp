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
    static ll sz;
    vector<node> v;
    void make(ll n){
        sz=n;
        v.eb();
    }
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
    void updt(ll idx,ll val,ll s=1,ll e=sz,ll vi=0){
        if(e<idx || idx<s) return;
        v[vi].val=val;
        if(s==e) return;
        mkch(vi);
        updt(idx,val,s,(s+e)/2,v[vi].li);
        updt(idx,val,(s+e)/2+1,e,v[vi].ri);
        v[vi].updt(v[v[vi].li],v[v[vi].ri]);
    }
    ll query(ll l,ll r,ll s=1,ll e=sz,ll vi=0){
        if(r<s || e<l) return 0;
        if(l<=s && e<=r) return v[vi].val;
        ll lval=query(l,r,s,(s+e)/2,v[vi].li);
        ll rval=query(l,r,(s+e)/2+1,e,v[vi].ri);
        return lval+rval;
    }
};
ll seg::sz=0;

ll n;
seg tree;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll q,m,k,a,b,c;
    cin>>n>>m>>k;
    tree.make(n);
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