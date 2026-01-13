#include <iostream>
using namespace std;

#define ll long long

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int q;
  cin >> q;

  while (q--) {
    int v;
    ll cx, t;
    cin >> v >> cx >> t;

    if (v == 1) {
      ll c = cx;

      if (c == 0) {
        ll k = 0, qv = 0;
        while (k < t) {
          ll z = t - k;
          if (qv > 0) {
            ll f = min(qv, z);
            qv -= f;
            k += f;
          } else {
            k += 1;
            qv = k / 2;
          }
        }
        cout << qv << "\n";
      } else {
        if (t <= 2 * c - 1) {
          cout << c << "\n";
        } else {
          ll k = 2 * c;
          ll qv = c - 1;

          while (k < t) {
            ll z = t - k;
            if (qv > 0) {
              ll f = min(qv, z);
              qv -= f;
              k += f;
            } else {
              k += 1;
              qv = k / 2;
            }
          }
          cout << qv << "\n";
        }
      }

    } else {
      ll x = cx;

      if (t == 0) {
        cout << 0 << "\n";
      } else {
        ll k = t;
        while (k > 0 && x <= k / 2) {
          if (x < k / 2) {
            ll num = k - 2 * x - 2;
            ll f = num / 3 + 1;
            k -= f;
            x += f;
          } else {
            k -= 1;
            x = 0;
          }
        }
        cout << x << "\n";
      }
    }
  }

  return 0;
}
