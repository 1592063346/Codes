#include<bits/stdc++.h>

using namespace std;

const int N = 5e4 + 10;

int n, m, k, x, y, ql[305], qr[305];
vector<int> sets[N];
pair<pair<int, int>, int> que[305][N];
long long dp[305][N], s[N];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &x, &y);
    m = max(m, x);
    sets[x].push_back(y);
  }
  for (int i = 1; i <= m; ++i) {
    sort(sets[i].begin(), sets[i].end(), greater<int>());
    memset(s, 0, sizeof s);
    for (int j = i; j <= k && j / i <= sets[i].size(); j += i) {
      s[j] = s[j - i] + sets[i][j / i - 1];
    }
    for (int j = 1; j <= k; ++j) {
      s[j] = max(s[j], s[j - 1]);
    }
    for (int j = 0; j < i; ++j) {
      que[j][ql[j] = qr[j] = 0] = {{j, k}, j};
    }
    for (int j = 1; j <= k; ++j) {
      int team = j % i;
      for (; que[team][ql[team]].first.second < j; ++ql[team]);
      que[team][ql[team]].first.first = j;
      int p = que[team][ql[team]].second;
      dp[i][j] = max(dp[i - 1][j], dp[i - 1][p] + s[j - p]);
      while (ql[team] <= qr[team]) {
        int l = que[team][qr[team]].first.first, r = que[team][qr[team]].first.second, p = que[team][qr[team]].second;
        while (l != r) {
          int mid = (l + r >> 1) + 1;
          if (dp[i - 1][j] + s[mid - j] >= dp[i - 1][p] + s[mid - p]) {
            r = mid - 1;
          } else {
            l = mid;
          }
        }
        if (dp[i - 1][j] + s[l - j] >= dp[i - 1][p] + s[l - p]) {
          --qr[team];
        } else {
          if (l < k) {
            que[team][qr[team]].first.second = l;
            que[team][++qr[team]] = {{l + 1, k}, j};
          }
          break;
        }
      }
      if (ql[team] > qr[team]) {
        que[team][++qr[team]] = {{j, k}, j};
      }
    }
  }
  for (int i = 1; i <= k; ++i) {
    printf("%lld%c", dp[m][i], " \n"[i == k]);
  }
  return 0;
}
