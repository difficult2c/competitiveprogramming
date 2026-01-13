#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
#define v vector
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int t;
  cin >> t;
  while (t--) {
	int n, k;
	string r;
	cin >> n >> k >> r;

	int m = n - k + 1;
	v<int> rb(m);
	for (int i = 0; i < m; i++)
	  rb[i] = (r[i] == '1');

	v<int> a(max(0, n - k));
	for (int i = 0; i + 1 < m; i++)
	  a[i] = rb[i] ^ rb[i + 1];

	v<ll> d;
	d.reserve(k);

	ll b0 = 0;
	int zc = 0;

	for (int s = 0; s < k; s++) {
	  int p = 0;
	  ll c0 = 0, ln = 0;
	  for (int i = s; i < n; i += k) {
		if (p)
		  c0++;
		ln++;
		if (i <= n - k - 1)
		  p ^= a[i];
	  }
	  b0 += c0;
	  ll dv = ln - 2 * c0;
	  d.push_back(dv);
	  if (dv == 0)
		zc++;
	}

	int pr = rb[0];

	v<ll> ps, ng;
	for (ll x : d) {
	  if (x > 0)
		ps.push_back(x);
	  else if (x < 0)
		ng.push_back(x);
	}

	sort(ps.begin(), ps.end());
	sort(ng.begin(), ng.end());

	ll sn = 0;
	for (ll x : ng)
	  sn += x;

	ll mn;
	if ((int)ng.size() % 2 == pr) {
	  mn = b0 + sn;
	} else if (zc) {
	  mn = b0 + sn;
	} else {
	  ll ad = LLONG_MAX;
	  if (!ng.empty())
		ad = min(ad, -ng.back());
	  if (!ps.empty())
		ad = min(ad, ps.front());
	  mn = b0 + sn + ad;
	}

	ll sp = 0;
	for (ll x : ps)
	  sp += x;

	ll mx;
	if ((int)ps.size() % 2 == pr) {
	  mx = b0 + sp;
	} else if (zc) {
	  mx = b0 + sp;
	} else {
	  ll bd = LLONG_MIN;
	  if (!ps.empty())
		bd = max(bd, -ps.front());
	  if (!ng.empty())
		bd = max(bd, ng.back());
	  mx = b0 + sp + bd;
	}

	mn = max(0LL, min((ll)n, mn));
	mx = max(0LL, min((ll)n, mx));

	cout << mn << " " << mx << "\n";
  }
  return 0;
}
