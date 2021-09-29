#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define point pair<int,int>
#define x first
#define y second
point operator-(point a, point b){return {a.x - b.x, a.y - b.y};}
int ccw(point a, point b, point c)
{
    long long ret = 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (b.y - a.y) * (c.x - a.x);
    if (ret < 0) return -1;
    return ret > 0;
}
int ccw(point a, point b)
{
    long long ret = 1LL * a.x * b.y - 1LL * a.y * b.x;
    if (ret < 0) return -1;
    return ret > 0;
}
long long dist2(point a, point b) { return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y); }
signed main(void)
{
    cin.tie(0)->sync_with_stdio(false);
    int n; cin>>n;
    point ps[n];
    for (int i = 0; i < n; ++i) cin>>ps[i].x>>ps[i].y;
    swap(ps[0], *min_element(ps,ps+n));
    sort(ps+1, ps+n, [&](point a, point b) { return ccw(ps[0],a,b) > 0;});
    vector<point> stk;
    stk.push_back(ps[0]);
    for (int i = 1; i < n; stk.push_back(ps[i++]))
    {
        while(stk.size() >= 2 && ccw(stk[stk.size() - 2], stk[stk.size() - 1], ps[i]) <= 0) stk.pop_back();
    }
    long long ans = 0LL;
    for (int i = 0, j = 1%n; i < (int)stk.size(); ++i)
    {
        while(ccw(stk[(i + 1)%n] - stk[i], stk[(j + 1)%n] - stk[j]) > 0) j = (j + 1) % (int)stk.size();
        ans = max(ans, dist2(stk[i], stk[j]));
    }
    cout << ans << '\n';
    return 0;
}
