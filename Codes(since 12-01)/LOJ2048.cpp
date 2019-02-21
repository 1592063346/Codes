#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, m, q, maxa[N], maxb[N], father[N], size[N];
bool answer[N];

struct event_t {
  int u, v, a, b, id;
} events[N << 1];

bool cmp_a(const event_t& a, const event_t& b) {
  return a.a == b.a ? a.b == b.b ? a.id < b.id : a.b < b.b : a.a < b.a;
}

bool cmp_b(const event_t& a, const event_t& b) {
  return a.b == b.b ? a.a < b.a : a.b < b.b;
}

struct stack_info_t {
  int u, v, fu, fv, sizeu, sizev, maxau, maxbu, maxav, maxbv;

  stack_info_t() {}
  stack_info_t(int u, int v, int fu, int fv, int sizeu, int sizev, int maxau, int maxbu, int maxav, int maxbv): u(u), v(v), fu(fu), fv(fv), sizeu(sizeu), sizev(sizev), maxau(maxau), maxbu(maxbu), maxav(maxav), maxbv(maxbv) {}
};

int find(int x) {
  return father[x] == x ? x : find(father[x]);
}

void merge(event_t e) {
  int u = find(e.u);
  int v = find(e.v);
  if (u != v) {
    if (size[u] > size[v]) {
      swap(u, v);
    }
    father[u] = v;
    size[v] += size[u];
    cmax(maxa[v], maxa[u]);
    cmax(maxb[v], maxb[u]);
  }
  cmax(maxa[v], e.a);
  cmax(maxb[v], e.b);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d%d", &events[i].u, &events[i].v, &events[i].a, &events[i].b);
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d%d%d%d", &events[m + i].u, &events[m + i].v, &events[m + i].a, &events[m + i].b);
    events[m + i].id = i;
  }
  m += q;
  sort(events + 1, events + 1 + m, cmp_a);
  int M = (int) sqrt(m * log2(m));
  for (int l = 1; l <= m; l += M) {
    int r = min(l + M - 1, m);
    vector<event_t> edges, queries;
    for (int i = 1; i < l; ++i) {
      if (!events[i].id) {
        edges.push_back(events[i]);
      }
    }
    for (int i = l; i <= r; ++i) {
      if (events[i].id) {
        queries.push_back(events[i]);
      }
    }
    if (!queries.size()) {
      continue;
    }
    sort(edges.begin(), edges.end(), cmp_b);
    sort(queries.begin(), queries.end(), cmp_b);
    for (int i = 1; i <= n; ++i) {
      father[i] = i;
      size[i] = 1;
      maxa[i] = -1;
      maxb[i] = -1;
    }
    vector<stack_info_t> pstack;
    int now = 0;
    for (auto e : queries) {
      for (; now < edges.size() && edges[now].b <= e.b; ++now) {
        merge(edges[now]);
      }
      for (int i = l; i <= r; ++i) {
        if (!events[i].id && events[i].a <= e.a && events[i].b <= e.b) {
          int u = find(events[i].u), v = find(events[i].v);
          pstack.emplace_back(u, v, father[u], father[v], size[u], size[v], maxa[u], maxb[u], maxa[v], maxb[v]);
          merge(events[i]);
        }
      }
      answer[e.id] = (find(e.u) == find(e.v) && maxa[find(e.u)] == e.a && maxb[find(e.u)] == e.b);
      for (; pstack.size(); pstack.pop_back()) {
        stack_info_t p = pstack.back();
        father[p.u] = p.fu;
        father[p.v] = p.fv;
        size[p.u] = p.sizeu;
        size[p.v] = p.sizev;
        maxa[p.u] = p.maxau;
        maxb[p.u] = p.maxbu;
        maxa[p.v] = p.maxav;
        maxb[p.v] = p.maxbv;
      }
    }
  }
  for (int i = 1; i <= q; ++i) {
    puts(answer[i] ? "Yes" : "No");
  }
  return 0;
}
