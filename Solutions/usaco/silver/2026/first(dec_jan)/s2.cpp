#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

#define ll long long
#define v vector
#define pb push_back

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;

    v<ll> l(n), r(n);
    for (int i = 0; i < n; i++)
      cin >> l[i];
    for (int i = 0; i < n; i++)
      cin >> r[i];

    v<v<pair<int, ll>>> g(n);
    for (int i = 0; i < m; i++) {
      int x, y;
      ll z;
      cin >> x >> y >> z;
      x--;
      y--;
      g[x].pb({y, z});
      if (x != y)
        g[y].pb({x, z});
    }

    v<int> p(n, 0);
    v<ll> q(n, 0);
    v<char> vs(n, 0);

    ll ans = 0;
    bool b = false;

    for (int i = 0; i < n && !b; i++) {
      if (vs[i])
        continue;

      deque<int> dq;
      v<int> cn;

      vs[i] = 1;
      p[i] = 1;
      q[i] = 0;
      dq.pb(i);
      cn.pb(i);

      bool fx = false;
      ll x2 = 0;

      while (!dq.empty() && !b) {
        int u = dq.front();
        dq.pop_front();
        for (auto &ed : g[u]) {
          int v = ed.first;
          ll z = ed.second;

          if (!vs[v]) {
            vs[v] = 1;
            p[v] = -p[u];
            q[v] = z - q[u];
            dq.pb(v);
            cn.pb(v);
          } else {
            int s = p[u] + p[v];
            ll rhs = z - q[u] - q[v];

            if (s == 0) {
              if (rhs != 0) {
                b = true;
                break;
              }
            } else {
              ll c2 = (s == 2 ? rhs : -rhs);
              if (!fx) {
                fx = true;
                x2 = c2;
              } else if (x2 != c2) {
                b = true;
                break;
              }
            }
          }
        }
      }

      if (b)
        break;

      if (fx) {
        if (x2 & 1) {
          b = true;
          break;
        }
        ll x = x2 / 2;
        ll cnt = 0;
        for (int u : cn) {
          ll a = p[u] * x + q[u];
          if (a >= l[u] && a <= r[u])
            cnt++;
        }
        ans += cnt;
      } else {
        v<pair<ll, int>> ev;
        for (int u : cn) {
          ll lo, hi;
          if (p[u] == 1) {
            lo = l[u] - q[u];
            hi = r[u] - q[u];
          } else {
            lo = -r[u] + q[u];
            hi = -l[u] + q[u];
          }
          if (lo <= hi) {
            ev.pb({lo, +1});
            ev.pb({hi + 1, -1});
          }
        }

        if (!ev.empty()) {
          sort(ev.begin(), ev.end());
          ll cur = 0, bst = 0;
          for (int j = 0; j < (int)ev.size();) {
            ll x = ev[j].first;
            while (j < (int)ev.size() && ev[j].first == x) {
              cur += ev[j].second;
              j++;
            }
            bst = max(bst, cur);
          }
          ans += bst;
        }
      }
    }

    if (b)
      cout << -1 << "\n";
    else
      cout << ans << "\n";
  }

  return 0;
}
