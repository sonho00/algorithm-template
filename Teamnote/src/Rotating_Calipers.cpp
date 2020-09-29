#include<bits/stdc++.h>
#define MAX 100000
#define INF 10000
using namespace std;
using ll = long long;

struct cor {
	ll x, y;
	cor(ll _x = 0, ll _y = 0) :x(_x), y(_y) {}
	bool operator==(cor a) { return x == a.x && y == a.y; }
	cor operator-(cor a) { return cor(x - a.x, y - a.y); }
	bool operator<(cor a) {
		if (y != a.y) return y < a.y;
		return x < a.x;
	}
	friend istream& operator>>(istream& stream, cor& a) { return stream >> a.x >> a.y; }
	friend ostream& operator<<(ostream& stream, cor& a) { return stream << a.x << ' ' << a.y; }
	friend ll outpro(cor a, cor b) { return a.x * b.y - a.y * b.x; }
	friend ll ccw(cor a, cor b, cor c) {
		ll tmp = outpro(b - a, c - a);
		if (tmp > 0) return 1;
		if (tmp < 0) return -1;
		return 0;
	}
	friend ll dist(cor a, cor b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
};
struct convex {
	ll sz;
	vector<cor> v;
	cor& operator[](ll a) { return v[(a + sz) % sz]; }
	void updt(cor& a) {
		convex& h = *this;
		while (sz >= 2) {
			ll tmp = ccw(h[-2], h[-1], a);
			if (tmp > 0) break;
			v.pop_back();
			--sz;
		}
		v.push_back(a);
		++sz;
	}
	double operator()() {
		convex& h = *this;
		ll l = 0, r = 0, m = 0;
		for (ll i = 0; i < sz; ++i) {
			if (h[m] < h[i]) m = i;
		}
		r = m;
		ll ret = dist(h[l], h[r]);
		while (l < m || r < sz) {
			ll tmp = outpro(h[l + 1] - h[l], h[r + 1] - h[r]);
			if (tmp > 0) ret = max(ret, dist(h[l], h[++r]));
			if (tmp < 0) ret = max(ret, dist(h[++l], h[r]));
			if (!tmp) ret = max(ret, dist(h[++l], h[++r]));
		}
		return sqrt(ret);
	}
};

ll c;
vector<cor> v;
cor bot(INF, INF);
convex hull;

int main() {
	cin >> c;
	while (c--) {
		cor x;
		cin >> x;
		if (x < bot) bot = x;
		v.push_back(x);
	}
	v.erase(unique(v.begin(), v.end()), v.end());
	c = v.size();
	sort(v.begin(), v.end(), [](cor& a, cor& b) {
		ll tmp = ccw(bot, a, b);
		if (!tmp) return a < b;
		return tmp > 0;
		});
	for (cor& x : v) {
		hull.updt(x);
	}
	cout << fixed;
	cout.precision(12);
	cout << hull();
	return 0;
}