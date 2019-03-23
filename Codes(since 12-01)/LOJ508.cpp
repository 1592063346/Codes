#include<bits/stdc++.h>

using namespace std;

template<typename T>
void read(T& x) {
  char c = getchar();
  bool f = false;
  for (x = 0; !isdigit(c); c = getchar()) {
    if (c == '-') {
      f = true;
    }
  }
  for (; isdigit(c); c = getchar()) {
    x = x * 10 + c - '0';
  }
  if (f) {
    x = -x;
  }
}

template<typename T, typename... others>
void read(T& x, others&... y) {
  read(x), read(y...);
}

const int N = 1e6 + 10;

int n, m, q, father[N], gcd[N], value[N];

void exgcd(int a, int b, int& d, int& x, int& y) {
  if (!b) {
    d = a;
    x = 1;
    y = 0;
  } else {
    exgcd(b, a % b, d, y, x);
    y -= x * (a / b);
  }
}

int find(int x) {
  if (father[x] == x) {
    return x;
  } else {
    int p = father[x];
    father[x] = find(father[x]);
    value[x] = (value[x] + value[p]) % m;
    return father[x];
  }
}

void link(int u, int v, int w) {
  int x = find(u), y = find(v);
  if (x != y) {
    gcd[y] = __gcd(gcd[y], __gcd(gcd[x], w << 1));
    value[x] = ((w + value[u]) % m + value[v]) % m;
    father[x] = y;
  } else {
    gcd[y] = __gcd(gcd[y], __gcd(((w + value[u]) % m + value[v]) % m, w << 1));
  }
}

int main() {
  read(n, m, q);
  for (int i = 1; i <= n; ++i) {
    father[i] = i;
  }
  while (q--) {
    int opt, u, v, x, b, c;
    read(opt, u, v, x);
    if (opt == 1) {
      link(u, v, x);
    } else {
      read(b, c);
      if (find(u) != find(v)) {
        puts("0");
      } else {
        int g = __gcd(m, gcd[find(u)]);
        x = ((value[u] + value[v] - x) % g + g) % g;
        int d, s, t;
        exgcd(g, b, d, s, t);
        if (x % d) {
          puts("0");
        } else {
          int diff = g / d, kmin = ((long long) t * (x / d) % diff + diff) % diff;
          if (kmin > c - 1) {
            puts("0");
          } else {
            printf("%d\n", 1 + (c - 1 - kmin) / (g / __gcd(b, g)));
          }
        }
      }
    }
  }
  return 0;
}
