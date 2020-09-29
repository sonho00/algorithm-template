#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

struct line{
    ll slope, constant;
    line() : slope(0), constant(0){}
    line(ll a, ll b) : slope(a), constant(b){}
};
// x should be monotonic increasing
struct CHT{
    int sz;
    deque<line> L;
    CHT() : sz(0) {}
    double get_point(line L1, line L2){
        return (double)(L2.constant-L1.constant)/(L1.slope-L2.slope);
    }
    bool increase(line L1, line L2, line L3){
        double p1=get_point(L1,L2);
        double p2=get_point(L2,L3);
        return p1<=p2;
    }
    void update(line L3){
        while(sz>1){
            line L2=L.back();
            L.pop_back();
            sz--;
            line L1=L.back();
            if(increase(L1,L2,L3)){
                L.push_back(L2);
                sz++;
                break;
            }
        }
        L.push_back(L3);
        sz++;
    }
    ll query(ll x){
        while(sz>1 && get_point(L[0],L[1])<(double)x){
            L.pop_front();
            sz--;
        }
        line L1=L.front();
        return L1.slope*x+L1.constant;
    }
};
