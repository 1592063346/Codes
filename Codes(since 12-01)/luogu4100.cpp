#include<bits/stdc++.h>

using namespace std;

const int N = 3e2 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int v, int p) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

int n, a[N][N], b[N][N], inv[N][N], adj[N][N], choice[N], visit[N], tt, answer[N];
vector<int> go[N];

void transform1(int a[N][N], int i, int j) {
  for (int p = 0; p < n; ++p) {
    swap(a[i][p], a[j][p]);
  }
}

void transform2(int a[N][N], int i, int k) {
  for (int p = 0; p < n; ++p) {
    a[i][p] = mul(a[i][p], k);
  }
}

void transform3(int a[N][N], int i, int j, int k) {
  for (int p = 0; p < n; ++p) {
    add(a[i][p], mul(a[j][p], k));
  }
}

void get_adj() {
  int det = 1;
  for (int i = 0; i < n; ++i) {
    inv[i][i] = 1;
  }
  for (int i = 0; i < n; ++i) {
    if (!a[i][i]) {
      int p = i;
      for (int j = i + 1; j < n; ++j) {
        if (a[j][i]) {
          p = j;
        }
      }
      if (p == i) {
        puts("NIE");
        exit(0);
      }
      transform1(a, i, p);
      transform1(inv, i, p);
      det = (mod - det) % mod;
    }
    det = mul(det, a[i][i]);
    int x = qpow(a[i][i], mod - 2);
    transform2(a, i, x);
    transform2(inv, i, x);
    for (int j = i + 1; j < n; ++j) {
      int p = a[j][i];
      transform3(a, j, i, (mod - p) % mod);
      transform3(inv, j, i, (mod - p) % mod);
    }
  }
  for (int i = n - 1; ~i; --i) {
    for (int j = i + 1; j < n; ++j) {
      int p = a[i][j];
      transform3(a, i, j, (mod - p) % mod);
      transform3(inv, i, j, (mod - p) % mod);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      adj[i][j] = mul(inv[j][i], det);
    }
  }
}

bool find(int u) {
  for (auto v : go[u]) {
    if (visit[v] != tt) {
      visit[v] = tt;
      if (!~choice[v] || find(choice[v])) {
        choice[v] = u;
        return true;
      }
    }
  }
  return false;
}

bool find_better(int u, int down) {
  for (auto v : go[u]) {
    if (visit[v] != tt) {
      visit[v] = tt;
      if (choice[v] == down || (choice[v] > down && find_better(choice[v], down))) {
        answer[u] = v;
        choice[v] = u;
        return true;
      }
    }
  }
  return false;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &b[i][j]);
    }
  }
  get_adj();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int det = 0;
      for (int k = 0; k < n; ++k) {
        add(det, mul(b[j][k], adj[i][k]));
      }
      if (det) {
        go[i].push_back(j);
      }
    }
  }
  memset(choice, -1, sizeof choice);
  int total = 0;
  for (int i = 0; i < n; ++i) {
    ++tt;
    total += find(i);
  }
  if (total != n) {
    puts("NIE");
  } else {
    puts("TAK");
    for (int i = 0; i < n; ++i) {
      ++tt;
      find_better(i, i);
      printf("%d\n", answer[i] + 1);
    }
  }
  return 0;
}
