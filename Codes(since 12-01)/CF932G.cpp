#include<bits/stdc++.h>

using namespace std;

const int N = 1234567, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int n, last, tt, ch[N][26], father[N], len[N], diff[N], anc[N], sum[N], dp[N];
string r, s, t;

int new_node(int from) {
  len[++tt] = len[from] + 2;
  return tt;
}

int extend(int i, int c) {
  int p = last;
  while (t[i - 1 - len[p]] - 'a' != c) {
    p = father[p];
  }
  if (!ch[p][c]) {
    int np = new_node(p), q = father[p];
    while (t[i - 1 - len[q]] - 'a' != c) {
      q = father[q];
    }
    father[np] = ch[q][c];
    diff[np] = len[np] - len[father[np]];
    anc[np] = diff[np] == diff[father[np]] ? anc[father[np]] : father[np];
    ch[p][c] = np;
  }
  return last = ch[p][c];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> r;
  n = r.length();
  if (n & 1) {
    cout << 0 << '\n';
    exit(0);
  }
  for (int i = 0; i < (n >> 1); ++i) {
    s.push_back(r[i]);
    s.push_back(r[n - i - 1]);
  }
  tt = 1;
  len[1] = -1;
  father[0] = 1;
  t.push_back('z' + 1);
  dp[0] = 1;
  for (int i = 1; i <= n; ++i) {
    t.push_back(s[i - 1]);
    int here = extend(i, s[i - 1] - 'a');
    for (int j = here; j > 1; j = anc[j]) {
      sum[j] = dp[i - (len[anc[j]] + diff[j])];
      if (father[j] != anc[j]) {
        add(sum[j], sum[father[j]]);
      }
      if (!(i & 1)) {
        add(dp[i], sum[j]);
      }
    }
  }
  cout << dp[n] << '\n';
  return 0;
}
