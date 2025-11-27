#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#define A(x) x.begin(), x.end()
#define l(x, d) lower_bound(A(t[d]), x)
using namespace std;
long long n, m, a[200000], b[200000], r, x, y;
vector<int> t[530000];
void ini(int s, int e, int d) {
	if (s < e)
		ini(s, s + e >> 1, d * 2), ini(s + e + 2 >> 1, e, d * 2 + 1), t[d].resize(e - s + 1), merge(A(t[d * 2]), A(t[d * 2 + 1]), t[d].begin());
	else
		t[d] = {0}, cin >> t[d][0];
}
int f(int s, int e, int d) {
	if (s == e)
		return 0;
	auto p = l(x, d * 2 + 1);
	if (p != t[d * 2 + 1].end() && *p < y)
		return f(s + e + 2 >> 1, e, d * 2 + 1);
	return f(s, s + e >> 1, d * 2) + t[d * 2 + 1].end() - p;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> a[i] >> b[i];
	ini(1, m, 1);
	for (int i = 0; i < n; i++) {
		x = min(a[i], b[i]), y = a[i] ^ b[i] ^ x;
		auto p = l(x, 1);
		if (p != t[1].end() && *p < y)
			r += f(1, m, 1) & 1 ? x : y;
		else
			r += t[1].end() - p & 1 ? b[i] : a[i];
	}
	cout << r;
	return 0;
}
