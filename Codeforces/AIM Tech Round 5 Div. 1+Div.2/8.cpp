#include<bits/stdc++.h>

using namespace std;

const int N = 194600, max_value = 5032108;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int n, q, a[N], minp[max_value], ans[N][16], min_step[max_value][8];
bool is_prime[max_value];
vector<int> primes;

void sieve() {
  memset(is_prime, true, sizeof is_prime);
  for (int i = 2; i <= max_value; ++i) {
    if (!minp[i]) {
      minp[i] = i;
      primes.push_back(i);
    }
    for (auto v : primes) {
      int d = i * v;
      if (d > max_value) {
        break;
      }
      minp[d] = v;
      if (i % v == 0) {
        break;
      }
    }
  }
}

int main() {
  sieve();
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n + 1; ++i) {
    for (int j = 0; j <= 14; ++j) {
      ans[i][j] = n + 1;
    }
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }

  auto get_sets = [&] (int value) {
    vector<int> prime_e;
    vector<pair<int, int>> result;
    while (value ^ 1) {
      int pri = minp[value], total = 0;
      for (; value % pri == 0; ++total, value /= pri);
      if (total & 1) {
        prime_e.push_back(pri);
      }
    }
    function<void(int, int, int)> dfs = [&] (int x, int v, int dist) {
      if (x == prime_e.size()) {
        result.emplace_back(v, dist);
      } else {
        dfs(x + 1, v * prime_e[x], dist);
        dfs(x + 1, v, dist + 1);
      }
    };
    dfs(0, 1, 0);
    return result;
  };

  memset(min_step, -1, sizeof min_step);
  for (int i = n; i; --i) {
    vector<pair<int, int>> all = get_sets(a[i]);
    for (auto p : all) {
      for (int j = 0; j <= 7; ++j) {
        if (~min_step[p.first][j]) {
          cmin(ans[i][p.second + j], min_step[p.first][j]);
        }
      }
    }
    for (auto p : all) {
      min_step[p.first][p.second] = i;
    }
    for (int j = 0; j <= 14; ++j) {
      cmin(ans[i][j], ans[i + 1][j]);
    }
  }
  for (int i = 1; i <= q; ++i) {
    int l, r, result = 0;
    scanf("%d%d", &l, &r);
    for (;; ++result) {
      if (ans[l][result] <= r) {
        break;
      }
    }
    printf("%d\n", result);
  }
  return 0;
}
