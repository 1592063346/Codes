#include<bits/stdc++.h>

using namespace std;

int n;

int main() {
  scanf("%d", &n);
  int answer = n >> 1;
  printf("%d\n", answer);
  vector<pair<int, int>> t0;
  for (int i = 1; i <= answer; ++i) {
    t0.emplace_back(1, 1 + i);
  }
  for (int i = answer + 2; i <= n; ++i) {
    t0.emplace_back(answer + 1, i);
  }
  for (int i = 0; i < answer; ++i, puts("")) {
    for (auto p : t0) {
      printf("%d %d ", (p.first + i - 1) % n + 1, (p.second + i - 1) % n + 1);
    }
  }
  return 0;
}
