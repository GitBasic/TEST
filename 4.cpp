#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#define x first
#define y second
#define A(k) l[c[a[i]]].erase(a[i]), s.erase({c[a[i]], a[i]}), u(c[a[i]]), l[k c[a[i]]].insert(a[i]), s.insert({c[a[i]], a[i]}), u(c[a[i]])
#define F(i) i&& l[i].size() ? P{*l[i].begin(), *l[i].rbegin()} : P{1e7, -1e7}
using namespace std;
using P = pair<int, int>;
int n, q, i = 1, r, a[200001], c[200001], m;
set<int> l[200002];
set<P> s;
P t[530000], p;
P M(P a, P b) { return {min(a.x, b.x), max(a.y, b.y)}; }
void u(int k, int s = 1, int e = n, int d = 1) {
	if (s < e)
		s + e >> 1 < k ? u(k, s + e + 2 >> 1, e, d * 2 + 1) : u(k, s, s + e >> 1, d * 2), t[d] = M(t[d * 2], t[d * 2 + 1]);
	else
		t[d] = F(s);
}
P f(int r, int s, int e, int d) {
	if (s >= r)
		return t[d];
	if (e < r)
		return {1e7, -1e7};
	return M(f(r, s, s + e >> 1, d * 2), f(r, s + e + 2 >> 1, e, d * 2 + 1));
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	for (; i <= n; c[a[i++]]++)
		cin >> a[i];
	for (i = 1; i <= n; m = max(m, c[i++]))
		l[c[i]].insert(i), s.insert({c[i], i});
	for (i = 1; i <= n; i++)
		u(i);
	for (; q--; r = 0) {
		cin >> i;
		A(--);
		cin >> a[i];
		A(++), m -= l[m += !l[m + 1].empty()].empty();
		if (m >> 11)
			for (auto i = s.rbegin(); i != s.rend() && i->x > m - 1 >> 2; i++)
				p = f(m - i->x, 1, n, 1), r = max(r, max(p.y - i->y, i->y - p.x));
		else
			for (i = 1, p = F(m); i <= m; i++) {
				p = M(p, F(m - i));
				if (l[i].size())
					r = max(r, max(p.y - *l[i].begin(), *l[i].rbegin() - p.x));
			}
		cout << r << '\n';
	}
	return 0;
}
