#include<bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10, mod = 1e9 + 7;

int n, m, a[N], h[N];
pair<int, int> c[N];

pair<int, int> operator + (const pair<int, int>& a, const pair<int, int>& b) {
  if (a.first > b.first) {
    return a;
  } else if (a.first < b.first) {
    return b;
  } else {
    return {a.first, (a.second + b.second) % mod};
  }
}

void modify(int p, pair<int, int> x) {
  for (; p <= m; p += p & -p) {
    c[p] = c[p] + x;
  }
}

pair<int, int> query(int p) {
  pair<int, int> result(0, 0);
  for (; p; p -= p & -p) {
    result = result + c[p];
  }
  return result;
}

int main() {
  scanf("%d", &n);
  int old = n;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[n + i]);
    h[i] = a[n + i];
  }
  for (int i = n; i; --i) {
    a[i] = a[(n << 1) - i + 1];
  }
  sort(h + 1, h + 1 + n);
  m = unique(h + 1, h + 1 + n) - h - 1;
  n <<= 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(h + 1, h + 1 + m, a[i]) - h;
    pair<int, int> result = query(a[i] - 1);
    if (++result.first == 1) {
      result.second = 1;
    }
    modify(a[i], result);
  }
  pair<int, int> result = query(m);
  for (int i = 1; i < old - result.first; ++i) {
    result.second = (result.second << 1) % mod;
  }
  printf("%d %d\n", result.first, result.first == old ? 1 : result.second);
  return 0;
}
