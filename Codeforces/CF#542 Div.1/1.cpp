#include<bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10;

int n, m;
vector<int> go[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    go[x].push_back(y >= x ? y - x : (y + n) - x);
  }
  for (int i = 1; i <= n; ++i) {
    sort(go[i].begin(), go[i].end());
  }
  for (int i = 1; i <= n; ++i) {
    int answer = 0;
    for (int j = i; j < i + n; ++j) {
      int x = j > n ? j - n : j;
      if (go[x].size()) {
        answer = max(answer, j - i + ((int) go[x].size() - 1) * n + go[x][0]);
      }
    }
    printf("%d%c", answer, " \n"[i == n]);
  }
  return 0;
}
