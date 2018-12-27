#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, q, a[N], pre_max[N], suf_max[N];
vector<int> pos[N];
long long c[N];

void modify(int p, int value) {
  for (; p <= n; p += p & -p) {
    c[p] += value;
  }
}

long long query(int p) {
  long long result = 0;
  for (; p; p -= p & -p) {
    result += c[p];
  }
  return result;
}

long long query(int l, int r) {
  return query(r) - query(l - 1);
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    pos[a[i]].push_back(i);
  }
  for (int i = 1; i <= q; ++i) {
    for (int j = 0; j + 1 < pos[i].size(); ++j) {
      int l = pos[i][j], r = pos[i][j + 1];
      if (query(l + 1, r - 1)) {
        return puts("NO"), 0;
      }
      modify(l, i);
    }
    if (pos[i].size()) {
      modify(pos[i].back(), i);
    }
  }
  for (int i = 1; i <= n; ++i) {
    pre_max[i] = max(pre_max[i - 1], a[i]);
  }
  for (int i = n; i; --i) {
    suf_max[i] = max(suf_max[i + 1], a[i]);
  }
  a[0] = 1;
  bool appeared_q = false;
  for (int i = 1; i <= n; ++i) {
    if (!a[i]) {
      a[i] = a[i - 1];
      if (!appeared_q && pre_max[i - 1] < q && suf_max[i + 1] < q) {
        a[i] = q;
      }
    }
    if (a[i] == q) {
      appeared_q = true;
    }
  }
  if (!appeared_q) {
    puts("NO");
  } else {
    puts("YES");
    for (int i = 1; i <= n; ++i) {
      printf("%d%c", a[i], " \n"[i == n]);
    }
  }
  return 0;
}
