#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, s, x[300001], p[300001], a, b;
priority_queue<pair<ll, ll>> q[300001];
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> s;
	for (int i = 1; i <= n; i++)
		cin >> x[i] >> p[i];
	for (int i = n; i; i--) {
		if (x[i] > 0)
			q[i].push({0, x[i]});
		else {
			for (a = b = x[i]; q[i].size() && (b < 0 || a < q[i].top().first); q[i].pop())
				a = min(a, q[i].top().first + b), b += q[i].top().second;
			if (b > 0)
				q[i].push({a, b});
		}
		if (q[i].size() > q[p[i]].size())
			swap(q[i], q[p[i]]);
		for (; q[i].size(); q[i].pop())
			q[p[i]].push(q[i].top());
	}
	for (b = s; q[0].size() && b >= -q[0].top().first; q[0].pop())
		b += q[0].top().second;
	cout << b - s;
	return 0;
}
