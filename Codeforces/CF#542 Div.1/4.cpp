#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, M = 320, mod = 998244353;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

void sub(int& x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}

int n, k, now, f[N], g[N], belong[N], a[N], pre_p[N], last_p[N], tag[M], answer;

template<typename T>
struct my_array {
  T a[N << 1];

  T& operator [] (int x) {
    return a[N + x];
  }
};

my_array<int> sum[M];

void update(int i, int v) {
  sub(sum[belong[i]][g[i]], f[i]);
  g[i] += v;
  add(sum[belong[i]][g[i]], f[i]);
  if (v == -1) {
    if (g[i] + tag[belong[i]] == k) {
      add(answer, f[i]);
    }
  } else {
    if (g[i] + tag[belong[i]] == k + 1) {
      sub(answer, f[i]);
    }
  }
}

void modify(int l, int r, int v) {
  if (l > r) {
    return;
  }
  for (int i = belong[l] + 1; i < belong[r]; ++i) {
    tag[i] += v;
    if (v == -1) {
      add(answer, sum[i][k - tag[i]]);
    } else {
      sub(answer, sum[i][k + 1 - tag[i]]);
    }
  }
  if (belong[l] != belong[r]) {
    for (int i = l; i < (belong[l] + 1) * M; ++i) {
      update(i, v);
    }
    for (int i = belong[r] * M; i <= r; ++i) {
      update(i, v);
    }
  } else {
    for (int i = l; i <= r; ++i) {
      update(i, v);
    }
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i <= n; ++i) {
    belong[i] = i / M;
  }
  f[0] = 1;
  g[0] = 0;
  sum[0][0] = 1;
  answer = 1;
  for (now = 1; now <= n; ++now) {
    modify(pre_p[last_p[a[now]]], last_p[a[now]] - 1, -1);
    modify(last_p[a[now]], now - 1, 1);
    f[now] = answer;
    g[now] = 0 - tag[belong[now]];
    add(sum[belong[now]][g[now]], f[now]);
    add(answer, f[now]);
    pre_p[now] = last_p[a[now]];
    last_p[a[now]] = now;
  }
  printf("%d\n", f[n]);
  return 0;
}
