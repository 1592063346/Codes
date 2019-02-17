#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, M = 45;

int n, q, f[N], answer[N], final[N * M], ch[N * M][2], node_cnt;
vector<pair<int, int>> queries[N];
char s[N];

int main() {
  scanf("%d%d%s", &n, &q, s + 1);
  for (int i = 1; i <= q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    queries[r].emplace_back(l, i);
  }
  for (int i = 1; i <= n; ++i) {
    int u = 0;
    for (int j = i; j <= min(n, i + M - 1); ++j) {
      int c = s[j] - '0';
      if (!ch[u][c]) {
        ch[u][c] = ++node_cnt;
      } else {
        f[j - i + 1] = max(f[j - i + 1], final[ch[u][c]]);
      }
      u = ch[u][c];
      final[u] = i;
    }
    for (auto que : queries[i]) {
      for (int j = 1; j <= M; ++j) {
        if (f[j] >= que.first) {
          answer[que.second] += j * (f[j] - max(f[j + 1], que.first - 1));
        } else {
          break;
        }
      }
    }
  }
  for (int i = 1; i <= q; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
