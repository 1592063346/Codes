#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int q, h[N], w[N], t;
char cmd[N][3];
long long number[N];
multiset<int> eels;

void modify(int p, int v) {
  for (; p <= t; p += p & -p) {
    number[p] += v;
  }
}

long long query(int p) {
  long long result = 0;
  for (; p; p -= p & -p) {
    result += number[p];
  }
  return result;
}

int id(int x) {
  return lower_bound(h + 1, h + 1 + t, x) - h;
}

int main() {
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%s%d", cmd[i], &w[i]);
    h[++t] = w[i];
  }
  sort(h + 1, h + 1 + t);
  t = unique(h + 1, h + 1 + t) - h - 1;
  for (int i = 1; i <= q; ++i) {
    if (*cmd[i] == '+') {
      modify(id(w[i]), w[i]);
      eels.insert(w[i]);
    } else {
      modify(id(w[i]), -w[i]);
      eels.erase(eels.lower_bound(w[i]));
    }
    if (!eels.size()) {
      puts("0");
    } else {
      int x = *eels.begin(), answer = 0;
      while (1) {
        multiset<int>:: iterator p = eels.lower_bound(x * 2 + 1);
        if (p == eels.end()) {
          break;
        } else {
          int y = id(x = *p);
          if (*p > 2 * query(y - 1)) {
            ++answer;
          }
        }
      }
      printf("%d\n", eels.size() - answer - 1);
    }
  }
  return 0;
}
