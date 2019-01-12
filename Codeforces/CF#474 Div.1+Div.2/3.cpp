#include<bits/stdc++.h>

using namespace std;

int x, d;

int main() {
  scanf("%d%d", &x, &d);
  long long t = 1;
  vector<long long> answer;
  for (int i = 30; i; --i) {
    int c = (1 << i) - 1;
    while (x >= c) {
      x -= c;
      for (int j = 0; j < i; ++j) {
        answer.push_back(t);
      }
      t += d + 1;
    }
  }
  printf("%d\n", answer.size());
  for (int i = 0; i < answer.size(); ++i) {
    printf("%lld%c", answer[i], " \n"[i + 1 == answer.size()]);
  }
  return 0;
}
