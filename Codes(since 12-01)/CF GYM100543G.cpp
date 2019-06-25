#include<bits/stdc++.h>

using namespace std;

const int N = 123456, inf = 1e9;

int q, n, tt, last, ch[N][26], half[N], father[N], len[N], ed[N], dp[N][2];
pair<int, int> parent[N];
string s, t;

int new_node(int from) {
  len[++tt] = len[from] + 2;
  return tt;
}

int extend(int i, int c) {
  int p = last;
  while (t[i - 1 - len[p]] - 'A' != c) {
    p = father[p];
  }
  if (!ch[p][c]) {
    int np = new_node(p), q = father[p];
    while (t[i - 1 - len[q]] - 'A' != c) {
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
  cin >> q;
  while (q--) {
    cin >> s;
    n = s.length();
    for (int i = 0; i <= tt; ++i) {
      memset(ch[i], 0, sizeof ch[i]);
      father[i] = half[i] = ed[i] = 0;
    }
    tt = 1;
    last = 0;
    dp[0][0] = dp[1][0] = 0;
    dp[0][1] = dp[1][1] = inf;
    father[0] = 1;
    len[1] = -1;
    t.clear();
    t.push_back('Z' + 1);
    for (int i = 0; i < n; ++i) {
      t.push_back(s[i]);
      ed[extend(i + 1, s[i] - 'A')] = i + 1;
    }
    for (int i = 0; i <= tt; ++i) {
      for (int j = 0; j < 26; ++j) {
        if (ch[i][j]) {
          parent[ch[i][j]] = make_pair(i, j);
        }
      }
    }
    int answer = inf;
    for (int i = 2; i <= tt; ++i) {
      dp[i][0] = min(min(dp[father[i]][0], dp[father[i]][1]) + len[i] - max(0, len[father[i]]), min(dp[parent[i].first][0], dp[parent[i].first][1]) + min(2, len[i]));
      dp[i][1] = dp[parent[i].first][1] + 1;
      if (len[i] >= 2) {
        int p = half[parent[i].first];
        while (len[p] + 2 > (len[i] >> 1) || t[ed[i] - 1 - len[p]] != t[ed[i]]) {
          p = father[p];
        }
        half[i] = ch[p][parent[i].second];
        if (!(len[i] & 1)) {
          dp[i][1] = min(dp[i][1], min(dp[half[i]][0], dp[half[i]][1]) + (len[i] >> 1) - len[half[i]] + 1);
        }
      }
      answer = min(answer, min(dp[i][0], dp[i][1]) + n - len[i]);
    }
    cout << answer << '\n';
  }
  return 0;
}
