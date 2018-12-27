#include<bits/stdc++.h>

using namespace std;

const int N = 15e4 + 10;

int n, num[N][2];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &num[i][0], &num[i][1]);
  }
  function<int (int)> check = [&] (int value) {
    if (value == 1) {
      return -1;
    }
    vector<int> e;
    for (int i = 2; i * i <= value; ++i) {
      if (value % i == 0) {
        e.push_back(i);
        for (; value % i == 0; value /= i);
      }
    }
    if (value != 1) {
      e.push_back(value);
    }
    for (auto v : e) {
      bool fail = false;
      for (int i = 1; i <= n; ++i) {
        if (num[i][0] % v && num[i][1] % v) {
          fail = true;
          break;
        }
      }
      if (!fail) {
        return v;
      }
    }
    return -1;
  };
  int answer = check(num[1][0]);
  if (!~answer) {
    answer = check(num[1][1]);
  }
  printf("%d\n", answer);
  return 0;
}
