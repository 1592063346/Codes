#include<bits/stdc++.h>

using namespace std;

const int N = 3010;

int n, m, p[N], c[N];
vector<int> sup[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &p[i], &c[i]);
    sup[p[i]].push_back(c[i]);
  }
  for (int i = 1; i <= m; ++i) {
    sort(sup[i].begin(), sup[i].end());
  }
  long long answer = 1e18;
  for (int i = 1; i <= n; ++i) {
    vector<int> total;
    int num_1 = sup[1].size();
    long long result = 0;
    for (int j = 2; j <= m; ++j) {
      for (int k = 0; k < sup[j].size(); ++k) {
        if (k <= (int) sup[j].size() - i) {
          ++num_1;
          result += sup[j][k];
        } else {
          total.push_back(sup[j][k]);
        }
      }
    }
    sort(total.begin(), total.end());
    for (auto v : total) {
      if (num_1 >= i) {
        break;
      }
      ++num_1;
      result += v;
    }
    if (num_1 >= i) {
      answer = min(answer, result);
    }
  }
  printf("%I64d\n", answer);
  return 0;
}
