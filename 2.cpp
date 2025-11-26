#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#define W s < e ? (z[d * 2] += z[d], z[d * 2 + 1] += z[d], y[d * 2] = max(y[d], y[d * 2] + z[d]), y[d * 2 + 1] = max(y[d], y[d * 2 + 1] + z[d])) : g[s] = max(g[s] + z[d], y[d]), z[d] = 0, y[d] = -1e18
using namespace std;
using ll = long long;
const ll N = 1000001, S = 2100000;
ll n, m, a[N], s[N], p[N], b, t, q, e, g[N], z[S], y[S];
priority_queue<pair<ll, ll>> pq;
vector<ll> c;
void u(ll l, ll r, ll k, ll x = -1e18, ll s = 0, ll e = n, ll d = 1) {
	W;
	if (s > r || e < l)
		return;
	if (s >= l && e <= r)
		z[d] = k, y[d] = x, W;
	else
		u(l, r, k, x, s, s + e >> 1, d * 2), u(l, r, k, x, s + e + 2 >> 1, e, d * 2 + 1);
}
ll f(ll x, ll s = 0, ll e = n, ll d = 1) {
	W;
	return s < e ? s + e >> 1 < x ? f(x, s + e + 2 >> 1, e, d * 2 + 1) : f(x, s, s + e >> 1, d * 2) : g[x];
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> s[i] >> p[i];
		if ((a[i] += a[i - 1]) <= s[i])
			pq.push({a[i] - s[i], i});
	}
	fill(y, y + S, -1e18);
	for (int i = 0; i < m; i++) {
		cin >> b >> t >> q;
		for (u(0, t = upper_bound(a, a + n + 1, t - (e += b)) - a - 1, q), c = {t + 1}; pq.size() && -pq.top().first < e; pq.pop())
			t = pq.top().second, u(t, n, p[t]), c.push_back(t);
		for (ll i : c)
			u(i, n, 0, f(max(i - 1, 0ll)));
	}
	for (t = f(n); pq.size(); pq.pop())
		t += p[pq.top().second];
	cout << t;
	return 0;
}
