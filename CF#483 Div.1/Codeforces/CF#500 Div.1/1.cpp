#include<bits/stdc++.h>

using namespace std;

int main() {
  int n, half;
  scanf("%d", &n);
  half = n;
  n <<= 1;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  sort(a.begin(), a.end());
  long long answer = 1e18;
  for (int i = 0; i + half - 1 < n; ++i) {
    long long l = i == 0 ? a[half] : a[0];
    long long r = i + half == n ? a[n - half - 1] : a[n - 1];
    answer = min(answer, (r - l) * (a[i + half - 1] - a[i]));
  }
  printf("%I64d\n", answer);
  return 0;
}
