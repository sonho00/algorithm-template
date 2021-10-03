//백준 1144
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
#define sz(v) (int)((v).size())
#define all(x) (x).begin(), (x).end()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
constexpr int inf = 1e9 + 7;
int n, m, grid[9][9];
// map<tuple<int, int, vector<int>>, int> dp;
map<int, map<int, map<vector<int>, int>>> dp;
void norm(vector<int>& a)
{
    vector<int> comp;
    for (auto& it: a) if (it != -1) comp.push_back(it);
    sort(all(comp));
    comp.resize(unique(all(comp)) - comp.begin());
    for(auto& it : a) if (it != -1) it = (int)(lower_bound(all(comp), it) - comp.begin());
}
int f(int r, int c, vector<int> p)
{
    if (c == m) return f(r + 1, 0, p);
    if (dp[r][c].count(p)) return dp[r][c][p];
    bool stopable = true;
    int before = -1;
    for (int i = 0; i < m; ++i)
    {
        if (p[i] != -1)
        {
            if (before == -1) before = p[i];
            else if (before != p[i])
            {
                stopable = false;
                break;
            }
        }
    }
    int& ret = dp[r][c][p] = inf;
    if (stopable) ret = 0;

    if (r == n) return ret;

    int canz = (p[0] == -1);
    for (int i = 1; i < m && !canz; ++i) if (p[0] == p[i]) canz = true;
    if (canz)
    {
        vector<int> np(m);
        for (int i = 0; i + 1 < m; ++i) np[i] = p[i + 1];
        np.back() = -1;
        norm(np);
        ret = min(ret, f(r, c + 1, np));
    }
    {
        int first = -1, second = -1;
        if (c - 1 >= 0 && p.back() != -1) first = p.back();
        if (r - 1 >= 0 && p.front() != -1) second = p.front();
        vector<int> np(m);
        for (int i = 0; i + 1 < m; ++i)
            np[i] = first != -1 && first == p[i + 1] || second != -1 && second == p[i + 1] ? inf : p[i + 1];
        np.back() = inf;
        norm(np);
        ret = min(ret, f(r, c + 1, np) + grid[r][c]);
    }
    return ret;
}
signed main(void)
{
    cin.tie(0)->sync_with_stdio(false);
    cin>>n>>m;
    forn(i, n) forn(j, m) cin>>grid[i][j];
    vector<int> tmp(m, -1);
    cout << f(0, 0, tmp) << '\n';
    return 0;
}
