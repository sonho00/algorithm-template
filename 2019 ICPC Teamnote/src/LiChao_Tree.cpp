#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> Line;

struct LiChaoTree{
    ll f(Line l, ll x){
        return l.first * x + l.second;
    }
    struct Node{
        int lnode, rnode;
        ll xl, xr;
        Line l;
    };
    vector<Node> nodes;
    void init(ll xmin, ll xmax){
        nodes.push_back({-1,-1,xmin,xmax,{0,-1e18}});
    }
    void insert(int n, Line newline){
        ll xl = nodes[n].xl, xr = nodes[n].xr;
        ll xm = (xl + xr) >> 1;
        Line llow = nodes[n].l, lhigh = newline;
        if( f(llow, xl) >= f(lhigh,xl) ) swap(llow, lhigh);
        if( f(llow, xr) <= f(lhigh, xr) ){
            nodes[n].l = lhigh;
            return;
        }
        else if( f(llow, xm) <= f(lhigh, xm) ){
            nodes[n].l = lhigh;
            if( nodes[n].rnode == -1 ){
                nodes[n].rnode = nodes.size();
                nodes.push_back({-1,-1,xm+1,xr,{0,-1e18}});
            }
            insert(nodes[n].rnode, llow);
        }
        else{
            nodes[n].l = llow;
            if( nodes[n].lnode == -1 ){
                nodes[n].lnode = nodes.size();
                nodes.push_back({-1,-1,xl,xm,{0,-1e18}});
            }
            insert(nodes[n].lnode, lhigh);
        }
    }
    ll get(int n, ll xq){
        if( n == -1 ) return -1e18;
        ll xl = nodes[n].xl, xr = nodes[n].xr;
        ll xm = (xl + xr) >> 1;
        if( xq <= xm ) return max(f(nodes[n].l, xq), get(nodes[n].lnode, xq));
        else return max(f(nodes[n].l, xq), get(nodes[n].rnode, xq));
    }
};
