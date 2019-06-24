#include<bits/stdc++.h>

using namespace std;

const int N = 345678;

int n, last, tt, ch[N][26], father[N], len[N], sum[N];
string s, t;

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
    ch[p][c] = np;
  }
  return last = ch[p][c];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> s;
  n = s.length();
  tt = 1;
  len[1] = -1;
  father[0] = 1;
  t.push_back('z' + 1);
  for (int i = 0; i < n; ++i) {
    t.push_back(s[i]);
    ++sum[extend(i + 1, s[i] - 'a')];
  }
  long long answer = 0;
  for (int i = tt; i > 1; --i) {
    sum[father[i]] += sum[i];
    answer = max(answer, (long long) sum[i] * len[i]);
  }
  cout << answer << '\n';
  return 0;
}
