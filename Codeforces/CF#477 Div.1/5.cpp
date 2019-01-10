#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, q, sq, que[N], father[N], dfn[N], rdfn[N], dfn_t, value[N], size[N], vir_f[N], vir_s[N], vir_v[N], vir_p[N];
bool vir_t[N], vacation[N];
vector<int> graph[N], num[N];

void dfs(int u) {
  rdfn[dfn[u] = ++dfn_t] = u;
  for (auto v : graph[u]) {
    dfs(v);
  }
}

int main() {
  scanf("%d%d", &n, &q);
  sq = sqrt(max(n, q));
  for (int i = 2; i <= n; ++i) {
    scanf("%d", &father[i]);
    graph[father[i]].push_back(i);
  }
  dfs(1);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &value[i]);
  }
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &que[i]);
    if (que[i] < 0) {
      que[i] = -que[i];
    }
  }
  int answer;
  for (int l = 1, r = min(sq, q); l != q + 1; l = r + 1, r = min(l + sq - 1, q)) {
    answer = 0;
    memset(size, 0, sizeof size);
    memset(vir_t, false, sizeof vir_t);
    memset(vir_v, 0, sizeof vir_v);
    memset(vir_s, 0, sizeof vir_s);
    memset(vir_p, 0, sizeof vir_p);
    for (int i = 1; i <= n; ++i) {
      num[i].clear();
    }
    for (int i = n; i; --i) {
      int u = rdfn[i];
      if (vacation[u]) {
        ++size[u];
      } else if (value[u] < size[u]) {
        ++answer;
      }
      if (father[u]) {
        size[father[u]] += size[u];
      }
    }
    for (int i = l; i <= r; ++i) {
      vir_t[que[i]] = true;
    }
    for (int i = n; i; --i) {
      int u = rdfn[i];
      if (vir_t[u] || vir_s[u]) {
        ++vir_s[father[u]];
      }
    }
    for (int i = 1; i <= n; ++i) {
      if (vir_s[i] >= 2) {
        vir_t[i] = true;
      }
    }
    for (int i = 1; i <= n; ++i) {
      if (vir_t[i]) {
        int j = father[i];
        for (; j && !vir_t[j]; j = father[j]) {
          if (!vacation[j]) {
            int x = value[j] - size[j];
            if (x < 0) {
              ++vir_p[i];
            }
            num[i].push_back(x);
          }
        }
        vir_f[i] = j;
        sort(num[i].begin(), num[i].end());
      }
    }
    for (int i = l; i <= r; ++i) {
      int x = que[i];
      bool type = vacation[x];
      vacation[x] = !vacation[x];
      if (value[x] < size[x] + vir_v[x]) {
        if (type) {
          ++answer;
        } else {
          --answer;
        }
      }
      for (; x; x = vir_f[x]) {
        if (!vacation[x] && value[x] < size[x] + vir_v[x]) {
          --answer;
        }
        if (type) {
          --vir_v[x];
        } else {
          ++vir_v[x];
        }
        if (!vacation[x] && value[x] < size[x] + vir_v[x]) {
          ++answer;
        }
        answer -= vir_p[x];
        vir_p[x] = lower_bound(num[x].begin(), num[x].end(), vir_v[x]) - num[x].begin();
        answer += vir_p[x];
      }
      printf("%d%c", answer, " \n"[i == q]);
    }
  }
  return 0;
}
