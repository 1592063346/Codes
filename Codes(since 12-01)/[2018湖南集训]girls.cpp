#include<bits/stdc++.h>

using namespace std;

const int N = 234567, sq = 400;

int n, m, degree[N];
vector<int> adj[N];
unordered_map<int, bool> go[N];
unsigned long long a, b, c, s[N], t[N];
bool tag[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> a >> b >> c;
  unsigned long long answer = 0;
  for (int i = n - 1; ~i; --i) {
    s[i] = s[i + 1] + c * i;
    t[i] = t[i + 1] + 1;
  }
  for (int i = 0; i < n; ++i) {
    s[i] = s[i + 1] + b * i * t[i + 1];
    t[i] = t[i + 1];
  }
  for (int i = n - 1; ~i; --i) {
    s[i] += s[i + 1];
    t[i] += t[i + 1];
  }
  for (int i = 0; i < n; ++i) {
    s[i] = s[i + 1] + a * i * t[i + 1];
    answer += s[i];
  }
  auto diff = [&] (int l, int r) {
    return (unsigned long long) (l + r) * (r - l + 1) / 2;
  };
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    if (x > y) {
      swap(x, y);
    }
    adj[x].push_back(y);
    adj[y].push_back(x);
    go[x][y] = go[y][x] = true;
    ++degree[x];
    ++degree[y];
    answer -= diff(0, x - 1) * a + (x * b + y * c) * x;
    answer -= diff(x + 1, y - 1) * b + (x * a + y * c) * (y - x - 1);
    answer -= diff(y + 1, n - 1) * c + (x * a + y * b) * (n - 1 - y);
  }
  vector<int> small, large;
  for (int i = 0; i < n; ++i) {
    if (degree[i] <= sq) {
      small.push_back(i);
      tag[i] = true;
    } else {
      large.push_back(i);
    }
  }
  unsigned long long fac = 1;
  for (int i = 1; i < n; ++i) {
    fac *= i;
  }
  for (int i = 0; i < n; ++i) {
    sort(adj[i].begin(), adj[i].end());
    long long foo1 = 0, bar1 = 0, foo2 = 0, bar2 = 0;
    for (auto j : adj[i]) {
      if (j < i) {
        answer += a * bar1 + (b * j + c * i) * foo1;
        ++foo1;
        bar1 += j;
      } else {
        answer += a * bar1 + (b * i + c * j) * foo1;
        answer += b * bar2 + (a * i + c * j) * foo2;
        ++foo2;
        bar2 += j;
      }
    }
  }
  for (auto i : small) {
    for (int p = 0; p < adj[i].size(); ++p) {
      int j = adj[i][p];
      if (tag[j] && j < i) {
        continue;
      }
      for (int q = p + 1; q < adj[i].size(); ++q) {
        int k = adj[i][q];
        if (tag[k] && k < i) {
          continue;
        }
        if (tag[j] && k < j) {
          continue;
        }
        if (go[j].find(k) == go[j].end()) {
          continue;
        }
        vector<int> x;
        x.push_back(i);
        x.push_back(j);
        x.push_back(k);
        sort(x.begin(), x.end());
        answer -= x[0] * a + x[1] * b + x[2] * c;
      }
    }
  }
  for (auto i : large) {
    for (int p = 0; p < adj[i].size(); ++p) {
      int j = adj[i][p];
      if (tag[j] || j < i) {
        continue;
      }
      for (int q = p + 1; q < adj[i].size(); ++q) {
        int k = adj[i][q];
        if (tag[k] || k < j) {
          continue;
        }
        if (go[j].find(k) == go[j].end()) {
          continue;
        }
        answer -= i * a + j * b + k * c;
      }
    }
  }
  cout << answer << '\n';
  return 0;
}
