#include<bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, m, t;
vector<pair<pair<int, int>, int>> edges;
unordered_map<int, int> result;

int dp(int s1, int s2) {
  if (!s1) {
    return 1;
  }
  if (result.count((s1 << n) | s2)) {
    return result[(s1 << n) | s2];
  }
  int must = s1 & -s1, answer = 0;
  for (auto e : edges) {
    if ((e.first.first & s1) == e.first.first && (e.first.second & s2) == e.first.second && (e.first.first & must) == must) {
      add(answer, mul(dp(s1 ^ e.first.first, s2 ^ e.first.second), e.second));
    }
  }
  return result[(s1 << n) | s2] = answer;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int opt, a, b, c, d;
    scanf("%d%d%d", &opt, &a, &b);
    --a;
    --b;
    edges.emplace_back(pair<int, int>(1 << a, 1 << b), 1);
    if (opt > 0) {
      scanf("%d%d", &c, &d);
      --c;
      --d;
      edges.emplace_back(pair<int, int>(1 << c, 1 << d), 1);
      if (a != c && b != d) {
        edges.emplace_back(pair<int, int>((1 << a) | (1 << c), (1 << b) | (1 << d)), opt == 1 ? 1 : mod - 1);
      }
    }
  }
  printf("%d\n", dp((1 << n) - 1, (1 << n) - 1));
  return 0;
}
