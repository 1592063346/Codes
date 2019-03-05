#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, inf = 0x3f3f3f3f;

struct query_t {
  int l, r, s, id;

  query_t() {}
  query_t(int l, int r, int s, int id): l(l), r(r), s(s), id(id) {}
};

int n, m, q, alpha, M, number[N], x[N], y[N], suffix_array[N], suffix_rank[N], height[20][N], logv[N], root[N], node_cnt, go[20][N], minp[N], maxp[N], w[N];
long long answer[N], sump[20][N];
vector<query_t> queries[55];
char a[N];

void build_sa(int n, int m) {
  for (int i = 0; i < n; ++i) {
    ++number[x[i] = a[i]];
  }
  for (int i = 1; i < m; ++i) {
    number[i] += number[i - 1];
  }
  for (int i = n - 1; ~i; --i) {
    suffix_array[--number[x[i]]] = i;
  }
  for (int k = 1; k <= n; k <<= 1) {
    int p = 0;
    for (int i = n - 1; i >= n - k; --i) {
      y[p++] = i;
    }
    for (int i = 0; i < n; ++i) {
      if (suffix_array[i] >= k) {
        y[p++] = suffix_array[i] - k;
      }
    }
    for (int i = 0; i < m; ++i) {
      number[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
      ++number[x[y[i]]];
    }
    for (int i = 1; i < m; ++i) {
      number[i] += number[i - 1];
    }
    for (int i = n - 1; ~i; --i) {
      suffix_array[--number[x[y[i]]]] = y[i];
    }
    swap(x, y);
    p = 1;
    x[suffix_array[0]] = 0;
    for (int i = 1; i < n; ++i) {
      x[suffix_array[i]] = y[suffix_array[i]] == y[suffix_array[i - 1]] && y[suffix_array[i] + k] == y[suffix_array[i - 1] + k] ? p - 1 : p++;
    }
    if (p >= n) {
      break;
    }
    m = p;
  }
}

void height_init(int n) {
  for (int i = 0; i < n; ++i) {
    suffix_rank[suffix_array[i]] = i;
  }
  for (int i = 0, k = 0; i < n; ++i) {
    if (k) {
      --k;
    }
    if (suffix_rank[i]) {
      int j = suffix_array[suffix_rank[i] - 1];
      while (a[i + k] == a[j + k]) {
        ++k;
      }
      height[0][suffix_rank[i]] = k;
    }
  }
  for (int i = 2; i <= n; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int i = 1; (1 << i) <= n; ++i) {
    for (int j = 0; j + (1 << i) - 1 < n; ++j) {
      height[i][j] = min(height[i - 1][j], height[i - 1][j + (1 << i - 1)]);
    }
  }
}

int get_lcp(int x, int y) {
  if (x == y) {
    return m - x;
  }
  x = suffix_rank[x];
  y = suffix_rank[y];
  if (x > y) {
    swap(x, y);
  }
  ++x;
  int k = logv[y - x + 1];
  return min(height[k][x], height[k][y - (1 << k) + 1]);
}

struct node_t {
  int lo, ro, sum;

  node_t() {}
  node_t(int lo, int ro, int sum): lo(lo), ro(ro), sum(sum) {}
} nodes[N * 20];

int insert(int l, int r, int& o, int p) {
  int x = ++node_cnt;
  nodes[x] = node_t(nodes[o].lo, nodes[o].ro, nodes[o].sum + 1);
  if (l != r) {
    int mid = l + r >> 1;
    if (p <= mid) {
      nodes[x].lo = insert(l, mid, nodes[o].lo, p);
    } else {
      nodes[x].ro = insert(mid + 1, r, nodes[o].ro, p);
    }
  }
  return x;
}

int query(int l, int r, int o1, int o2, int p) {
  if (!o2 || nodes[o2].sum - nodes[o1].sum == 0) {
    return inf;
  }
  if (l == r) {
    return l;
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      int result = query(l, mid, nodes[o1].lo, nodes[o2].lo, p);
      if (result != inf) {
        return result;
      }
    }
    return query(mid + 1, r, nodes[o1].ro, nodes[o2].ro, p);
  }
}

pair<int, int> find_interval(int from, int to) {
  int len = to - from + 1, l, r, ql, qr;
  l = 0;
  r = suffix_rank[from];
  while (l != r) {
    int mid = l + r >> 1;
    if (get_lcp(suffix_array[mid], from) >= len) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  ql = l;
  l = suffix_rank[from];
  r = m - 1;
  while (l != r) {
    int mid = (l + r >> 1) + 1;
    if (get_lcp(suffix_array[mid], from) >= len) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  qr = l;
  return {ql, qr};
}

long long solve(int s, int t, int from, int to) {
  pair<int, int> interval = find_interval(from, to);
  long long answer = 0;
  while (s <= t) {
    int p = query(0, m - 1, root[interval.first], root[interval.second + 1], s);
    if (p <= t) {
      answer += alpha - p - 1;
      s = p + to - from + 1;
    } else {
      break;
    }
  }
  return answer;
}

int main() {
  scanf("%d%d", &n, &alpha);
  scanf("%s%s", a, a + n + 1);
  m = n << 1 | 1;
  M = min(n, 50);
  a[n] = '#';
  build_sa(m, 'z' + 1);
  height_init(m);
  for (int i = 1; i <= m; ++i) {
    root[i] = insert(0, m - 1, root[i - 1], suffix_array[i - 1]);
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    int s, t, l, r;
    scanf("%d%d%d%d", &s, &t, &l, &r);
    if (t - s >= r - l) {
      if (r - l + 1 <= M) {
        queries[r - l + 1].emplace_back(s - 1, t - 1 - r + l, n + l, i);
      } else {
        answer[i] = solve(s - 1, t - 1 - r + l, n + l, n + r);
      }
    }
  }
  for (int len = 1; len <= M; ++len) {
    if (!queries[len].size()) {
      continue;
    }
    for (int i = m - 1, j = m - 1; i >= -1; --i) {
      if (i == -1 || get_lcp(suffix_array[i], suffix_array[j]) < len) {
        for (int k = i + 1; k <= j; ++k) {
          maxp[suffix_array[k]] = j;
        }
        j = i;
      }
    }
    for (int i = 0, j = 0; i <= m; ++i) {
      if (i == m || get_lcp(suffix_array[i], suffix_array[j]) < len) {
        for (int k = j; k < i; ++k) {
          minp[suffix_array[k]] = j;
        }
        j = i;
      }
    }
    memset(w, 0x3f, sizeof w);
    for (int i = n - 1, j = n - len; ~i; --i) {
      if (i + len <= j) {
        w[minp[j]] = j;
        --j;
      }
      go[0][i] = i + len - 1 < n ? w[minp[i]] : inf;
      sump[0][i] = i + 1;
    }
    for (int j = n - 1; ~j; --j) {
      for (int i = 1; i < 17; ++i) {
        go[i][j] = go[i - 1][j] < n ? go[i - 1][go[i - 1][j]] : inf;
        sump[i][j] = sump[i - 1][j] + (go[i - 1][j] < n ? sump[i - 1][go[i - 1][j]] : 0);
      }
    }
    for (auto v : queries[len]) {
      int p = query(0, m - 1, root[minp[v.s]], root[maxp[v.s] + 1], v.l);
      if (p <= v.r) {
        for (int i = 16; ~i; --i) {
          if (go[i][p] <= v.r) {
            answer[v.id] += (long long) alpha * (1 << i) - sump[i][p];
            p = go[i][p];
          }
        }
        answer[v.id] += alpha - p - 1;
      }
    }
  }
  for (int i = 1; i <= q; ++i) {
    printf("%lld\n", answer[i]);
  }
  return 0;
}
