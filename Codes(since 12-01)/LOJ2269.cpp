#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>

using namespace std;

const int N = 3e4 + 10, mod = 10007;

short add(short x, short y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
  return x;
}

short sub(short x, short y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
  return x;
}

short mul(short x, short y) {
  return (int) x * y % mod;
}

int n, m, q, value[N], ch[N][2], father[N], inv_value[mod];
vector<int> adj[N];

struct polygon_t {
  short buffer[128], number0[128];

  polygon_t() {
    memset(buffer, 0, sizeof buffer);
    memset(number0, 0, sizeof number0);
  }

  short value(int x) {
    return number0[x] ? 0 : buffer[x];
  }

  polygon_t operator + (polygon_t b) {
    polygon_t result;
    for (int i = 0; i < m; ++i) {
      result.buffer[i] = add(value(i), b.value(i));
      result.number0[i] = !result.buffer[i];
    }
    return result;
  }

  polygon_t operator - (polygon_t b) {
    polygon_t result;
    for (int i = 0; i < m; ++i) {
      result.buffer[i] = sub(value(i), b.value(i));
      result.number0[i] = !result.buffer[i];
    }
    return result;
  }

  polygon_t operator * (polygon_t b) {
    polygon_t result = *this;
    for (int i = 0; i < m; ++i) {
      if (!b.value(i)) {
        ++result.number0[i];
      } else {
        result.buffer[i] = mul(buffer[i], b.value(i));
      }
    }
    return result;
  }

  polygon_t operator / (polygon_t b) {
    polygon_t result = *this;
    for (int i = 0; i < m; ++i) {
      if (!b.value(i)) {
        --result.number0[i];
      } else {
        result.buffer[i] = mul(buffer[i], inv_value[b.value(i)]);
      }
    }
    return result;
  }

  void fwt(bool inv = false) {
    for (int i = 0; i < m; ++i) {
      buffer[i] = value(i);
    }
    for (int i = 1; i < m; i <<= 1) {
      for (int j = 0; j < m; j += i << 1) {
        for (int k = 0; k < i; ++k) {
          short p = buffer[j + k], q = buffer[i + j + k];
          if (!inv) {
            buffer[j + k] = add(p, q);
            buffer[i + j + k] = sub(p, q);
          } else {
            buffer[j + k] = mul(add(p, q), inv_value[2]);
            buffer[i + j + k] = mul(sub(p, q), inv_value[2]);
          }
        }
      }
    }
  }
} E, f[N], g[N], initial[128];

struct matrix_t {
  polygon_t a00, a01, a20, a21;

  void init(int u) {
    a00 = a01 = a20 = f[u];
    a21 = f[u] + g[u];
  }

  matrix_t operator * (matrix_t b) {
    matrix_t result;
    result.a00 = a00 * b.a00;
    result.a01 = a00 * b.a01 + a01;
    result.a20 = a20 * b.a00 + b.a20;
    result.a21 = a20 * b.a01 + a21 + b.a21;
    return result;
  }
} info[N];

void dfs(int u, int p) {
  f[u] = initial[value[u]];
  for (auto v : adj[u]) {
    if (v != p) {
      father[v] = u;
      dfs(v, u);
      f[u] = f[u] * (info[v].a20 + E);
      g[u] = g[u] + info[v].a21;
    }
  }
  info[u].init(u);
}

bool is_root(int u) {
  return ch[father[u]][0] != u && ch[father[u]][1] != u;
}

int side(int f, int u) {
  return ch[f][1] == u;
}

void pull(int u) {
  info[u].init(u);
  if (ch[u][0]) {
    info[u] = info[u] * info[ch[u][0]];
  }
  if (ch[u][1]) {
    info[u] = info[ch[u][1]] * info[u];
  }
}

void rotate(int u) {
  int f = father[u], s1 = side(f, u), s2 = side(father[f], f), ano = ch[u][!s1];
  father[u] = father[f];
  if (!is_root(f)) {
    ch[father[f]][s2] = u;
  }
  father[ano] = f;
  ch[f][s1] = ano;
  father[f] = u;
  ch[u][!s1] = f;
  pull(f);
  pull(u);
}

void splay(int u) {
  for (; !is_root(u); rotate(u)) {
    int f = father[u];
    if (!is_root(f)) {
      if (side(f, u) == side(father[f], f)) {
        rotate(f);
      } else {
        rotate(u);
      }
    }
  }
}

void access(int u) {
  for (int x = 0; u; x = u, u = father[u]) {
    splay(u);
    if (ch[u][1]) {
      f[u] = f[u] * (info[ch[u][1]].a20 + E);
      g[u] = g[u] + info[ch[u][1]].a21;
    }
    ch[u][1] = x;
    if (ch[u][1]) {
      f[u] = f[u] / (info[ch[u][1]].a20 + E);
      g[u] = g[u] - info[ch[u][1]].a21;
    }
    pull(u);
  }
}

int main() {
  inv_value[1] = 1;
  for (int i = 2; i < mod; ++i) {
    inv_value[i] = (mod - mod / i) * inv_value[mod % i] % mod;
  }
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    E.buffer[i] = 1;
  }
  for (int i = 0; i < m; ++i) {
    ++initial[i].buffer[i];
    initial[i].fwt();
    for (int j = 0; j < m; ++j) {
      if (!initial[i].buffer[j]) {
        initial[i].buffer[j] = 1;
        initial[i].number0[j] = 1;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &value[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(1, 0);
  scanf("%d", &q);
  char cmd[7];
  while (q--) {
    int x, y;
    scanf("%s", cmd);
    if (*cmd == 'Q') {
      scanf("%d", &x);
      splay(1);
      polygon_t answer = info[1].a21;
      answer.fwt(true);
      printf("%d\n", answer.buffer[x]);
    } else {
      scanf("%d%d", &x, &y);
      access(x);
      splay(x);
      polygon_t p = initial[value[x]], q = initial[y];
      value[x] = y;
      f[x] = f[x] / p * q;
      pull(x);
    }
  }
  return 0;
}
