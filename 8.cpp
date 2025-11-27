#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#define M 200001
#define A o.begin(), o.end()
#define L(x) upper_bound(A, x) - o.begin()
#define P push_back
using namespace std;
using ll = long long;
ll n, q, u, v, w, k, h[M], a[M], l[M], r[M], t[1050000], z[1050000];
vector<ll> o;
vector<pair<ll, ll>> e[M], Q;
void d(ll x, ll f, ll w, ll r) {
	h[x] = w, a[x] = r;
	for (auto [i, g] : e[x])
		if (i != f)
			d(i, x, w + g, r);
}
bool c(ll x, ll f) {
	if (x < 2) {
		for (auto [j, h] : e[x])
			if (j != f)
				d(j, x, h, 0);
		return 1;
	}
	for (auto [i, g] : e[x])
		if (i != f)
			if (c(i, x)) {
				a[x] = k += g;
				for (auto [j, h] : e[x])
					if (j != f && j != i)
						d(j, x, h, k);
				return 1;
			}
	return 0;
}
void upd(ll l, ll r, ll k, ll s = 2, ll e = o.size(), ll d = 1) {
	if (s < e)
		t[d * 2] += z[d], t[d * 2 + 1] += z[d], z[d * 2] += z[d], z[d * 2 + 1] += z[d], z[d] = 0;
	if (s > r || e < l)
		return;
	if (s >= l && e <= r) {
		t[d] += k, z[d] = k;
		return;
	}
	upd(l, r, k, s, s + e >> 1, d * 2), upd(l, r, k, s + e + 2 >> 1, e, d * 2 + 1), t[d] = min(t[d * 2], t[d * 2 + 1]);
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i < n; e[u].P({v, w}), e[v].P({u, w}), i++)
		cin >> u >> v >> w;
	c(n, 0), o = {0, k};
	for (int i = 1; i <= q; i++) {
		cin >> w >> u;
		if (w < 2) {
			cin >> v;
			if (h[u] < v)
				o.P(l[i] = max(a[u] + h[u] - v, 0ll)), o.P(r[i] = min(a[u] - h[u] + v, k));
			Q.P({i, 1});
		} else
			Q.P({u, -1});
	}
	sort(A), o.erase(unique(A), o.end());
	for (auto [i, x] : Q) {
		upd(L(l[i]) + 1, L(r[i]), x);
		cout << (t[1] > 0 ? "YES\n" : "NO\n");
	}
	return 0;
}
