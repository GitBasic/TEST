#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#define A(x) x.begin(), x.end()
using namespace std;
using ll = long long;
ll n, m, g[100000], l[100000], s[100000], e[100000], i, r, c[270000], a[270000];
vector<pair<ll, ll>> o;
vector<tuple<ll, ll, ll>> k;
void u(ll p, ll k, ll s, ll e, ll d) {
	if (s == e) {
		c[d] += k, a[d] += k * p;
		return;
	}
	if (s + e >> 1 < p)
		u(p, k, s + e + 2 >> 1, e, d * 2 + 1);
	else
		u(p, k, s, s + e >> 1, d * 2);
	c[d] = c[d * 2] + c[d * 2 + 1], a[d] = a[d * 2] + a[d * 2 + 1];
}
ll fd(ll l, ll s, ll e, ll d) {
	if (s == e)
		return s * l;
	if (l > c[d * 2])
		return a[d * 2] + fd(l - c[d * 2], s + e + 2 >> 1, e, d * 2 + 1);
	return fd(l, s, s + e >> 1, d * 2);
}
void f() {
	for (ll& i : c)
		i = 0;
	for (ll& i : a)
		i = 0;
	for (i = 0; i < m; i++)
		if (s[i] < e[i])
			o.push_back({(s[i] + e[i] + 1) / 2, i});
	sort(A(o)), reverse(A(o)), i = 0, r = 1e6;
	for (auto [d, p, b] : k) {
		if (d < r)
			for (; i < o.size() && o[i].first > d; i++) {
				auto [P, I] = o[i];
				if (c[1] < l[I] || fd(l[I], 1, 1e5, 1) > g[I])
					e[I] = P - 1;
				else
					s[I] = P;
			}
		r = d, u(p, b, 1, 1e5, 1);
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	k.resize(n);
	for (auto& [d, p, l] : k)
		cin >> d >> p >> l;
	for (sort(A(k)), reverse(A(k)), k.push_back({-2, 0, 0}); i < m; s[i] = -1, e[i++] = 1e5)
		cin >> g[i] >> l[i];
	for (int t = 17; t--; o = {})
		f();
	for (i = 0; i < m; i++)
		cout << s[i] << '\n';
	return 0;
}
