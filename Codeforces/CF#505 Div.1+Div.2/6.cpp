#include<bits/stdc++.h>

using namespace std;

const int N = 2e3 + 10;
const double pi = acos(-1);

int n, x[N], y[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &x[i], &y[i]);
  }
  function<long long (int)> binom2 = [&] (int n) {
    return (long long) n * (n - 1) >> 1;
  };
  long long answer = 0;
  for (int i = 1; i <= n; ++i) {
    vector<double> angle;
    for (int j = 1; j <= n; ++j) {
      if (j != i) {
        angle.push_back(atan2(y[j] - y[i], x[j] - x[i]));
      }
    }
    sort(angle.begin(), angle.end());
    int pos = angle.size();
    for (int i = 0; i < pos; ++i) {
      angle.push_back(angle[i] + pi * 2);
    }
    for (int i = pos, j = 0; i < angle.size(); ++i) {
      for (; angle[i] - angle[j] > pi; ++j);
      int other = n - 2 - i + j;
      answer += binom2(i - j) * binom2(other);
    }
  }
  printf("%I64d\n", answer >> 1);
  return 0;
}
