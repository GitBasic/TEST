#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#define L y[r].l
#define R y[r].r
using namespace std;
using ll = long long;
ll n, m, x = -9e9, t[200001], a, i = 1;
pair<ll, ll> p[200001];
struct N {
	ll s, c, l, r;
} y[6200001];
void u(ll k, ll s, ll e, ll& r, ll o) {
	y[r = ++a] = y[o];
	if (s < e)
		s + e >> 1 < k ? u(k, s + e + 2 >> 1, e, R, y[o].r) : u(k, s, s + e >> 1, L, y[o].l), y[r].s = y[L].s + y[R].s, y[r].c = y[L].c + y[R].c;
	else
		y[r].s += k, y[r].c++;
}
ll g(ll k, ll l, ll r) {
	if (!L && !R)
		return y[r].s / y[r].c * k;
	if ((a = y[R].c - y[y[l].r].c) < k)
		return y[R].s - y[y[l].r].s + g(k - a, y[l].l, L);
	return g(k, y[l].r, R);
}
void f(ll s, ll e, ll l, ll r) {
	if (s > e)
		return;
	ll d = s + e >> 1, o = -9e9, b;
	for (i = l; i <= min(r, d - m + 1); i++)
		tie(o, b) = max(tuple(o, b), {2 * (p[i].first - p[d].first) + g(m, t[i - 1], t[d]), i});
	x = max(x, o), f(s, d - 1, l, b), f(d + 1, e, b, r);
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for (; i <= n; i++)
		cin >> p[i].second >> p[i].first;
	sort(p, p + n + 1);
	for (i = 1; i <= n; i++)
		u(p[i].second, 1, 1e9, t[i], t[i - 1]);
	f(m, n, 1, n);
	cout << x;
	return 0;
}
