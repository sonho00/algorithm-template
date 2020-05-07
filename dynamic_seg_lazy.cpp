#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a; i<=b; ++i)
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const ll INF=1e18;
const ll MAX=1e6;

struct node{
    ll s,e,lz,val,li,ri;
    node(ll s,ll e,ll lz=0)
    :s(s),e(e),lz(lz),val(0),li(0),ri(0){}
    void updt(node& a,node& b){
        val=a.val+b.val;
    }
};
struct seg{
    vector<node> v;
    void make(ll n){v.eb(1,n);}
    void mkch(ll vi){
        ll s=v[vi].s;
        ll e=v[vi].e;
        if(!v[vi].li){
            v[vi].li=v.size();
            v.eb(s,(s+e)/2,v[vi].val/(e-s+1));
        }
        if(!v[vi].ri){
            v[vi].ri=v.size();
            v.eb((s+e)/2+1,e,v[vi].val/(e-s+1));
        }
    }
    void lazy(ll vi){
        if(v[vi].s!=v[vi].e){
            mkch(vi);
            v[v[vi].li].lz+=v[vi].lz;
            v[v[vi].ri].lz+=v[vi].lz;
        }
        v[vi].val+=(v[vi].e-v[vi].s+1)*v[vi].lz;
        v[vi].lz=0;
    }
    void updt(ll l,ll r,ll val,ll vi=0){
        ll s=v[vi].s;
        ll e=v[vi].e;
        if(r<s || e<l){
            lazy(vi);
            return;
        }
        if(l<=s && e<=r){
            v[vi].lz+=val;
            lazy(vi);
            return;
        }
        lazy(vi);
        updt(l,r,val,v[vi].li);
        updt(l,r,val,v[vi].ri);
        v[vi].updt(v[v[vi].li],v[v[vi].ri]);
    }
    ll query(ll l,ll r,ll vi=0){
        ll s=v[vi].s;
        ll e=v[vi].e;
        if(r<s || e<l) return 0;
        lazy(vi);
        if(l<=s && e<=r) return v[vi].val;
        ll lval=query(l,r,v[vi].li);
        ll rval=query(l,r,v[vi].ri);
        return lval+rval;
    }
};

ll n;
seg tree;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll q,m,k,a,b,c,d;
    cin>>n>>m>>k;
    tree.make(n);
    FOR(i,1,n){
        cin>>a;
        tree.updt(i,i,a);
    }
    q=m+k;
    while(q--){
        cin>>a;
        if(a==1){
            cin>>b>>c>>d;
            tree.updt(b,c,d);
        }
        else{
            cin>>b>>c;
            cout<<tree.query(b,c)<<'\n';
        }
    }
    return 0;
}