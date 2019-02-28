#include<bits/stdc++.h>

using namespace std;

const int N = 5e2 + 10;

int n, nodes[N], size[N];
vector<int> s[N << 2];
vector<pair<int, int>> edges;

int solve(vector<int>& s, vector<int>& t, int v) {
  printf("%d\n", s.size());
  for (int i = 0; i < s.size(); ++i) {
    printf("%d%c", s[i], " \n"[i + 1 == s.size()]);
  }
  printf("%d\n", t.size());
  for (int i = 0; i < t.size(); ++i) {
    printf("%d%c", t[i], " \n"[i + 1 == t.size()]);
  }
  printf("%d\n", v);
  fflush(stdout);
  int result;
  scanf("%d", &result);
  return result;
}

void print_answer() {
  puts("ANSWER");
  for (auto edge : edges) {
    printf("%d %d\n", edge.first, edge.second);
  }
}

void modify(int l, int r, int o, int p) {
  s[o].push_back(p);
  if (l != r) {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, o << 1, p);
    } else {
      modify(mid + 1, r, o << 1 | 1, p);
    }
  }
}

void query(int l, int r, int o, int p) {
  vector<int> one(1, 1);
  int sum = solve(one, s[o], p);
  if (sum) {
    if (l == r) {
      edges.emplace_back(p, l);
      for (int x = o; x; x >>= 1) {
        s[x].erase(find(s[x].begin(), s[x].end(), l));
      }
    } else {
      int mid = l + r >> 1;
      if (s[o << 1].size()) {
        query(l, mid, o << 1, p);
      }
      if (s[o << 1 | 1].size()) {
        query(mid + 1, r, o << 1 | 1, p);
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  vector<int> one(1, 1), others;
  for (int i = 2; i <= n; ++i) {
    others.push_back(i);
  }
  size[1] = n;
  for (int i = 2; i <= n; ++i) {
    size[i] = solve(one, others, i);
  }
  for (int i = 1; i <= n; ++i) {
    nodes[i] = i;
  }
  sort(nodes + 1, nodes + 1 + n, [&] (const int& x, const int& y) {
    return size[x] < size[y];
  });
  for (int i = 1; i < n; ++i) {
    if (size[nodes[i]] != 1) {
      query(1, n, 1, nodes[i]);
    }
    modify(1, n, 1, nodes[i]);
  }
  for (auto x : s[1]) {
    edges.emplace_back(1, x);
  }
  print_answer();
  return 0;
}
