#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using ll = long long;
ll n, m, s, e, t, r = INT_MAX, c[3001][3001], dp[3001][3001], p[3001];
deque<pair<ll, ll>> d[3001];
pair<ll, ll> b[3], T;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> s >> e >> t;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; c[i][j] += c[i][j - 1], j++)
			cin >> c[i][j];
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < s; j++)
			dp[i][j] = INT_MAX;
	for (int j = s; j <= m; j++) {
		b[0] = b[1] = b[2] = {INT_MAX, 0};
		for (int i = 1; i <= n; i++) {
			for (; d[i].size() && d[i].back().x > dp[i][j - s]; d[i].pop_back());
			d[i].push_back({dp[i][j - s], j - s});
			if (d[i].front().y < j - e)
				d[i].pop_front();
			if (b[0] > (T = {d[i].front().x + c[i][j], i}))
				b[2] = b[1], b[1] = b[0], b[0] = T;
			else if (b[1] > T)
				b[2] = b[1], b[1] = T;
			else
				b[2] = min(b[2], T);
		}
		for (int i = 1; i <= n; i++)
			dp[i][j] = (b[0].y == i || b[0].y == p[i] ? b[1].y == i || b[1].y == p[i] ? b[2].x : b[1].x : b[0].x) - c[i][j] + t;
	}
	for (int j = m - e; j < m; j++)
		for (int i = 1; i <= n; i++)
			r = min(r, dp[i][j] + c[i][m]);
	cout << r;
	return 0;
}
