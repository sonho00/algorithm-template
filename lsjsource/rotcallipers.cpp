#include <bits/stdc++.h>
using namespace std;

using point = pair<int,int>;
#define x first
#define y second

point operator-(point a, point b) { return make_pair(a.x - b.x, a.y - b.y); }
int ccw(point a, point b) {
    long long x = 1LL * a.x * b.y - 1LL * a.y * b.x;
    return x < 0 ? -1 : x > 0;
}
int ccw(point p, point a, point b) { return ccw(a - p, b - p); }
long long dist2(point a, point b) { return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y); }
signed main(void)
{
    cin.tie(0)->sync_with_stdio(false);
    int T = 1; cin >> T;
    while (T--)
    {
        int n; cin >> n;
        point ps[n];
        for (int i = 0; i < n; ++i) cin >> ps[i].x >> ps[i].y;
        swap(ps[0], *min_element(ps, ps + n));
        sort(ps + 1, ps + n, [&](point a, point b)
        {
            long long x = ccw(ps[0], a, b);
            return x ? x > 0 : a < b;
        });
        vector<point> hull;
        for (int i = 0; i < n; hull.push_back(ps[i++]))
            while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull[hull.size() - 1], ps[i]) <= 0)
                hull.pop_back();
        point a = ps[0], b = ps[1];
        for (int i = 0, p = 0; i < (int)hull.size(); ++i)
        {
            while (p + 1 < (int)hull.size() && ccw(hull[i + 1] - hull[i], hull[p + 1] - hull[p]) > 0)
            {
                if (dist2(a, b) < dist2(hull[i], hull[p])) tie(a, b) = tie(hull[i], hull[p]);
                ++p;
            }
            if (dist2(a, b) < dist2(hull[i], hull[p])) tie(a, b) = tie(hull[i], hull[p]);
        }
        cout << a.x << ' ' << a.y << ' ' << b.x << ' ' << b.y << '\n';
    }
    return 0;
}
