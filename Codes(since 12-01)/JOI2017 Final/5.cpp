#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int n, m, c[N], t[N], number[N], p_number[N], answer[N];
vector<int> go[N];

void solve() {
  for (int i = 1; i <= m; ++i) {
    for (auto v : go[i]) {
      ++p_number[v];
    }
    int most_remaining = 0;
    for (auto v : go[i]) {
      cmax(most_remaining, number[v] - p_number[v]);
    }
    for (int j = 1; j <= m; ++j) {
      if (t[j] != i && !p_number[t[j]]) {
        cmax(most_remaining, number[t[j]]);
        break;
      }
    }
    cmin(answer[i], n - number[i] - most_remaining);
    for (auto v : go[i]) {
      --p_number[v];
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &c[i]);
    ++number[c[i]];
  }
  for (int i = 1; i <= n; ++i) {
    t[i] = i;
  }
  sort(t + 1, t + 1 + n, [&] (const int& x, const int& y) {
    return number[x] > number[y];
  });
  memset(answer, 0x3f, sizeof answer); 
  for (int i = 1; i < n; i += 2) {
    if (c[i] != c[i + 1]) {
      go[c[i]].push_back(c[i + 1]);
      go[c[i + 1]].push_back(c[i]);
    }
  }
  solve();
  for (int i = 1; i <= m; ++i) {
    go[i].clear();
  }
  for (int i = 2; i < n; i += 2) {
    if (c[i] != c[i + 1]) {
      go[c[i]].push_back(c[i + 1]);
      go[c[i + 1]].push_back(c[i]);
    }
  }
  solve();
  for (int i = 1; i <= m; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
