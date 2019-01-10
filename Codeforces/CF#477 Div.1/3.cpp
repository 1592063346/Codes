#include<bits/stdc++.h>

using namespace std;

int n;
vector<long long> bits[60], answer;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    long long x;
    scanf("%lld", &x);
    for (int j = 59; ~j; --j) {
      if (x >> j & 1) {
        bits[j].push_back(x);
        break;
      }
    }
  }
  bool ok = true;
  long long t = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 60; ++j) {
      if (!(t >> j & 1) && bits[j].size()) {
        answer.push_back(bits[j].back());
        t ^= bits[j].back();
        bits[j].pop_back();
        break;
      }
    }
    if (answer.size() != i) {
      ok = false;
      break;
    }
  }
  if (!ok) {
    puts("No");
  } else {
    puts("Yes");
    for (int i = 0; i < n; ++i) {
      printf("%lld%c", answer[i], " \n"[i + 1 == n]);
    }
  }
  return 0;
}
