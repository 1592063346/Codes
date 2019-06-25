#include<bits/stdc++.h>

using namespace std;

const int N = 456789, inf = 1e9;

class edge_t {
 public:
  int to, cap, flow;

  edge_t() {
  }

  edge_t(int to, int cap, int flow): to(to), cap(cap), flow(flow) {
  }
};

class flow_t {
  int n, s, t;
  vector<vector<int>> adj;
  vector<edge_t> edges;
  vector<int> d, cur;

 public:
  flow_t(int n, int s, int t): n(n), s(s), t(t) {
    adj.resize(n);
    d.resize(n);
    cur.resize(n);
  }

  void add_edge(int from, int to, int cap) {
    edges.emplace_back(to, cap, 0);
    edges.emplace_back(from, 0, 0);
    int z = edges.size();
    adj[from].push_back(z - 2);
    adj[to].push_back(z - 1);
  }

  bool bfs() {
    fill(d.begin(), d.end(), -1);
    fill(cur.begin(), cur.end(), 0);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (auto y : adj[x]) {
        if (edges[y].flow < edges[y].cap && !~d[edges[y].to]) {
          d[edges[y].to] = d[x] + 1;
          q.push(edges[y].to);
        }
      }
    }
    return ~d[t];
  }

  int dfs(int x, int y) {
    if (x == t || !y) {
      return y;
    }
    int flow = 0;
    for (int& i = cur[x]; i < adj[x].size(); ++i) {
      int j = adj[x][i], f;
      if (d[x] + 1 == d[edges[j].to] && (f = dfs(edges[j].to, min(edges[j].cap - edges[j].flow, y))) > 0) {
        edges[j].flow += f;
        edges[j ^ 1].flow -= f;
        flow += f;
        y -= f;
        if (!y) {
          break;
        }
      }
    }
    return flow;
  }

  int max_flow() {
    int result = 0;
    while (bfs()) {
      result += dfs(s, inf);
    }
    return result;
  }
};

int q, n, tt, last, ch[N][26], father[N], len[N];
string s, t;

int new_node(int from) {
  len[++tt] = len[from] + 2;
  return tt;
}

void extend(int i, int c) {
  int p = last;
  while (t[i - len[p] - 1] - 'a' != c) {
    p = father[p];
  }
  if (!ch[p][c]) {
    int np = new_node(p), q = father[p];
    while (t[i - len[q] - 1] - 'a' != c) {
      q = father[q];
    }
    father[np] = ch[q][c];
    ch[p][c] = np;
  }
  last = ch[p][c];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> q;
  while (q--) {
    cin >> s;
    n = s.length();
    memset(ch, 0, sizeof ch);
    memset(father, 0, sizeof father);
    tt = 1;
    last = 0;
    father[0] = 1;
    len[1] = -1;
    t.clear();
    t.push_back('z' + 1);
    for (int i = 0; i < n; ++i) {
      t.push_back(s[i]);
      extend(i + 1, s[i] - 'a');
    }
    flow_t graph(tt << 1, 0, 1);
    for (int i = 2; i <= tt; ++i) {
      graph.add_edge(0, i - 1 << 1, 1);
      graph.add_edge(i - 1 << 1 | 1, 1, 1);
      graph.add_edge(i - 1 << 1 | 1, i - 1 << 1, inf);
      if (father[i] >= 2) {
        graph.add_edge(father[i] - 1 << 1, i - 1 << 1 | 1, inf);
      }
      for (int j = 0; j < 26; ++j) {
        if (ch[i][j] >= 2) {
          graph.add_edge(i - 1 << 1, ch[i][j] - 1 << 1 | 1, inf);
        }
      }
    }
    cout << tt - 1 - graph.max_flow() << '\n';
  }
  return 0;
}
