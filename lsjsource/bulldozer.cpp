#include<bits/stdc++.h>
using namespace std;
using point = pair<int,int>;
#define x first
#define y second
point operator-(point a, point b){ return point(a.x - b.x, a.y - b.y); }
long long det(point a, point b) { return 1LL * a.x * b.y - 1LL * a.y * b.x; }
signed main()
{
    cin.tie(0)->sync_with_stdio(false);
    int N; cin>>N;
    vector<pair<point, long long>> P(N);
    for (auto& it: P) cin >> it.first.x >> it.first.y >> it.second;
    sort(P.begin(), P.end(), [](auto& a, auto& b)
    {
        if (a.first.y == b.first.y) return a.first.x < b.first.x;
        return a.first.y < b.first.y;
    });
    vector<pair<int, int>> swp;
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            swp.push_back({i, j});
    auto comp2 = [&](pair<int, int>& a, pair<int, int>& b) -> bool
    {
        long long d = det(P[a.second].first - P[a.first].first, P[b.second].first - P[b.first].first);
        if (d) return d > 0;
        else
        {
            if (P[a.first].first != P[b.first].first) return P[a.first].first < P[b.first].first;
            return P[a.second].first < P[b.second].first;
        }
    };
    sort(swp.begin(), swp.end(), comp2);
    vector<pair<point, long long>> srt = P;
    vector<int> pos(N); iota(pos.begin(), pos.end(), 0);
    auto comp3 = [&](pair<int, int>& a, pair<int, int>& b) -> long long
    {
        return det(P[a.second].first - P[a.first].first, P[b.second].first - P[b.first].first);
    };
    for (int i = 0; i < (int)swp.size(); )
    {
        int j = i;
        while(j < (int)swp.size() && comp3(swp[i], swp[j]) == 0)
        {
            int x = swp[j].first, y = swp[j].second;
            int &px = pos[x], &py = pos[y];
            swap(srt[px], srt[py]);
            swap(px, py);
            ++j;
        }
        i = j;
    }
    return 0;
}
