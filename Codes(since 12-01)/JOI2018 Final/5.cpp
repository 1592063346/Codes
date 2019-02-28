#include<bits/stdc++.h>

using namespace std;

const int N = 1 << 20;

int n, q, l, size[N], f[N], g[N];
char value[N], t[N];

void fmt(int* f) {
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j += i << 1) {
      for (int k = 0; k < i; ++k) {
        f[i + j + k] += f[j + k];
      }
    }
  }
}

int main() {
  scanf("%d%d%s", &n, &q, value);
  l = n;
  n = 1 << n;
  for (int i = 1; i < n; ++i) {
    size[i] = size[i - (i & -i)] + 1;
  }
  for (int i = 0; i < n; ++i) {
    f[i] = value[i] - '0';
    g[i] = value[(n - 1) ^ i] - '0';
  }
  fmt(f);
  fmt(g);
  while (q--) {
    scanf("%s", t);
    int s0 = 0, s1 = 0, s2 = 0;
    reverse(t, t + l);
    for (int i = 0; i < l; ++i) {
      if (t[i] == '0') {
        s0 |= 1 << i;
      } else if (t[i] == '1') {
        s1 |= 1 << i;
      } else {
        s2 |= 1 << i;
      }
    }
    int answer = 0;
    if (size[s0] <= 6) {
      for (int i = s0;; i = (i - 1) & s0) {
        if (size[s0 ^ i] & 1) {
          answer -= g[i | s2];
        } else {
          answer += g[i | s2];
        }
        if (!i) {
          break;
        }
      }
    } else if (size[s1] <= 6) {
      for (int i = s1;; i = (i - 1) & s1) {
        if (size[s1 ^ i] & 1) {
          answer -= f[i | s2];
        } else {
          answer += f[i | s2];
        }
        if (!i) {
          break;
        }
      }
    } else {
      for (int i = s2;; i = (i - 1) & s2) {
        answer += value[s1 | i] - '0';
        if (!i) {
          break;
        }
      }
    }
    printf("%d\n", answer);
  }
  return 0;
}
