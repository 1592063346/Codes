#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, m, degree[N];
vector<int> adj[N], sadj[N];
long long f3[N], f4[N], f5[N], r3[N], r4[N], tag[N];

bool direct(int x, int y) {
  return degree[x] > degree[y] || (degree[x] == degree[y] && x > y);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
    ++degree[x];
    ++degree[y];
  }
  for (int i = 1; i <= n; ++i) {
    for (auto j : adj[i]) {
      if (direct(i, j)) {
        sadj[i].push_back(j);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (auto j : sadj[i]) {
      ++tag[j];
    }
    for (auto j : sadj[i]) {
      for (auto k : sadj[j]) {
        if (tag[k]) {
          ++r3[i];
          ++r3[j];
          ++r3[k];
        }
      }
    }
    for (auto j : sadj[i]) {
      --tag[j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (auto j : sadj[i]) {
      for (auto k : adj[j]) {
        if (direct(i, k)) {
          r4[i] += tag[k];
          r4[j] += tag[k];
          r4[k] += tag[k];
          ++tag[k];
        }
      }
    }
    for (auto j : sadj[i]) {
      for (auto k : adj[j]) {
        if (direct(i, k)) {
          r4[j] += --tag[k];
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    f3[i] = -degree[i];
    for (auto j : adj[i]) {
      f3[i] += degree[j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    f4[i] = -2ll * r3[i] - (long long) degree[i] * (degree[i] - 1);
    for (auto j : adj[i]) {
      f4[i] += f3[j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    f5[i] = -2ll * r4[i] - 2ll * r3[i] * (degree[i] - 2) - f3[i] * (degree[i] - 1) + 2 * r3[i];
    for (auto j : adj[i]) {
      f5[i] += f4[j];
    }
    cout << f5[i] << '\n';
  }
  return 0;
}
