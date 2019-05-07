#include<bits/stdc++.h>

using namespace std;

const int N = 10000005;

int k, seed, s, p[N << 2], sum[N << 2];

class my_array {
 public:
  int a[N << 1];

  int& operator [] (int x) {
    return a[x + k];
  }

  void reset() {
    memset(a, 0, sizeof a);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> k >> seed >> s;
  auto rng = [&] () {
    return seed = ((seed * 12321) ^ 9999) % 32768;
  };
  int t = 0, n = k << 1 | 1;
  for (int i = 1; i <= n; ++i) {
    p[i] = rng() / 128 % 2;
    t += p[i];
  }
  int x = 1;
  while (t > k) {
    while (p[x] == 0) {
      ++x;
    }
    p[x] = 0;
    --t;
  }
  while (t < k) {
    while (p[x] == 1) {
      ++x;
    }
    p[x] = 1;
    ++t;
  }
  for (int i = 1; i <= n; ++i) {
    p[n + i] = p[i];
  }
  for (int i = 1; i <= (n << 1); ++i) {
    sum[i] = sum[i - 1] + (p[i] == 1 ? 1 : -1);
  }
  my_array number;
  auto solve = [&] (int value, int x) {
    int foo = 0, bar = 0;
    number.reset();
    for (int i = 1, j = 0; i <= n; ++i) {
      if (p[i] == 1) {
        bar -= number[++foo];
      } else {
        bar += number[foo--];
      }
      while (j < i + n - 1) {
        ++j;
        if (p[j] == 1) {
          if (sum[j] > foo) {
            ++bar;
          }
          ++number[sum[j]];
        }
      }
      if (i > 1) {
        if (p[i - 1] == 1) {
          if (sum[i - 1] > foo) {
            --bar;
          }
          --number[sum[i - 1]];
        }
      }
      if (p[i] == value) {
        if (bar == x) {
          return i;
        }
      }
    }
  };
  cout << solve(0, 0) << '\n';
  cout << solve(0, s) << '\n';
  for (int i = 1; i <= (n << 1); ++i) {
    p[i] = !p[i];
  }
  for (int i = 1; i <= (n << 1); ++i) {
    sum[i] = sum[i - 1] + (p[i] == 1 ? 1 : -1);
  }
  cout << solve(1, s) << '\n';
  return 0;
}
