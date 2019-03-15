#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int n, k, m, s, a[N], b[N], sh[N], number[N], all;

int main() {
  scanf("%d%d%d%d", &n, &k, &m, &s);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= s; ++i) {
    scanf("%d", &b[i]);
    if (++sh[b[i]] == 1) {
      ++all;
    }
  }
  int legal = 0;
  for (int i = n, j = n; i; --i) {
    for (; j && (legal < all || i - j < k); --j) {
      if (++number[a[j]] == sh[a[j]]) {
        ++legal;
      }
    }
    if (legal < all) {
      break;
    }
    if (j / k + 1 + (n - i) / k >= m) {
      vector<int> answer;
      for (int p = 1; p <= j % k; ++p) {
        answer.push_back(p);
      }
      memset(number, 0, sizeof number);
      for (int p = j + 1, t = i - j - k; t && p <= i; ++p) {
        if (++number[a[p]] > sh[a[p]]) {
          --t;
          answer.push_back(p);
        }
      }
      for (int p = i + 1; p <= i + (n - i) % k; ++p) {
        answer.push_back(p);
      }
      printf("%d\n", answer.size());
      for (auto v : answer) {
        printf("%d ", v);
      }
      return puts(""), 0;
    }
    if (--number[a[i]] == sh[a[i]] - 1) {
      --legal;
    }
  }
  puts("-1");
  return 0;
}
